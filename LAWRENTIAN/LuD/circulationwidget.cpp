#include "circulationwidget.h"
#include "ui_circulationwidget.h"

circulationWidget::circulationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::circulationWidget)
{
    ui->setupUi(this);
}

circulationWidget::~circulationWidget()
{
    delete ui;
}
