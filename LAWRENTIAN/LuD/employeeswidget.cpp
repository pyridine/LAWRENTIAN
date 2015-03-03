#include "employeeswidget.h"
#include "ui_employeeswidget.h"
#include "employeetabledbc.h"
#include "client.h"
#include "QTableWidgetItem"
#include "PermissionDef.h"
#include "permissions.h"
#include "editemployeeinfo.h"
#include <iostream>

using namespace std;
employeesWidget::employeesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::employeesWidget)
{
    ui->setupUi(this);
}

void employeesWidget::init(LoginCredentials* l){
    loginCred = l;

    handlePermissions();
}

void employeesWidget::handlePermissions(){

    if(!loginCred->hasPermission(PermissionDef::ADMIN_PTOKEN)
            &&!loginCred->hasPermission(PermissionDef::EDIT_EMPLOYEE_INFO)
            &&!loginCred->hasPermission(PermissionDef::MANAGE_EMPLOYEE_PROBATION)){
        this->ui->approveRegButton->hide();
    }
}

void employeesWidget::initDB(Client *c){
    this->client = c;
    dbController = new EmployeeTableDBC(client);
}

void employeesWidget::initNormalView(){
    viewType=0;
    ui->employeeTable->clear();
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
    viewType=1;
    ui->employeeTable->clear();
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
    viewType=2;
    ui->employeeTable->clear();
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

void employeesWidget::reUpdateTable(){
    if(viewType == 0){
        this->initNormalView();
    }
    if(viewType == 1){
        this->initPrivilegedView();
    }
    if(viewType == 2){
        this->initTotalView();
    }
}

void employeesWidget::on_approveRegButton_clicked()
{
    EditEmployeeInfo* employeeInfo = new EditEmployeeInfo(this,loginCred);
    employeeInfo->initDB(this->client);
    employeeInfo->myParent = this;
    employeeInfo->populateNameComboBox();
    employeeInfo->populateAllFields();
    employeeInfo->show();
}


