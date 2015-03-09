#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "articleworkspace.h"
#include "profilewidget.h"
#include "employeeswidget.h"
#include "adwidget.h"
#include "permissionswidget.h"
#include "editortimesheetwidget.h"
#include "writertimesheetwidget.h"
#include "subscriptionswidget.h"
#include "circulationwidget.h"
#include "permissiondef.h"
#include "mainwindowdbc.h"
#include "photopoolwindow.h"
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
    tabs = new QTabWidget(mainWidget);


    tabs->setFixedSize(1100,600);

    // Needs to initialize employeesWidget BEFORE profileWidget
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


    //Init/Add profile widget.
    profileWidget* w_profile = new profileWidget();
    w_profile->init(loginCredo, client, empWidget);
    w_profile->initDB(client);
    w_profile->init(this,loginCredo->getName(),dbController->translateTitle(loginCredo->getTitle()));
    tabs->addTab(w_profile, "Profile");

    // Adds tab for employee
    tabs->addTab(empWidget, employeeTabTitle);


    if(loginCredo->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PermissionDef::SUBMIT_COPY)
            ||loginCredo->hasPermission(PermissionDef::EDIT_COPY)
            ||loginCredo->hasPermission(PermissionDef::SUBMIT_GRAPHIC)
            ||loginCredo->hasPermission(PermissionDef::EDIT_GRAPHIC)
            ||loginCredo->hasPermission(PermissionDef::SUBMIT_PHOTO)
            ||loginCredo->hasPermission(PermissionDef::EDIT_PHOTO)
            ||loginCredo->hasPermission(PermissionDef::EDIT_ARTICLE_WORKSPACE)
            ||loginCredo->hasPermission(PermissionDef::SEC_ALL)
            ||loginCredo->hasPermission(PermissionDef::SEC_ARTS)
            ||loginCredo->hasPermission(PermissionDef::SEC_FEATURES)
            ||loginCredo->hasPermission(PermissionDef::SEC_NEWS)
            ||loginCredo->hasPermission(PermissionDef::SEC_OPED)
            ||loginCredo->hasPermission(PermissionDef::SEC_SPORTS)
            ||loginCredo->hasPermission(PermissionDef::SEC_VARIETY)){

        articleWorkspace* awk = new articleWorkspace();
        awk->init(this, client,loginCredo);
        //awk->updateArticleList();

        tabs->addTab(awk, "Articles");

        //TODO: Display submenus of categories (News, Feat, A&E, etc) by permission.
    }

    if(loginCredo->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PermissionDef::EDIT_TIMESHEETS)
            ||loginCredo->hasPermission(PermissionDef::VIEW_TIMESHEETS)){
        editorTimesheetWidget *etw = new editorTimesheetWidget();
        etw->initDB(client);
        etw->init(loginCredo, client);
        tabs->addTab(etw, "Editor Timesheet");
    }

    if(loginCredo->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PermissionDef::EDIT_TIMESHEETS)
            ||loginCredo->hasPermission(PermissionDef::VIEW_TIMESHEETS)){
        writerTimesheetWidget *wtw = new writerTimesheetWidget();
        wtw->initDB(client);
        wtw->init(this, loginCredo, client);
        tabs->addTab(wtw, "Writer Timesheet");
    }

    if(loginCredo->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PermissionDef::EDIT_CIRCULATIONS)
            ||loginCredo->hasPermission(PermissionDef::VIEW_CIRCULATIONS)){

        circulationWidget* circWidg = new circulationWidget(this,loginCredo);

        if(loginCredo->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PermissionDef::EDIT_CIRCULATIONS)){
            circWidg->init_ViewAndEditPrivileges(client);
        } else{
            circWidg->init_ViewPrivileges(client);
        }
        tabs->addTab(circWidg, "Circulations");
    }

    if(loginCredo->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PermissionDef::EDIT_PHOTO)){
        PhotoPoolWindow* ppw = new PhotoPoolWindow();
        ppw->init(client);
        tabs->addTab(ppw, "Photo Pool");
    }

    if(loginCredo->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||loginCredo->hasPermission(PermissionDef::VIEW_PERMISSIONS)){

        PermissionsWidget* pemWidg = new PermissionsWidget(this);
        pemWidg->initDB(client);

        tabs->addTab(pemWidg, "Permissions");
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
