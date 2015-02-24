#include "editemployeeinfo.h"
#include "ui_editemployeeinfo.h"

#include <QStringList>
#include <iostream>

EditEmployeeInfo::EditEmployeeInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditEmployeeInfo)
{
    ui->setupUi(this);
    ui->approvedComboBox->addItem("No");
    ui->approvedComboBox->addItem("Yes");
}

void EditEmployeeInfo::initDB(Client *c){
    editEmployeeInfoDBC = new EditEmployeeInfoDBC(c);
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
    updateAllFields();
}

void EditEmployeeInfo::updateAllFields()
{
    string selectedName = ui->nameComboBox->currentText().toStdString();
    size_t approvedExists = selectedName.find(" [UNAPPROVED]");
    if(approvedExists != string::npos){
        cout<<"Found unapproved!"<<endl;
        cout<<selectedName<<endl;
        selectedName.erase(selectedName.find(" [UNAPPROVED]"), selectedName.size());
    }

    int approved = editEmployeeInfoDBC->collectApproved(selectedName);
    if(approved == 0)
    {
        ui->approvedComboBox->setCurrentIndex(0);
    } else {
        ui->approvedComboBox->setCurrentIndex(1);
    }

    int employeeID = editEmployeeInfoDBC->collectLuid(selectedName);
    ui->luidTextField->setText(QString::number(employeeID));

    string title = editEmployeeInfoDBC->collectTitle(selectedName);
    ui->titleTextField->setText(QString::fromStdString(title));

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
    string selectedName = ui->nameComboBox->currentText().toStdString();
    string oldName = selectedName;
    size_t approvedExists = selectedName.find(" [UNAPPROVED]");
    if(approvedExists != string::npos){
        selectedName.erase(selectedName.find(" [UNAPPROVED]"), selectedName.size());
    }

    int luid = ui->luidTextField->text().toInt();
    string title = ui->titleTextField->text().toStdString();
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
    editEmployeeInfoDBC->saveEmployeeChanges(oldName, selectedName, luid, title, email, phone, approvedInt);
    if(approvedInt == 1){
        ui->nameComboBox->setItemText(index, QString::fromStdString(selectedName));
    }
}

void EditEmployeeInfo::on_pushButton_2_clicked()
{
    this->close();
}
