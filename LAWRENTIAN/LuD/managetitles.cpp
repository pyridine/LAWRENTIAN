#include "managetitles.h"
#include "ui_managetitles.h"
#include <iostream>

using namespace std;

ManageTitles::ManageTitles(QWidget *Mparent, bool wantTitleEdit, int meId) :
    QDialog(Mparent),
    ui(new Ui::ManageTitles)
{
    ui->setupUi(this);
    isTitle = wantTitleEdit;
    editeeID = meId;
    parent = static_cast<PermissionsWidget*>(Mparent);
    QLISTWIDGET_FREEDATA = 32;
}

ManageTitles::~ManageTitles()
{
    delete ui;
}

void ManageTitles::initDB_LOL(PermissionsWidgetDBC* d){
    dbController = d;

    if(isTitle){
        this->ui->employeeIdentifier->hide();
    } else{
        this->ui->titleComboBox->hide();
        this->ui->employeeIdentifier->setText(QString::fromStdString(dbController->translateEmployee(editeeID)));
    }

    getPermissions();
    populateTitleComboBox();
    if(!isTitle)getEditeePermissions(); //title permissions are fetched when the combobox is changed.
}

void ManageTitles::on_cancelButton_clicked()
{
    this->hide();
    this->close();
    delete(this);

}

void ManageTitles::on_applyButton_clicked()
{
    applyChangesToDatabase();
    parent->resetEmployeeCombobox();
    parent->updatePermissionView();
    this->hide();
    this->close();
    delete(this);

}

void ManageTitles::getPermissions(){
    vector<int>* perms = dbController->getAllPermissions();
    vector<int>::iterator permit = perms->begin();
    while(permit != perms->end()){
        QListWidgetItem* qlite = new QListWidgetItem(QString::fromStdString(dbController->translatePermission(*permit)));
        qlite->setData(QLISTWIDGET_FREEDATA/*Not used by Qt*/,*permit);
        ui->allPermissions->addItem(qlite);
        permit++; //why do I always forget this!!
    }
}

void ManageTitles::getEditeePermissions(){
    vector<int>* permissions;

    if(isTitle){
        permissions = dbController->getTitlePermissions(editeeID);
    } else{
        permissions = dbController->getEmployeePermissions(editeeID);
    }
    vector<int>::iterator permit = permissions->begin();
    while(permit != permissions->end()){
        QListWidgetItem* qlite = new QListWidgetItem(QString::fromStdString(dbController->translatePermission(*permit)));
        qlite->setData(QLISTWIDGET_FREEDATA/*Not used by Qt*/,*permit);
        ui->containedPermissions->addItem(qlite);
        permit++; //argh!
    }
}

void ManageTitles::applyChangesToDatabase(){
    if(isTitle){
        dbController->dropAllPermission_Title(editeeID);
        for(int i = 0; i < ui->containedPermissions->count();i++){
            ui->containedPermissions->setCurrentRow(i);
            dbController->addPermission_title(editeeID,this->getSelectedEiteePermissionToken());
        }
    }else{
        dbController->dropAllPermission_Employee(editeeID);
        for(int i = 0; i < ui->containedPermissions->count();i++){
            ui->containedPermissions->setCurrentRow(i);
            dbController->addPermission_employee(editeeID,this->getSelectedEiteePermissionToken());
        }
    }
    return;
}

int ManageTitles::getSelectedPermissionPoolToken(){
    return ui->allPermissions->currentItem()->data(QLISTWIDGET_FREEDATA).toInt();
}

int ManageTitles::getSelectedEiteePermissionToken(){
    return ui->containedPermissions->currentItem()->data(QLISTWIDGET_FREEDATA).toInt();
}

void ManageTitles::on_allPermissions_currentRowChanged(int currentRow)
{
    if(currentRow >= 0 && ui->allPermissions->count() >= 1){
        int selectedPermID = getSelectedPermissionPoolToken();
        ui->permissiondescgoeshere->setText(QString::fromStdString(dbController->translatePermission_long(selectedPermID)));

    }
}

void ManageTitles::populateTitleComboBox(){
    vector<int>* tots = dbController->getTitles();
    vector<int>::iterator it = tots->begin();

    while(it != tots->end()){
        ui->titleComboBox->addItem(
                    QString::fromStdString(dbController->translateTitle(*it)),
                    QVariant(*it));
        it++;
    }
}

void ManageTitles::on_titleComboBox_currentIndexChanged(int index)
{
    if(index >= 0){
        this->ui->containedPermissions->clear();
        if(isTitle){
            editeeID = ui->titleComboBox->currentData().toInt();
            getEditeePermissions();
        }
    }
}

void ManageTitles::on_allPermissions_itemDoubleClicked(QListWidgetItem *item)
{
    int gotch = item->data(QLISTWIDGET_FREEDATA).toInt();
    tryAddPermission(gotch);
}
void ManageTitles::tryAddPermission(int a){
    for(int i = 0; i < ui->containedPermissions->count();i++){
        if(ui->containedPermissions->item(i)->data(QLISTWIDGET_FREEDATA).toInt() == a){
            return;
        }
    }
    QListWidgetItem* qlite = new QListWidgetItem(QString::fromStdString(dbController->translatePermission(a)));
    qlite->setData(QLISTWIDGET_FREEDATA/*Not used by Qt*/,a);
    ui->containedPermissions->addItem(qlite);

}

void ManageTitles::on_containedPermissions_itemDoubleClicked(QListWidgetItem *item)
{
    ui->containedPermissions->takeItem(ui->containedPermissions->currentRow());
}
