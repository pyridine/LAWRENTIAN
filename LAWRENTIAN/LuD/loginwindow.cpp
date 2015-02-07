#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <iostream>

using namespace std;

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    cout << "Hi, I am LOGINWINDOW." << endl;
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
