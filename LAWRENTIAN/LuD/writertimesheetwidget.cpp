#include "writertimesheetwidget.h"
#include "ui_writertimesheetwidget.h"

writerTimesheetWidget::writerTimesheetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::writerTimesheetWidget)
{
    ui->setupUi(this);
}

writerTimesheetWidget::~writerTimesheetWidget()
{
    delete ui;
}
