#include "editortimesheetwidget.h"
#include "ui_editortimesheetwidget.h"
#include "client.h"

#include "alert.h"

editorTimesheetWidget::editorTimesheetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editorTimesheetWidget)
{
    ui->setupUi(this);
}

void editorTimesheetWidget::init(LoginCredentials* l, Client *c){
    loginCred = l;
    this->client = c;
    ui->currentIssueDate->setDate(QDate::currentDate());
    initTable(QDate::currentDate());
}

void editorTimesheetWidget::initDB(Client *c){
    editorTimesheetDBC = new EditorTimesheetDBC(c);
}

void editorTimesheetWidget::initTable(QDate date)
{
    int NUMBEROFCOLUMNS = 3;
    int NUMBEROFROWS = editorTimesheetDBC->collectEditorForTimesheet(date).size();

    vector<vector<string>>* result_matrix = editorTimesheetDBC->getTimesheet(date);
    ui->editorTimesheetTable->setRowCount(NUMBEROFROWS);
    ui->editorTimesheetTable->setColumnCount(NUMBEROFCOLUMNS); //notice! hardcoded!

    ui->editorTimesheetTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Editor"));
    ui->editorTimesheetTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Hours"));
    ui->editorTimesheetTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Issue date"));

    vector<vector<string>>::iterator writerIt = result_matrix->begin();
    for(int i = 0; i < NUMBEROFROWS; ++i){
        vector<string> nextWriter = *writerIt;
        vector<string>::iterator empDataIt = nextWriter.begin();
        for(int z = 0; z < NUMBEROFCOLUMNS; z++){
            string nextItem = *empDataIt;
            ui->editorTimesheetTable->setItem(i,z,new QTableWidgetItem((nextItem.c_str())));
            ++empDataIt;
        }
        ++writerIt;
    }
}

editorTimesheetWidget::~editorTimesheetWidget()
{
    delete ui;
}

void editorTimesheetWidget::on_submitChangesButton_clicked()
{
    Alert *alert = new Alert;
    int ret = alert->showQuestionAlert("Submit Changes", "Are you sure you want to submit changes?");
    switch(ret){
    case QMessageBox::Save:
    {
        int LUID = loginCred->getLUID();
        QDate chosenDate = ui->currentIssueDate->date();
        int hoursWorked = ui->hoursWorkedTextEdit->text().toInt();
        editorTimesheetDBC->setHoursWorked(LUID, chosenDate, hoursWorked);

        initTable(chosenDate);
        Alert *confirm = new Alert;
        confirm->showInformationAlert("Updated Successfully", "Hours updated successfully!");
        break;
    }
    case QMessageBox::Cancel:
        break;
    }
}

void editorTimesheetWidget::on_currentIssueDate_userDateChanged(const QDate &date)
{
    int LUID = loginCred->getLUID();
    QDate chosenDate = ui->currentIssueDate->date();
    int hours = editorTimesheetDBC->getHoursWorked(LUID, chosenDate);
    if(hours == NULL){
        hours = 0;
        QString hoursString = QString::number(hours);
        ui->hoursWorkedTextEdit->setText(hoursString);
    } else{
    QString hoursString = QString::number(hours);
    ui->hoursWorkedTextEdit->setText(hoursString);
    }
    initTable(chosenDate);
}
