#include "editortimesheetwidget.h"
#include "ui_editortimesheetwidget.h"

editorTimesheetWidget::editorTimesheetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editorTimesheetWidget)
{
    ui->setupUi(this);
}

editorTimesheetWidget::~editorTimesheetWidget()
{
    delete ui;
}
