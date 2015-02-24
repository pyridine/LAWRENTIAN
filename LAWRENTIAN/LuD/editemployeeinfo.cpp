#include "editemployeeinfo.h"
#include "ui_editemployeeinfo.h"

EditEmployeeInfo::EditEmployeeInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditEmployeeInfo)
{
    ui->setupUi(this);
}

EditEmployeeInfo::~EditEmployeeInfo()
{
    delete ui;
}
