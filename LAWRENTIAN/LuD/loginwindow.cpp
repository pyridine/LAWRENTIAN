#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <iostream>
#include "registrationwindow.h"
#include <qwindow>
#include "loginwindowdbcontroller.h"
#include "qmessagebox.h"

using namespace std;

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    cout << "Hi, I am LOGINWINDOW." << endl;
    ui->setupUi(this);

    LoginWindowDBController lwdbc;
    dbController = &lwdbc;
}


void LoginWindow::initDB(const Client* cp){
    dbController->init(cp);
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
    w->initDB(LoginWindow::dbController->getClient());
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
            cout << "luid is " << luid << endl;
            if(luid != -1)
            {
                if(dbController->isApproved(luid))
                {
                    showAlert("Well then","Haven't coded this part yet...");
                    //TODO: Create the login credentials and open the main screen.


                }
                else
                {
                    showAlert("Error","Your registration has not yet been approved. Please contact your employee manager for assistance.");
                }
            }
            else
            {
                showAlert("Error","That username/password combination does not exist. \n Please check your spelling.");
            }
        }
        else
        {
            showAlert("Error","Password cannot be blank.");
        }
    }
    else
    {
        showAlert("Error","Username cannot be blank.");
    }
}


void LoginWindow::showAlert(const string& title,const string& msg)
{
    QMessageBox alertBox;
    QString t = QString::fromUtf8(title.c_str());
    QString m = QString::fromUtf8(msg.c_str());
    alertBox.critical(0, t,m);
    alertBox.setFixedSize(500,200);
}

