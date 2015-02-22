#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "articleworkspace.h"
#include "profilewidget.h"
#include "employeeswidget.h"
#include "adwidget.h"
#include "editortimesheetwidget.h"
#include "writertimesheetwidget.h"
#include "subscriptionswidget.h"
#include "circulationwidget.h"

#include <QTabWidget>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

Client* MainWindow::getClient(){
    return client;
}

void MainWindow::init(LoginWindow *parent, LoginCredentials *l){
    loginCredo = l;
    parentWindow = parent;

    QWidget *mainWidget = new QWidget(ui->centralwidget);
    QTabWidget *tabs = new QTabWidget(mainWidget);


    tabs->setFixedSize(1100,600);

    //Init/Add profile widget.
    profileWidget* w_profile = new profileWidget();
    w_profile->init(this,loginCredo->getName(),Permissions::translateTitle(static_cast<Title>(loginCredo->getTitle())));
    tabs->addTab(w_profile, "Profile");

    employeesWidget* empWidget = new employeesWidget();
    empWidget->init(loginCredo);
    empWidget->initDB(client);

    if(loginCredo->hasPermission(VIEW_ALL_EMPLOYEE_INFO)){
        empWidget->initTotalView();
    } else if(loginCredo->hasPermission(VIEW_PRIVILEGED_EMPLOYEE_INFO)){
        empWidget->initPrivilegedView();
    } else{
        empWidget->initNormalView();
    }

    tabs->addTab(empWidget, "Employees");
    //TODO: Submenues in employees depending on can see all employee info, can edit permissions,
    //probations, etc.


    if(loginCredo->hasPermission(ADMIN_PTOKEN)
            ||loginCredo->hasPermission(SUBMIT_COPY)
            ||loginCredo->hasPermission(EDIT_COPY)
            ||loginCredo->hasPermission(SUBMIT_GRAPHIC)
            ||loginCredo->hasPermission(EDIT_GRAPHIC)
            ||loginCredo->hasPermission(SUBMIT_PHOTO)
            ||loginCredo->hasPermission(EDIT_PHOTO)
            ||loginCredo->hasPermission(EDIT_ARTICLE_WORKSPACE)
            ||loginCredo->hasPermission(APPROVE_ARTICLE)){

        tabs->addTab(new articleWorkspace(), "Article Workspace");
        //TODO: Display submenus of categories (News, Feat, A&E, etc) by permission.
    }

    if(loginCredo->hasPermission(ADMIN_PTOKEN)
            ||loginCredo->hasPermission(EDIT_TIMESHEETS)
            ||loginCredo->hasPermission(VIEW_TIMESHEETS)){

        tabs->addTab(new editorTimesheetWidget(), "Editor Timesheet");
    }

    if(loginCredo->hasPermission(ADMIN_PTOKEN)
            ||loginCredo->hasPermission(EDIT_TIMESHEETS)
            ||loginCredo->hasPermission(VIEW_TIMESHEETS)){

        tabs->addTab(new writerTimesheetWidget(), "Writer Timesheet");
    }


    if(loginCredo->hasPermission(ADMIN_PTOKEN)
            ||loginCredo->hasPermission(EDIT_TIMESHEETS)
            ||loginCredo->hasPermission(VIEW_TIMESHEETS)){

        tabs->addTab(new writerTimesheetWidget(), "Writer Timesheet");
    }


    if(loginCredo->hasPermission(ADMIN_PTOKEN)
            ||loginCredo->hasPermission(EDIT_SUBSCRIPTIONS)
            ||loginCredo->hasPermission(VIEW_SUBSCRIPTIONS)){

        tabs->addTab(new subscriptionsWidget(), "Subscriptions");
    }

    if(loginCredo->hasPermission(ADMIN_PTOKEN)
            ||loginCredo->hasPermission(EDIT_CIRCULATIONS)
            ||loginCredo->hasPermission(VIEW_CIRCULATIONS)){

        tabs->addTab(new circulationWidget(), "Circulation");
    }

    if(loginCredo->hasPermission(ADMIN_PTOKEN)
            ||loginCredo->hasPermission(EDIT_ADS)
            ||loginCredo->hasPermission(VIEW_ADS)){

        tabs->addTab(new adWidget(), "Ads");
    }

}

void MainWindow::logOut(){
    delete(loginCredo);
    this->hide();
    parentWindow->show();
}

void MainWindow::initDB(Client* c){
    client = c;
    //Store this, and pass it to controllers upon construction.....
}


MainWindow::~MainWindow()
{
    delete ui;
}
