#include "profilewidget.h"
#include "ui_profilewidget.h"

profileWidget::profileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profileWidget)
{
    ui->setupUi(this);
}

profileWidget::~profileWidget()
{
    delete ui;
}
