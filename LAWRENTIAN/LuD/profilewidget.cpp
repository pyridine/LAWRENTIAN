#include "profilewidget.h"
#include "ui_profilewidget.h"
#include <string>
#include <qstring.h>
#include <iostream>
#include "alert.h"

#include "editprofilewidget.h"
#include "editemployeeinfo.h"
#include "Sender.h"
#include "FileSystem.h"

using namespace std;

profileWidget::profileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profileWidget)
{
    ui->setupUi(this);
}

void profileWidget::init(LoginCredentials* l, Client *c){
    loginCred = l;
    this->client = c;
}

void profileWidget::initDB(Client *c){
    profileWidgetDBC = new ProfileWidgetDBC(c);
}

void profileWidget::init(MainWindow *parent, QString name, string title){
    setWelcomeLabel();
    updateNotifications();
    parentWindow = parent;
}

void profileWidget::setWelcomeLabel()
{
    QString name = QString::fromStdString(profileWidgetDBC->collectName(loginCred->getLUID()));
    QString title = QString::fromStdString(profileWidgetDBC->collectTitle(loginCred->getLUID()));
    ui->welcomeLabel->setText((QString::fromStdString("Welcome, ")+(name)+(QString::fromStdString("!"))));
    ui->titleLabel->setText((QString::fromStdString("(")+title+QString::fromStdString(")")));
}

void profileWidget::updateNotifications()
{
    ui->systemNotificationsTextBrowser->clear();
    ui->systemNotificationsTextBrowser->setOpenLinks(false);

    QDate currentDate = QDate::currentDate();

    // Checks what writers can be taken off probation
    vector<string> possibleProbationApprovals = profileWidgetDBC->collectProbationApprovals(currentDate);
    if(possibleProbationApprovals.size()>0){
        QString probationApprovalText = "Writers to be taken off probation: ";
        ui->systemNotificationsTextBrowser->append("<span>"+probationApprovalText+"</span>");
        for(int i = 0; i < possibleProbationApprovals.size(); i++){
            QString name = QString::fromStdString(possibleProbationApprovals[i]);
            QString indexString = QString::number(i);
            QString url = "<a href="+indexString+">"+name+"</a>";
            ui->systemNotificationsTextBrowser->append(url);
        }
        ui->systemNotificationsTextBrowser->append("<span>\n</span>");
    }

    // Checks if timesheet can be and should be generated
    vector<int> timesheetWriterIds = profileWidgetDBC->collectWriterForTimesheet(currentDate);
    int alreadyExists = profileWidgetDBC->writerTimesheetExists(currentDate);
    if(timesheetWriterIds.size()>0 && alreadyExists==0){
        QString timesheetGenerationText = "Generate/Update Writer Timesheet: ";
        ui->systemNotificationsTextBrowser->append("<span>"+timesheetGenerationText+"</span>");
        QString url = "<a href=GenerateWriterTimesheet>Generate</a>";
        ui->systemNotificationsTextBrowser->append(url);
    }

    // Checks if timesheet can be updated
    if(timesheetWriterIds.size()!=alreadyExists && alreadyExists>0){
        QString timesheetGenerationText = "Generate/Update Writer Timesheet: ";
        ui->systemNotificationsTextBrowser->append("<span>"+timesheetGenerationText+"</span>");
        QString url = "<a href=UpdateWriterTimesheet>Update</a>";
        ui->systemNotificationsTextBrowser->append(url);
    }
}

profileWidget::~profileWidget()
{
    delete ui;
}

void profileWidget::on_logOutButton_clicked()
{
    parentWindow->logOut();
}

void profileWidget::on_editProfileButton_clicked()
{
    EditProfileWidget *editProfileWidget = new EditProfileWidget;
    editProfileWidget->myParent = this;
    editProfileWidget->init(loginCred);
    editProfileWidget->initDB(this->client);
    editProfileWidget->populateAllFields();
    editProfileWidget->show();

}

void profileWidget::on_systemNotificationsTextBrowser_anchorClicked(const QUrl &arg1)
{
    string urlString = arg1.toString().toStdString();

    QDate currentDate = QDate::currentDate();
    vector<string> possibleProbationApprovals = profileWidgetDBC->collectProbationApprovals(currentDate);
    vector<int> writerIds = profileWidgetDBC->collectWriterForTimesheet(currentDate);

    //Generate Timesheet
    if(urlString == "GenerateWriterTimesheet"){
        for(int i = 0; i<writerIds.size(); i++){
            pair<int, int> submissionDate = calculateArticlesOnTimeAndLate(currentDate, writerIds[i]);
            profileWidgetDBC->generateWriterTimesheet(writerIds[i], submissionDate.first, submissionDate.second, currentDate);
        }
        Alert *alert = new Alert;
        alert->showInformationAlert("Generated!", "Writer Timesheet successfully generated");
        updateNotifications();
        this->parentWindow->tabs->setCurrentIndex(4);
    } else if(urlString == "UpdateWriterTimesheet"){
        profileWidgetDBC->deleteWriterTimesheetRecords(currentDate);
        for(int i = 0; i<writerIds.size(); i++){
            pair<int, int> submissionDate = calculateArticlesOnTimeAndLate(currentDate, writerIds[i]);
            profileWidgetDBC->generateWriterTimesheet(writerIds[i], submissionDate.first, submissionDate.second, currentDate);
        }
        Alert *alert = new Alert;
        alert->showInformationAlert("Updated!", "Writer Timesheet successfully updated");
        updateNotifications();
        this->parentWindow->tabs->setCurrentIndex(4);
    } else {
        // Approve Probation
        int urlInt = stoi(urlString);
        EditEmployeeInfo *employeeInfo = new EditEmployeeInfo;
        employeeInfo->initDB(this->client);
        employeeInfo->initSelectedName(QString::fromStdString(possibleProbationApprovals[urlInt]));
        employeeInfo->show();
    }
}

pair<int, int> profileWidget::calculateArticlesOnTimeAndLate(QDate issueDate, int writerId)
{
    pair<int, int> articlesOnTimeAndLate;
    int articlesOnTime = 0;
    int articlesLate = 0;
    QDate deadline = issueDate.addDays(-3);

    QString issueDateQString = issueDate.toString("yyyy-MM-dd");
    string issueDateString = issueDateQString.toStdString();
    Sender *sndr = new Sender;
    vector<int> articleIds = profileWidgetDBC->collectArticleIdForTimesheet(issueDate, writerId);
    cout<<"Writer with id: "<<writerId<<" has "<<articleIds.size()<<" articles for this issue"<<endl;
    for(int i = 0; i < articleIds.size(); i++){
        string sectionName = profileWidgetDBC->collectArticleSection(articleIds[i]);
        string articleName = profileWidgetDBC->collectArticleTitle(articleIds[i]);
        FileSystem::VerSeq versions;
        versions = sndr->getHistory(issueDateString, sectionName, articleName, fs::COPY);

        // Reads in first submitted file (assumed its submitted by writer)
        if(versions.size()>0){
            FileSystem::TimeIce submissionTime = versions[0].time;
            QDate submissionDate;
            submissionDate.setDate(submissionTime.year, submissionTime.month, submissionTime.day);

            if(submissionDate <= deadline){
                articlesOnTime++;
            } else {
                articlesLate++;
            }
        }
        articlesOnTimeAndLate = make_pair (articlesOnTime, articlesLate);
        return articlesOnTimeAndLate;
    }
}

void profileWidget::on_pushButton_clicked()
{
    updateNotifications();
}
