#include "subscriptionswidget.h"
#include "ui_subscriptionswidget.h"

subscriptionsWidget::subscriptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subscriptionsWidget)
{
    ui->setupUi(this);
}

subscriptionsWidget::~subscriptionsWidget()
{
    delete ui;
}
