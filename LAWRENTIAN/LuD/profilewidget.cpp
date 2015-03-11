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

void profileWidget::init(LoginCredentials* l, Client *c, employeesWidget *ew)
{
    loginCred = l;
    this->client = c;
    this->ew = ew;

    if(!loginCred->hasPermission(PermissionDef::ADMIN_PTOKEN)
            &&!loginCred->hasPermission(PermissionDef::VIEW_TIMESHEETS)
            &&!loginCred->hasPermission(PermissionDef::MANAGE_EMPLOYEE_PROBATION)){
        this->ui->systemNotificationsTextBrowser->hide();
        this->ui->label->hide();
        ui->currentIssueDate->setEnabled(false);
        ui->setDateButton->setEnabled(false);
    }
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateNotifications()));
    timer->start(10000);
}

void profileWidget::initDB(Client *c){
    profileWidgetDBC = new ProfileWidgetDBC(c);

    QDate latestDate = profileWidgetDBC->collectLatestIssueDate();
    if((!latestDate.isNull()) && QDate::currentDate()<=latestDate){
        ui->currentIssueDate->setDate(latestDate);
        QString latestDateString = latestDate.toString("d MMMM yyyy");
        ui->dateLabel->setText(latestDateString);
        ui->selectTimesheetDate->setDate(latestDate);
    } else {
        ui->currentIssueDate->setDate(QDate::currentDate());
        QPalette palette = ui->currentIssueDate->palette();
        //palette.setColor(QPalette::Base, Qt::green);
        palette.brightText();
        ui->currentIssueDate->setPalette(palette);
        ui->setDateButton->setDefault(true);
        ui->dateLabel->setText("NO DATE SPECIFIED");
        ui->selectTimesheetDate->setDate(QDate::currentDate());
    }
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

    // Checks what employees need to be approved:
    vector<string> unapprovedEmployees = profileWidgetDBC->collectRegistrationApprovals();
    if(unapprovedEmployees.size()>0)
    {
        QString employeeApprovalText = "Employees to be approved: ";
        ui->systemNotificationsTextBrowser->append("<span>"+employeeApprovalText+"</span>");
        for(int i = 0; i < unapprovedEmployees.size(); i++){
            QString name = QString::fromStdString(unapprovedEmployees[i]);
            QString indexString = QString::number(i);
            QString prefix = "employeeApprovals";
            QString url = "<a href="+prefix+indexString+">"+name+"</a>";
            ui->systemNotificationsTextBrowser->append(url);
        }
        ui->systemNotificationsTextBrowser->append("<table width=\"100%\"><tr><td><hr /></td></tr></table>");
    }

    if(loginCred->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCred->hasPermission(PermissionDef::MANAGE_EMPLOYEE_PROBATION)){
        // Checks what writers can be taken off probation
        vector<string> possibleProbationApprovals = profileWidgetDBC->collectProbationApprovals(currentDate);
        if(possibleProbationApprovals.size()>0){
            QString probationApprovalText = "Writers to be taken off probation: ";
            ui->systemNotificationsTextBrowser->append("<span>"+probationApprovalText+"</span>");
            for(int i = 0; i < possibleProbationApprovals.size(); i++){
                QString name = QString::fromStdString(possibleProbationApprovals[i]);
                QString indexString = QString::number(i);
                QString prefix = "probationApprovals";
                QString url = "<a href="+prefix+indexString+">"+name+"</a>";
                ui->systemNotificationsTextBrowser->append(url);
            }
            ui->systemNotificationsTextBrowser->append("<table width=\"100%\"><tr><td><hr /></td></tr></table>");
        }
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
    vector<string> unapprovedEmployees = profileWidgetDBC->collectRegistrationApprovals();

    size_t approvalExists = urlString.find("employeeApprovals");
    if(approvalExists != string::npos){
        string indexString = urlString.substr(approvalExists+17);
        int index = stoi(indexString);
        EditEmployeeInfo *employeeInfo = new EditEmployeeInfo;
        employeeInfo->init(loginCred, ew);
        employeeInfo->initDB(this->client);
        employeeInfo->initSelectedNameApproval(QString::fromStdString(unapprovedEmployees[index]));
        employeeInfo->show();
    }

    // Approve Probation
    size_t probationExists = urlString.find("probationApprovals");
    if(probationExists != string::npos){
        string indexString = urlString.substr(probationExists+18);
        int index = stoi(indexString);
        EditEmployeeInfo *employeeInfo = new EditEmployeeInfo;
        employeeInfo->init(loginCred, ew);
        employeeInfo->initDB(this->client);
        employeeInfo->initSelectedNameProbation(QString::fromStdString(possibleProbationApprovals[index]));
        employeeInfo->show();
    }



}

void profileWidget::on_setDateButton_clicked()
{
    Alert *alert = new Alert;
    int ret = alert->showQuestionAlert("Set Date", "Are you sure you went to set the current issue date?");
    switch(ret) {
    case QMessageBox::Save: {
        QDate currentIssue = ui->currentIssueDate->date();
        profileWidgetDBC->setCurrentIssueDate(currentIssue);
        QString currentIssueString = currentIssue.toString("d MMMM yyyy");
        ui->dateLabel->setText(currentIssueString);
        break;
    }
    case QMessageBox::Cancel:
        return;
    }
}

void profileWidget::on_submitChangesButton_clicked()
{
    Alert *alert = new Alert;
    int ret = alert->showQuestionAlert("Submit Changes", "Are you sure you want to submit changes?");
    switch(ret){
    case QMessageBox::Save:
    {
        int LUID = loginCred->getLUID();
        QDate chosenDate = ui->selectTimesheetDate->date();
        int hoursWorked = ui->hoursWorkedTextEdit->text().toInt();
        profileWidgetDBC->setHoursWorked(LUID, chosenDate, hoursWorked);

        Alert *confirm = new Alert;
        confirm->showInformationAlert("Updated Successfully", "Hours updated successfully!");
        break;
    }
    case QMessageBox::Cancel:
        break;
    }
}

void profileWidget::on_setCurrentIssueButton_clicked()
{
    QDate latestIssue = profileWidgetDBC->collectLatestIssueDate();
    if(!latestIssue.isNull()){
        ui->selectTimesheetDate->setDate(latestIssue);
    } else {
        Alert *alert = new Alert;
        alert->showInformationAlert("No Set Issue Date", "No current issue date set.\nSetting to current date");
        ui->selectTimesheetDate->setDate(QDate::currentDate());
    }
}

void profileWidget::on_selectTimesheetDate_userDateChanged(const QDate &date)
{
    int LUID = loginCred->getLUID();
    QDate chosenDate = ui->selectTimesheetDate->date();
    int hours = profileWidgetDBC->getHoursWorked(LUID, chosenDate);
    if(hours == NULL){
        hours = 0;
        QString hoursString = QString::number(hours);
        ui->hoursWorkedTextEdit->setText(hoursString);
    } else{
        QString hoursString = QString::number(hours);
        ui->hoursWorkedTextEdit->setText(hoursString);
    }
}
