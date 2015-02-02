#include "checkemployeeswindow.h"
#include "ui_checkemployeeswindow.h"

#include <QMessageBox>

CheckEmployeesWindow::CheckEmployeesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckEmployeesWindow)
{
    ui->setupUi(this);
}

CheckEmployeesWindow::~CheckEmployeesWindow()
{
    delete ui;
}

// Used to pass in the employee vector
void CheckEmployeesWindow::initCheckEmployeesWindow(vector<Employee> employeeVector)
{
    CheckEmployeesWindow::employeeVector = employeeVector;
    employeeCount = 0;
    CheckEmployeesWindow::iterateThroughEmployees(employeeCount);
    employeeCount++;
}

void CheckEmployeesWindow::iterateThroughEmployees(int employeeCount)
{
    string name = employeeVector[employeeCount].getName();
    QString nameQstring = QString::fromStdString(name);
    ui->nameTextField->setText(nameQstring);

    string luId = employeeVector[employeeCount].getLuId();
    QString luIdQstring = QString::fromStdString(luId);
    ui->luIdTextField->setText(luIdQstring);

    string email = employeeVector[employeeCount].getEmail();
    QString emailQstring = QString::fromStdString(email);
    ui->emailTextField->setText(emailQstring);

    string phone = employeeVector[employeeCount].getPhoneNumber();
    QString phoneQstring = QString::fromStdString(phone);
    ui->phoneTextField->setText(phoneQstring);

    string username = employeeVector[employeeCount].getUsername();
    QString usernameQstring = QString::fromStdString(username);
    ui->usernameTextField->setText(usernameQstring);
}

void CheckEmployeesWindow::on_pushButton_clicked()
{
    if(employeeCount < employeeVector.size()){
    CheckEmployeesWindow::iterateThroughEmployees(employeeCount);
    employeeCount++;
    } else
    {
        QMessageBox alertBox;
        alertBox.critical(0, "Error", "No More Employees Available");
        alertBox.setFixedSize(500,200);
    }
}
