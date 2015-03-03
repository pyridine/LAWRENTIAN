#include "permissionswidget.h"
#include "ui_permissionswidget.h"
#define thurd third //I am an idiot but I will not admit it
#include <iostream>
#include <tuple>
#include <utility>
#include "QVariant"
#include <QListWidgetItem>

using namespace std;
PermissionsWidget::PermissionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PermissionsWidget)
{
    ui->setupUi(this);
    QLISTWIDGET_FREEDATA = 32;
}

void PermissionsWidget::initDB(Client* c){
    dbController = new PermissionsWidgetDBC(c);

    updateEmployeeList();
}

void PermissionsWidget::updateEmployeeList(){

    ui->employeeCombobox->clear();

    vector<std::tuple<int, string, int> *>* employees = dbController->getEmployees();
    for(int i = 0; i < employees->size(); i++){
        pair<int/*luid*/,int/*title*/>* employeePair = new pair<int,int>();
        employeePair->first = std::get<0>(*(employees->at(i))); //This weird syntax is how you access tuples ¯\_(ツ)_/¯
        employeePair->second = std::get<2>(*(employees->at(i)));
        QPoint* kludge = new QPoint(employeePair->first,employeePair->second); //Kludge alert
        this->ui->employeeCombobox->addItem(QString::fromStdString(std::get<1>(*(employees->at(i)))),QVariant::fromValue(*kludge)); //Are your eyes glazing over yet?
    }
    cout << "Here, you need to reset the permissions view thing." << endl;

}

PermissionsWidget::~PermissionsWidget()
{
    delete ui;
}

void PermissionsWidget::on_employeeCombobox_currentIndexChanged(int index)
{
    this->ui->permissionList->clear();
    if(index >= 0 && ui->employeeCombobox->count() >= 1){
        QPoint data = ui->employeeCombobox->currentData().toPoint();
        int empID = getSelectedEmployee_ID();
        int empTitle = getSelectedEmployee_TitleID();
        vector<int>* exceptionTokens = dbController->getEmployeePermissions(empID);
        vector<int>* titlePTokens = dbController->getTitlePermissions(empTitle);

        this->ui->titlegoeshere->setText(QString::fromStdString(dbController->translateTitle(empTitle)));


        //Add exception tokens
        for(int i = 0; i <exceptionTokens->size(); i++){
            int nextPerm = exceptionTokens->operator [](i);
            QListWidgetItem* qlite = new QListWidgetItem(QString::fromStdString(dbController->translatePermission(nextPerm)));
            qlite->setData(QLISTWIDGET_FREEDATA/*Not used by Qt*/,nextPerm);
            qlite->setForeground(Qt::red);
            ui->permissionList->addItem(qlite);
        }
        //Add title tokens
        for(int i = 0; i <titlePTokens->size(); i++){
            int nextPerm = titlePTokens->operator [](i);
            QListWidgetItem* qlite = new QListWidgetItem(QString::fromStdString(dbController->translatePermission(nextPerm)));
            qlite->setData(QLISTWIDGET_FREEDATA/*Not used by Qt*/,nextPerm);
            qlite->setForeground(Qt::black);
            ui->permissionList->addItem(qlite);
        }


    }
}

int PermissionsWidget::getSelectedPermissionToken(){
    return ui->permissionList->currentItem()->data(QLISTWIDGET_FREEDATA).toInt();
}
int PermissionsWidget::getSelectedEmployee_ID(){
    QPoint data = ui->employeeCombobox->currentData().toPoint();
    return data.x(); //I know, this is such a kludge...
}
int PermissionsWidget::getSelectedEmployee_TitleID(){
    QPoint data = ui->employeeCombobox->currentData().toPoint();
    return data.y(); //I know, this is such a kludge...
}




void PermissionsWidget::on_permissionList_currentRowChanged(int currentRow)
{
    ui->permissiondescription->width();
    if(currentRow >= 0 && ui->permissionList->count() >= 1){
        int selectedPermID = getSelectedPermissionToken();
        ui->permissiondescription->setText(QString::fromStdString(dbController->translatePermission_long(selectedPermID)));

    }
}
