#include "editemployeeinfo.h"
#include "ui_editemployeeinfo.h"
#include "employeeswidget.h"
#include <QStringList>
#include <iostream>
#include "alert.h"

EditEmployeeInfo::EditEmployeeInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditEmployeeInfo)
{
    ui->setupUi(this);

}

void EditEmployeeInfo::init(LoginCredentials *c, employeesWidget *parent)
{
    login = c;
    //parentYay = static_cast<employeesWidget*>(parent);
    parentYay = parent;
    handlePermissions();
}

void EditEmployeeInfo::handlePermissions(){
    if(!login->hasPermission(PermissionDef::ADMIN_PTOKEN)
            &&!login->hasPermission(PermissionDef::MANAGE_EMPLOYEE_PROBATION))
    {
        ui->probationComboBox->setEnabled(false);
    }
    if(!login->hasPermission(PermissionDef::ADMIN_PTOKEN)
            &&!login->hasPermission(PermissionDef::EDIT_EMPLOYEE_INFO)){
        ui->approvedComboBox->setEnabled(false);
        ui->emailTextField->setEnabled(false);
        ui->luidTextField->setEnabled(false);
        ui->phoneTextField->setEnabled(false);
        ui->probationStartDate->setEnabled(false);
        ui->titleComboBaucks->setEnabled(false);
    }
}

void EditEmployeeInfo::initDB(Client *c){
    editEmployeeInfoDBC = new EditEmployeeInfoDBC(c);


    //Populate combobox.
    //Yeah, it's not in the right method.
    //Fuckin' sue me.
    vector<int>* tots = editEmployeeInfoDBC->getAllTitles();
    vector<int>::iterator it = tots->begin();

    while(it != tots->end()){
        ui->titleComboBaucks->addItem(
                    QString::fromStdString(editEmployeeInfoDBC->translateTitle(*it)),
                    QVariant(*it));
        it++;
    }

}

void EditEmployeeInfo::initSelectedNameProbation(QString selectedName)
{
    populateNameComboBox();
    populateAllFields();
    ui->nameComboBox->setCurrentText(selectedName);
    ui->nameComboBox->setEnabled(false);
    ui->luidTextField->setEnabled(false);
    ui->phoneTextField->setEnabled(false);
    ui->emailTextField->setEnabled(false);
    ui->approvedComboBox->setEnabled(false);
    ui->titleComboBaucks->setEnabled(false);
    updateAllFields();
}

void EditEmployeeInfo::initSelectedNameApproval(QString selectedName)
{
    populateNameComboBox();
    populateAllFields();
    ui->nameComboBox->setCurrentText(selectedName+" [UNAPPROVED]");
    ui->nameComboBox->setEnabled(false);
    ui->luidTextField->setEnabled(false);
    ui->phoneTextField->setEnabled(false);
    ui->emailTextField->setEnabled(false);
    ui->approvedComboBox->setEnabled(true);
    ui->titleComboBaucks->setEnabled(true);
    ui->probationComboBox->setEnabled(false);
    ui->probationStartDate->setEnabled(false);
    updateAllFields();
}

void EditEmployeeInfo::populateNameComboBox()
{
    ui->nameComboBox->setEditable(true);
    vector<string> namesList;
    namesList = editEmployeeInfoDBC->collectRegisteredNames();
    for (int i = 0; i < namesList.size(); i++){
        int approved = editEmployeeInfoDBC->collectApproved(namesList[i]);
        if(approved == 0){
            string name = namesList[i];
            string concatName = name+" [UNAPPROVED]";
            ui->nameComboBox->addItem(QString::fromStdString(concatName));
        } else{
            ui->nameComboBox->addItem(QString::fromStdString(namesList[i]));
        }

    }
}

void EditEmployeeInfo::populateAllFields()
{
    ui->approvedComboBox->addItem("No");
    ui->approvedComboBox->addItem("Yes");
    ui->probationComboBox->addItem("No");
    ui->probationComboBox->addItem("Yes");
    ui->probationStartDate->setDate(QDate::currentDate());
    updateAllFields();
}

void EditEmployeeInfo::updateAllFields()
{
    string selectedName = ui->nameComboBox->currentText().toStdString();
    size_t approvedExists = selectedName.find(" [UNAPPROVED]");
    if(approvedExists != string::npos){
        selectedName.erase(selectedName.find(" [UNAPPROVED]"), selectedName.size());
    }

    int approved = editEmployeeInfoDBC->collectApproved(selectedName);
    if(approved == 0)
    {
        ui->approvedComboBox->setCurrentIndex(0);
    } else {
        ui->approvedComboBox->setCurrentIndex(1);
    }

    string probationDate = editEmployeeInfoDBC->collectProbationDate(selectedName);
    QDate probationDateQDate = QDate::fromString(QString::fromStdString(probationDate), "yyyy-MM-dd");

    if(probationDateQDate.isNull()){
        QDate date;
        date.setDate(2000, 1, 1);
        ui->probationStartDate->setDate(date);
        ui->probationStartDate->setEnabled(false);
        ui->probationComboBox->setCurrentIndex(0);
    } else {
        ui->probationComboBox->setCurrentIndex(1);
        ui->probationStartDate->setDate(probationDateQDate);
        ui->probationStartDate->setEnabled(true);
    }

    int employeeID = editEmployeeInfoDBC->collectLuid(selectedName);
    ui->luidTextField->setText(QString::number(employeeID));

    int titleID = editEmployeeInfoDBC->getEmployeeTitle(employeeID);

    //Set title combo box.
    for(int i = 0; i < ui->titleComboBaucks->count(); i++){
        ui->titleComboBaucks->setCurrentIndex(i);
        if(ui->titleComboBaucks->currentData().toInt() == titleID){
            i = ui->titleComboBaucks->count(); //Super dumb loop break lol
        }
    }

    string phone = editEmployeeInfoDBC->collectPhone(selectedName);
    ui->phoneTextField->setText(QString::fromStdString(phone));

    string email = editEmployeeInfoDBC->collectEmail(selectedName);
    ui->emailTextField->setText(QString::fromStdString(email));
}

