#include "writertimesheetwidget.h"
#include "ui_writertimesheetwidget.h"

#include "alert.h"
#include <iostream>

writerTimesheetWidget::writerTimesheetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::writerTimesheetWidget)
{
    ui->setupUi(this);
}

void writerTimesheetWidget::init(LoginCredentials* l, Client *c){
    loginCred = l;
    this->client = c;
}

void writerTimesheetWidget::initDB(Client *c){
    writerTimesheetDBC = new WriterTimesheetDBC(c);
}

writerTimesheetWidget::~writerTimesheetWidget()
{
    delete ui;
}

void writerTimesheetWidget::on_updateWriterTimesheetButton_clicked()
{
    QDate currentDate = QDate::currentDate();
    vector<int> writerIds = writerTimesheetDBC->collectWriterForTimesheet(currentDate);
    int alreadyExists = writerTimesheetDBC->writerTimesheetExists(currentDate);
    if(writerIds.size()>0 && alreadyExists>0){
        writerTimesheetDBC->deleteWriterTimesheetRecords(currentDate);

        for(int i = 0; i<writerIds.size(); i++){
            int articlesOnTime = writerTimesheetDBC->collectArticlesOnTime(writerIds[i], currentDate);
            int articlesLate = writerTimesheetDBC->collectArticlesLate(writerIds[i], currentDate);
            writerTimesheetDBC->generateWriterTimesheet(writerIds[i], articlesOnTime, articlesLate, currentDate);
        }
        Alert *alert = new Alert;
        alert->showInformationAlert("Updated!", "Writer Timesheet successfully updated");
    }
}
