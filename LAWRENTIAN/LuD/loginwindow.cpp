#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <iostream>
#include "registrationwindow.h"
#include <qwindow>
#include "loginwindowdbc.h"
#include "qmessagebox.h"
#include "alert.h"
#include "permissiondef.h"
#include "logincredentials.h"
#include "mainwindow.h"
#include "titledef.h"
#include "locationdef.h"

using namespace std;

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

}


void LoginWindow::initDB(Client* cp){
    dbController = new LoginWindowDBC(cp);

    cout << "Populating Permissions ids..." << endl;

    PermissionDef::__populateValues(dbController);

    cout << "Done. Permission for view_circ is " << PermissionDef::VIEW_CIRCULATIONS << endl;
    cout << "Populating Title ids..." << endl;

    TitleDef::__populateValues(dbController);

    cout << "Done. Permission for assoc_news_editor is " << TitleDef::ASSOCIATE_NEWS_EDITOR << endl;
    cout << "Populating Location ids..." << endl;

    LocationDef::__populateValues(dbController);

    cout << "Done. id for DELTA is " << LocationDef::DELT << endl;
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_2_clicked()
{
    //You need to use the pointer-new syntax or else Qt immediately closes the window upon opening.
    //This is just the way it works.
    RegistrationWindow *w = new RegistrationWindow();
    w->setWindowModality(Qt::ApplicationModal);
    w->show();
    Client* clientPointer = dbController->getClient();
    w->initDB(clientPointer);
}

void LoginWindow::on_pushButton_clicked()
{
    string sn = ui->usernamebox->text().toStdString();
    string pass = ui->passwordbox->text().toStdString();

    if(sn.begin() != sn.end())
    {
        if(pass.begin() != pass.end())
        {
            int luid = dbController->getLUID(sn,pass);
            if(luid != -1)
            {
                if(dbController->isApproved(luid))
                {


                    LoginCredentials* loginCred = new LoginCredentials();

                    int loginLUID = luid;
                    string realName = dbController->getEmployeeName(loginLUID);
                    vector<int>* employeePermissions = dbController->getEmployeePermissions(loginLUID);
                    vector<int>* titlePermissions = dbController->getEmployeeTitlePermissions(loginLUID);
                    int title = dbController->getEmployeeTitle(loginLUID);

                    //combine the two vectors.
                    for(vector<int>::iterator it = titlePermissions->begin(); it != titlePermissions->end(); it++){
                        employeePermissions->push_back(*it);
                    }
                    Permissions* finalPermissions = new Permissions(employeePermissions);

                    loginCred->setID(loginLUID);
                    loginCred->setName(realName);
                    loginCred->setPermissions(finalPermissions);
                    loginCred->setTitle(title);

                    cout << "< NEW LOGIN." << endl;
                    cout << "Permissions: " << endl;
                    vector<int>::iterator pit = employeePermissions->begin();

                    while(pit != employeePermissions->end()){
                        cout << dbController->translatePermission(static_cast<int>(*pit)) << ", ";
                        ++pit;
                    }

                    cout << endl;
                    cout << "Real name: " << loginCred->getName().toStdString() << endl;
                    cout << "Lawrence ID: " << loginCred->getLUID() << endl;
                    cout << "Title: " << dbController->translateTitle(loginCred->getTitle()) << endl;

                    cout << ">" << endl;
                    MainWindow* m = new MainWindow();
                    //initDB and THEN init. it MUST be in this order!!!!
                    m->initDB(dbController->getClient());
                    m->init(this,loginCred);
                    ui->usernamebox->setText("");
                    ui->passwordbox->setText("");
                    this->hide();
                    m->show();
                }
                else
                {
                    Alert::showAlert("Error","Your registration has not yet been approved. Please contact your employee manager for assistance.");
                }
            }
            else
            {
                Alert::showAlert("Error","That username/password combination does not exist. \n Please check your spelling.");
            }
        }
        else
        {
            Alert::showAlert("Error","Password cannot be blank.");
        }
    }
    else
    {
        Alert::showAlert("Error","Username cannot be blank.");
    }
}


void LoginWindow::on_pushButton_3_clicked()
{
    dbController->__DEBUG__POPULATE_TITLE_PERMISSIONS();
}
