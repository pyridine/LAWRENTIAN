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
#include "permissiondef.h"
#include "mainwindowdbc.h"
#include <qstring.h>
#include <QTabWidget>
#include <iostream>
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
    w_profile->init(this,loginCredo->getName(),dbController->translateTitle(loginCredo->getTitle()));
    tabs->addTab(w_profile, "Profile");

    employeesWidget* empWidget = new employeesWidget();
    empWidget->init(loginCredo);
    empWidget->initDB(client);



    QString employeeTabTitle = QString::fromStdString("Employees");
    if(loginCredo->hasPermission(PermissionDef::VIEW_ALL_EMPLOYEE_INFO)
            || loginCredo->hasPermission(PermissionDef::VIEW_PRIVILEGED_EMPLOYEE_INFO)){

        int numUnregistered = empWidget->getNumUnregistered();

        if(numUnregistered > 0){
            employeeTabTitle= "Employees (" + QString::number(empWidget->getNumUnregistered()) + " unapproved)";
        }
        if(loginCredo->hasPermission(PermissionDef::VIEW_PRIVILEGED_EMPLOYEE_INFO)){
            empWidget->initPrivilegedView();
        } else{
            empWidget->initTotalView();

        }
    }  else{
        empWidget->initNormalView();
    }


    tabs->addTab(empWidget, employeeTabTitle);

    //TODO: Submenues in employees depending on can see all employee info, can edit permissions,
    //probations, etc.


    cout << "about to create article wksps" << endl;

    if(loginCredo->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PermissionDef::SUBMIT_COPY)
            ||loginCredo->hasPermission(PermissionDef::EDIT_COPY)
            ||loginCredo->hasPermission(PermissionDef::SUBMIT_GRAPHIC)
            ||loginCredo->hasPermission(PermissionDef::EDIT_GRAPHIC)
            ||loginCredo->hasPermission(PermissionDef::SUBMIT_PHOTO)
            ||loginCredo->hasPermission(PermissionDef::EDIT_PHOTO)
            ||loginCredo->hasPermission(PermissionDef::EDIT_ARTICLE_WORKSPACE)
            ||loginCredo->hasPermission(PermissionDef::APPROVE_ARTICLE)){

        articleWorkspace* awk = new articleWorkspace();
        awk->initDB(client,loginCredo);
        awk->updateArticleList();

        tabs->addTab(awk, "Article Workspace");

        //TODO: Display submenus of categories (News, Feat, A&E, etc) by permission.
    }

    if(loginCredo->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PermissionDef::EDIT_TIMESHEETS)
            ||loginCredo->hasPermission(PermissionDef::VIEW_TIMESHEETS)){

        tabs->addTab(new editorTimesheetWidget(), "Editor Timesheet");
    }

    if(loginCredo->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PermissionDef::EDIT_TIMESHEETS)
            ||loginCredo->hasPermission(PermissionDef::VIEW_TIMESHEETS)){

        tabs->addTab(new writerTimesheetWidget(), "Writer Timesheet");
    }


    if(loginCredo->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PermissionDef::EDIT_TIMESHEETS)
            ||loginCredo->hasPermission(PermissionDef::VIEW_TIMESHEETS)){

        tabs->addTab(new writerTimesheetWidget(), "Writer Timesheet");
    }

    if(loginCredo->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PermissionDef::EDIT_CIRCULATIONS)
            ||loginCredo->hasPermission(PermissionDef::VIEW_CIRCULATIONS)){

        circulationWidget* circWidg = new circulationWidget();

        if(loginCredo->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PermissionDef::EDIT_CIRCULATIONS)){
            circWidg->init_ViewAndEditPrivileges(client);
        } else{
            circWidg->init_ViewPrivileges(client);
        }
        tabs->addTab(circWidg, "Circulation");
    }
}

void MainWindow::logOut(){
    delete(loginCredo);
    this->hide();
    parentWindow->show();
}

void MainWindow::initDB(Client* c){
    client = c;
    dbController = new MainWindowDBC(c);
}

MainWindow::~MainWindow()
{
    delete ui;
}
