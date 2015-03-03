#include "writertimesheetwidget.h"
#include "ui_writertimesheetwidget.h"

#include "alert.h"
#include <iostream>
#include "Sender.h"
#include "FileSystem.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTableView>
#include <QMetaType>
#include <QThread>

writerTimesheetWidget::writerTimesheetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::writerTimesheetWidget)
{
    ui->setupUi(this);
}

void writerTimesheetWidget::init(MainWindow* parent, LoginCredentials* l, Client *c){
    loginCred = l;
    this->client = c;
    parentWindow = parent;
    updateWriterTimesheet();
}

void writerTimesheetWidget::initDB(Client *c){
    writerTimesheetDBC = new WriterTimesheetDBC(c);
}

void writerTimesheetWidget::initTable()
{
    QDate currentDate = QDate::currentDate();
    int NUMBEROFCOLUMNS = 4;
    int NUMBEROFROWS = writerTimesheetDBC->collectWriterForTimesheet(currentDate).size();

    vector<vector<string>>* result_matrix = writerTimesheetDBC->getTimesheet(currentDate);
    ui->writerTimesheetTable->setRowCount(NUMBEROFROWS);
    ui->writerTimesheetTable->setColumnCount(NUMBEROFCOLUMNS); //notice! hardcoded!

    ui->writerTimesheetTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->writerTimesheetTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Articles on time"));
    ui->writerTimesheetTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Articles late"));
    ui->writerTimesheetTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Issue date"));

    vector<vector<string>>::iterator writerIt = result_matrix->begin();
    for(int i = 0; i < NUMBEROFROWS; ++i){
        vector<string> nextWriter = *writerIt;
        vector<string>::iterator empDataIt = nextWriter.begin();
        for(int z = 0; z < NUMBEROFCOLUMNS; z++){
            string nextItem = *empDataIt;
            ui->writerTimesheetTable->setItem(i,z,new QTableWidgetItem((nextItem.c_str())));
            ++empDataIt;
        }
        ++writerIt;
    }
}

pair<int, int> writerTimesheetWidget::calculateArticlesOnTimeAndLate(QDate issueDate, int writerId)
{
    pair<int, int> articlesOnTimeAndLate;
    int articlesOnTime = 0;
    int articlesLate = 0;
    QDate deadline = issueDate.addDays(-3);

    QString issueDateQString = issueDate.toString("yyyy-MM-dd");
    string issueDateString = issueDateQString.toStdString();
    Sender *sndr = new Sender;
    vector<int> articleIds = writerTimesheetDBC->collectArticleIdForTimesheet(issueDate, writerId);
    for(int i = 0; i < articleIds.size(); i++){
        string sectionName = writerTimesheetDBC->collectArticleSection(articleIds[i]);
        string articleName = writerTimesheetDBC->collectArticleTitle(articleIds[i]);
        FileSystem::VerSeq versions;
        versions = sndr->getHistory(issueDateString, sectionName, articleName, fs::COPY);

        // Reads in first submitted file (assumed its submitted by writer)
        if(versions.size()>0){
            FileSystem::TimeIce submissionTime = versions[0].time;
            QDate submissionDate;
            submissionDate.setDate(submissionTime.year, submissionTime.month, submissionTime.day);

            if(submissionDate <= deadline){
                articlesOnTime++;
            } else {
                articlesLate++;
            }
        }
    }
    articlesOnTimeAndLate = make_pair (articlesOnTime, articlesLate);
    return articlesOnTimeAndLate;
}

void writerTimesheetWidget::updateWriterTimesheet()
{
    QDate currentDate = QDate::currentDate();
    vector<int> writerIds = writerTimesheetDBC->collectWriterForTimesheet(currentDate);
    int alreadyExists = writerTimesheetDBC->writerTimesheetExists(currentDate);
    if(alreadyExists>0){
        if(writerIds.size()>0 && alreadyExists>0){
            writerTimesheetDBC->deleteWriterTimesheetRecords(currentDate);
            for(int i = 0; i<writerIds.size(); i++){
                pair<int, int> articleSubmission = calculateArticlesOnTimeAndLate(currentDate, writerIds[i]);
                writerTimesheetDBC->generateWriterTimesheet(writerIds[i], articleSubmission.first, articleSubmission.second, currentDate);
            }
        }
        initTable();
        Alert *alert = new Alert;
        alert->showInformationAlert("Updated!", "Writer Timesheet successfully updated");
    } else {
        //Alert *alert = new Alert;
        //alert->showInformationAlert("Update", "Nothing to update");
    }
}

writerTimesheetWidget::~writerTimesheetWidget()
{
    delete ui;
}

void writerTimesheetWidget::on_updateWriterTimesheetButton_clicked()
{
    updateWriterTimesheet();
}