EditEmployeeInfo::~EditEmployeeInfo()
{
    delete ui;
}

void EditEmployeeInfo::on_nameComboBox_currentIndexChanged(int index)
{
    updateAllFields();
}

void EditEmployeeInfo::on_pushButton_clicked()
{
    Alert proceed;
    int ret = proceed.showQuestionAlert("Update Employee Info", "Are you sure you want to save changes?");
    switch(ret){
    case QMessageBox::Save:
    {
        string selectedName = ui->nameComboBox->currentText().toStdString();
        string oldName = selectedName;
        size_t approvedExists = selectedName.find(" [UNAPPROVED]");
        if(approvedExists != string::npos){
            selectedName.erase(selectedName.find(" [UNAPPROVED]"), selectedName.size());
        }

        int luid = ui->luidTextField->text().toInt();
        //string title = ui->titleTextField->text().toStdString();
        editEmployeeInfoDBC->updateEmployeeTitle(luid,ui->titleComboBaucks->currentData().toInt());
        string email = ui->emailTextField->text().toStdString();
        string phone = ui->phoneTextField->text().toStdString();
        string approved = ui->approvedComboBox->currentText().toStdString();
        int approvedInt;
        int index = ui->nameComboBox->currentIndex();
        if(approved == "Yes"){
            approvedInt = 1;
        } else {
            approvedInt = 0;
            // Checks if " [UNAPPROVED]" is not in the name
            if(selectedName.find(" [UNAPPROVED]") == string::npos){
                // Adds " [UNAPPROVED]"
                string concatString = selectedName+" [UNAPPROVED]";
                ui->nameComboBox->setItemText(index, QString::fromStdString(concatString));
            }
        }
        // If put on probation
        if(ui->probationComboBox->currentIndex()==1){
            QDate probationDateQDate = ui->probationStartDate->date();
            string probationDateString = probationDateQDate.toString("yyyy-MM-dd").toStdString();
            cout<<"About to set probationDate to: "<<probationDateString<<endl;
            editEmployeeInfoDBC->saveEmployeeChanges(oldName, selectedName, luid, "title", email, phone, approvedInt, probationDateString);
        }
        // If NOT put on probation
        if(ui->probationComboBox->currentIndex()==0)
        {
            cout<<"About to set probationDate to NULL"<<endl;
            editEmployeeInfoDBC->saveEmployeeChanges(oldName, selectedName, luid, "title", email, phone, approvedInt, "");
        }
        // Updates name if approved
        if(approvedInt == 1){
            ui->nameComboBox->setItemText(index, QString::fromStdString(selectedName));
        }
        break;
    }
    case QMessageBox::Cancel:
        break;
    }
}

void EditEmployeeInfo::on_pushButton_2_clicked()
{
    parentYay->reUpdateTable();
    this->close();
}

void EditEmployeeInfo::on_probationComboBox_currentIndexChanged(int index)
{
    string selectedName = getSelectedName();

    string probationDate = editEmployeeInfoDBC->collectProbationDate(selectedName);
    QDate probationDateQDate = QDate::fromString(QString::fromStdString(probationDate), "yyyy-MM-dd");

    // Checks if wants to put on probation
    if(probationDateQDate.isNull() && ui->probationComboBox->currentIndex()==1){
        ui->probationStartDate->setEnabled(true);
        ui->probationStartDate->setDate(QDate::currentDate());
    }
    if((!probationDateQDate.isNull()) && ui->probationComboBox->currentIndex()==0){
        QDate date;
        date.setDate(2000, 1, 1);
        ui->probationStartDate->setDate(date);
        ui->probationStartDate->setEnabled(false);
    }
    if(probationDateQDate.isNull() && ui->probationComboBox->currentIndex()==0){
        QDate date;
        date.setDate(2000, 1, 1);
        ui->probationStartDate->setDate(date);
        ui->probationStartDate->setEnabled(false);
    }
}

string EditEmployeeInfo::getSelectedName()
{
    string selectedName = ui->nameComboBox->currentText().toStdString();
    size_t approvedExists = selectedName.find(" [UNAPPROVED]");
    if(approvedExists != string::npos){
        selectedName.erase(selectedName.find(" [UNAPPROVED]"), selectedName.size());
    }
    return selectedName;
}
