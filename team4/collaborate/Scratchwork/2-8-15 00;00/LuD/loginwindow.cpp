#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <iostream>
#include "registrationwindow.h"
#include <qwindow>
#include "loginwindowdbcontroller.h"

using namespace std;

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    cout << "Hi, I am LOGINWINDOW." << endl;
    ui->setupUi(this);

    LoginWindowDBController lwdbc;
    LoginWindow::dbController = &lwdbc;
}


void LoginWindow::initDB(Client* cp){
    LoginWindow::dbController->init(cp);
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
