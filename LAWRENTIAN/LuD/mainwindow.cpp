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

void MainWindow::init(LoginWindow *parent, LoginCredentials *l){
    loginCredo = l;
    parentWindow = parent;

    QWidget *mainWidget = new QWidget(ui->centralwidget);
    QTabWidget *tabs = new QTabWidget(mainWidget);


    tabs->setFixedSize(1100,600);

    //Init/Add profile widget.
    profileWidget* w_profile = new profileWidget();
    w_profile->init(this,loginCredo->getName());
    tabs->addTab(w_profile, "Profile");

    tabs->addTab(new employeesWidget(), "Employees");
    //TODO: Submenues in employees depending on can see all employee info, can edit permissions,
    //probations, etc.


    if(loginCredo->hasPermission(PToken::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PToken::SUBMIT_COPY)
            ||loginCredo->hasPermission(PToken::EDIT_COPY)
            ||loginCredo->hasPermission(PToken::SUBMIT_GRAPHIC)
            ||loginCredo->hasPermission(PToken::EDIT_GRAPHIC)
            ||loginCredo->hasPermission(PToken::SUBMIT_PHOTO)
            ||loginCredo->hasPermission(PToken::EDIT_PHOTO)
            ||loginCredo->hasPermission(PToken::EDIT_ARTICLE_WORKSPACE)
            ||loginCredo->hasPermission(PToken::APPROVE_ARTICLE)){

        tabs->addTab(new articleWorkspace(), "Article Workspace");
        //TODO: Display submenus of categories (News, Feat, A&E, etc) by permission.
    }

    if(loginCredo->hasPermission(PToken::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PToken::EDIT_TIMESHEETS)
            ||loginCredo->hasPermission(PToken::VIEW_TIMESHEETS)){

        tabs->addTab(new editorTimesheetWidget(), "Editor Timesheet");
    }

    if(loginCredo->hasPermission(PToken::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PToken::EDIT_TIMESHEETS)
            ||loginCredo->hasPermission(PToken::VIEW_TIMESHEETS)){

        tabs->addTab(new writerTimesheetWidget(), "Writer Timesheet");
    }


    if(loginCredo->hasPermission(PToken::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PToken::EDIT_TIMESHEETS)
            ||loginCredo->hasPermission(PToken::VIEW_TIMESHEETS)){

        tabs->addTab(new writerTimesheetWidget(), "Writer Timesheet");
    }


    if(loginCredo->hasPermission(PToken::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PToken::EDIT_SUBSCRIPTIONS)
            ||loginCredo->hasPermission(PToken::VIEW_SUBSCRIPTIONS)){

        tabs->addTab(new subscriptionsWidget(), "Subscriptions");
    }

    if(loginCredo->hasPermission(PToken::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PToken::EDIT_CIRCULATIONS)
            ||loginCredo->hasPermission(PToken::VIEW_CIRCULATIONS)){

        tabs->addTab(new circulationWidget(), "Circulation");
    }

    if(loginCredo->hasPermission(PToken::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PToken::EDIT_ADS)
            ||loginCredo->hasPermission(PToken::VIEW_ADS)){

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
