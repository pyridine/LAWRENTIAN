#include "profilewidget.h"
#include "ui_profilewidget.h"
#include <string>
#include <qstring.h>
#include <iostream>

#include "editprofilewidget.h"
#include "editemployeeinfo.h"

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
    // Checks what writers can be taken off probation
    QDate currentDate = QDate::currentDate();
    vector<string> possibleProbationApprovals = profileWidgetDBC->collectProbationApprovals(currentDate);
    if(possibleProbationApprovals.size()>0){
        QString probationApprovalText = "Writers to be taken off probation: ";
        ui->systemNotificationsTextBrowser->append("<span>"+probationApprovalText+"</span>");
        for(int i = 0; i < possibleProbationApprovals.size(); i++){
            QString name = QString::fromStdString(possibleProbationApprovals[i]);
            QString indexString = QString::number(i);
            QString url = "<a href="+indexString+">"+name+"</a>";
            ui->systemNotificationsTextBrowser->append(url);
            selectedUser = QString::fromStdString(possibleProbationApprovals[i]);
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
    QDate currentDate = QDate::currentDate();
    vector<string> possibleProbationApprovals = profileWidgetDBC->collectProbationApprovals(currentDate);
    string urlString = arg1.toString().toStdString();
    int urlInt = stoi(urlString);
    EditEmployeeInfo *employeeInfo = new EditEmployeeInfo;
    employeeInfo->initDB(this->client);
    employeeInfo->initSelectedName(QString::fromStdString(possibleProbationApprovals[urlInt]));
    employeeInfo->show();
}

void profileWidget::on_pushButton_clicked()
{
    updateNotifications();
}
