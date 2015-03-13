#include "adwidget.h"
#include "ui_adwidget.h"

adWidget::adWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adWidget)
{
    ui->setupUi(this);
}

adWidget::~adWidget()
{
    delete ui;
}
