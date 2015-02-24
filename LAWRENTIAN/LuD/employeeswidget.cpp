#include "employeeswidget.h"
#include "ui_employeeswidget.h"
#include "employeetabledbc.h"
#include "client.h"
#include "QTableWidgetItem"
#include "PermissionDef.h"
#include "permissions.h"
#include <iostream>

using namespace std;
employeesWidget::employeesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::employeesWidget)
{
    ui->setupUi(this);
    ui->approveRegButton->hide();
}

void employeesWidget::init(LoginCredentials* l){
    loginCred = l;
}
void employeesWidget::initDB(Client *c){
    dbController = new EmployeeTableDBC(c);

}

void employeesWidget::initNormalView(){
    int NUMBEROFCOLUMNS = 5;
    int NUMBEROFROWS = 1+dbController->getNumberOfEmployees();

    vector<vector<string>>* result_matrix = dbController->getRegularEmployeeView();
    ui->employeeTable->setRowCount(NUMBEROFROWS);
    ui->employeeTable->setColumnCount(NUMBEROFCOLUMNS); //notice! hardcoded!


    ui->employeeTable->setItem(0,0, new QTableWidgetItem("luid"));
    ui->employeeTable->setItem(0,1, new QTableWidgetItem("name"));
    ui->employeeTable->setItem(0,2, new QTableWidgetItem("title"));
    ui->employeeTable->setItem(0,3, new QTableWidgetItem("name"));
    ui->employeeTable->setItem(0,4, new QTableWidgetItem("email"));

    vector<vector<string>>::iterator employeeIt = result_matrix->begin();
    for(int i = 1; i < NUMBEROFROWS; ++i){
        vector<string> nextEmployee = *employeeIt;
        vector<string>::iterator empDataIt = nextEmployee.begin();
        for(int z = 0; z < NUMBEROFCOLUMNS; z++){
            string nextItem = *empDataIt;
            ui->employeeTable->setItem(i,z,new QTableWidgetItem((nextItem.c_str())));
            ++empDataIt;
        }
        ++employeeIt;
    }
}

void employeesWidget::initPrivilegedView(){
    int NUMBEROFCOLUMNS = 6;
    int NUMBEROFROWS = 1+dbController->getNumberOfEmployees();

    vector<vector<string>>* result_matrix = dbController->getPrivilegedEmployeeView();
    ui->employeeTable->setRowCount(NUMBEROFROWS);
    ui->employeeTable->setColumnCount(NUMBEROFCOLUMNS); //notice! hardcoded!


    ui->employeeTable->setItem(0,0, new QTableWidgetItem("luid"));
    ui->employeeTable->setItem(0,1, new QTableWidgetItem("name"));
    ui->employeeTable->setItem(0,2, new QTableWidgetItem("title"));
    ui->employeeTable->setItem(0,3, new QTableWidgetItem("name"));
    ui->employeeTable->setItem(0,4, new QTableWidgetItem("email"));
    ui->employeeTable->setItem(0,5, new QTableWidgetItem("approval"));

    vector<vector<string>>::iterator employeeIt = result_matrix->begin();
    for(int i = 1; i < NUMBEROFROWS; ++i){
        vector<string> nextEmployee = *employeeIt;
        vector<string>::iterator empDataIt = nextEmployee.begin();
        for(int z = 0; z < NUMBEROFCOLUMNS; z++){
            string nextItem = *empDataIt;
            ui->employeeTable->setItem(i,z,new QTableWidgetItem((nextItem.c_str())));
            ++empDataIt;
        }
        ++employeeIt;
    }
}

void employeesWidget::initTotalView(){
    int NUMBEROFCOLUMNS = 8;
    int NUMBEROFROWS = 1+dbController->getNumberOfEmployees();

    vector<vector<string>>* result_matrix = dbController->getFullEmployeeView();
    ui->employeeTable->setRowCount(NUMBEROFROWS);
    ui->employeeTable->setColumnCount(NUMBEROFCOLUMNS); //notice! hardcoded!


    ui->employeeTable->setItem(0,0, new QTableWidgetItem("luid"));
    ui->employeeTable->setItem(0,1, new QTableWidgetItem("name"));
    ui->employeeTable->setItem(0,2, new QTableWidgetItem("title"));
    ui->employeeTable->setItem(0,3, new QTableWidgetItem("name"));
    ui->employeeTable->setItem(0,4, new QTableWidgetItem("email"));
    ui->employeeTable->setItem(0,5, new QTableWidgetItem("username"));
    ui->employeeTable->setItem(0,6, new QTableWidgetItem("password"));
    ui->employeeTable->setItem(0,7, new QTableWidgetItem("approval"));

    vector<vector<string>>::iterator employeeIt = result_matrix->begin();
    for(int i = 1; i < NUMBEROFROWS; ++i){
        vector<string> nextEmployee = *employeeIt;
        vector<string>::iterator empDataIt = nextEmployee.begin();
        for(int z = 0; z < NUMBEROFCOLUMNS; z++){
            string nextItem = *empDataIt;
            ui->employeeTable->setItem(i,z,new QTableWidgetItem((nextItem.c_str())));
            ++empDataIt;
        }
        ++employeeIt;
    }
}


employeesWidget::~employeesWidget()
{
    delete ui;
}

void employeesWidget::on_employeeTable_cellClicked(int row, int column)
{
    /*
    int lastColumn = ui->employeeTable->columnCount()-1;

    if(loginCred->hasPermission(int::EDIT_EMPLOYEE_INFO)
            ||loginCred->hasPermission(ADMIN_int)){
        if(ui->employeeTable->takeItem(row,lastColumn)->text().toStdString().compare("no")){
            ui->approveRegButton->show();
        }
    } else{
        ui->approveRegButton->hide();
    }*/
}

int employeesWidget::getNumUnregistered(){
    return dbController->getNumUnregistered();
}
