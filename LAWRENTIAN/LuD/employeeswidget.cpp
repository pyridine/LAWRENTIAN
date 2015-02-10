#include "employeeswidget.h"
#include "ui_employeeswidget.h"

employeesWidget::employeesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::employeesWidget)
{
    ui->setupUi(this);
}

employeesWidget::~employeesWidget()
{
    delete ui;
}
