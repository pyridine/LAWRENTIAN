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
    ui->generateTimesheetDate->setDate(QDate::currentDate());
    QDate latestDate = writerTimesheetDBC->collectLatestTimesheetDate();
    if(!latestDate.isNull()){
        ui->selectIssueDate->setDate(latestDate);
        initTable(latestDate);
        updateWriterTimesheet(latestDate);
    }
}

void writerTimesheetWidget::initDB(Client *c){
    writerTimesheetDBC = new WriterTimesheetDBC(c);
}

void writerTimesheetWidget::initTable(QDate selectedDate)
{
    //QDate currentDate = QDate::currentDate();
    int NUMBEROFCOLUMNS = 4;
    int NUMBEROFROWS = writerTimesheetDBC->collectWriterForTimesheet(selectedDate).size();
    int alreadyExists = writerTimesheetDBC->writerTimesheetExists(selectedDate);

    if(alreadyExists>0){
    vector<vector<string>>* result_matrix = writerTimesheetDBC->getTimesheet(selectedDate);
    ui->writerTimesheetTable->setRowCount(NUMBEROFROWS);
    ui->writerTimesheetTable->setColumnCount(NUMBEROFCOLUMNS); //notice! hardcoded!

    ui->writerTimesheetTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->writerTimesheetTable->setColumnWidth(0, 200);
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
    } else {
    ui->writerTimesheetTable->clear();
    ui->writerTimesheetTable->setRowCount(0);
    ui->writerTimesheetTable->setColumnCount(4); //notice! hardcoded!

    ui->writerTimesheetTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->writerTimesheetTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Articles on time"));
    ui->writerTimesheetTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Articles late"));
    ui->writerTimesheetTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Issue date"));
    }
}

pair<int, int> writerTimesheetWidget::calculateArticlesOnTimeAndLate(QDate issueDate, int writerId)
{
    using namespace FileSystem;

    pair<int, int> articlesOnTimeAndLate;
    int articlesOnTime = 0;
    int articlesLate = 0;
    QDate deadline = issueDate.addDays(-3);

    QString issueDateQString = issueDate.toString("yyyy-MM-dd");
    string issueDateString = issueDateQString.toStdString();
    string date_art = QDate::fromString(issueDateQString,df::dbFormat).toString(df::srvrFormat).toStdString();
    Sender sndr = Sender();
    vector<int> articleIds = writerTimesheetDBC->collectArticleIdForTimesheet(issueDate, writerId);
    for(int i = 0; i < articleIds.size(); i++){
        string sectionName = writerTimesheetDBC->collectArticleSection(articleIds[i]);
        string articleName = writerTimesheetDBC->collectArticleTitle(articleIds[i]);
        FileSystem::VerSeq ver_seq = sndr.getHistory(date_art, sectionName, articleName, fs::COPY);
        FileSystem::VerSeq::const_iterator iter = ver_seq.begin();
        int noOfSubmissions = ver_seq.size();

        // Reads in first submitted file (assumed its submitted by writer)
        if(ver_seq.size()>0){
            FileSystem::TimeIce submissionTime = iter->time;
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

void writerTimesheetWidget::generateTimesheet(QDate issueDate)
{
    vector<int> writerIds = writerTimesheetDBC->collectWriterForTimesheet(issueDate);

    for(int i = 0; i<writerIds.size(); i++){
        pair<int, int> submissionDate = calculateArticlesOnTimeAndLate(issueDate, writerIds[i]);
        writerTimesheetDBC->generateWriterTimesheet(writerIds[i], submissionDate.first, submissionDate.second, issueDate);
    }
    Alert *alert = new Alert;
    alert->showInformationAlert("Generated!", "Writer Timesheet successfully generated");
    this->parentWindow->tabs->setCurrentIndex(4);
}

bool writerTimesheetWidget::updateWriterTimesheet(QDate selectedDate)
{
    //QDate currentDate = QDate::currentDate();
    vector<int> writerIds = writerTimesheetDBC->collectWriterForTimesheet(selectedDate);
    int alreadyExists = writerTimesheetDBC->writerTimesheetExists(selectedDate);
    if(alreadyExists>0){
        if(writerIds.size()>0 && alreadyExists>0){
            writerTimesheetDBC->deleteWriterTimesheetRecords(selectedDate);
            for(int i = 0; i<writerIds.size(); i++){
                pair<int, int> articleSubmission = calculateArticlesOnTimeAndLate(selectedDate, writerIds[i]);
                writerTimesheetDBC->generateWriterTimesheet(writerIds[i], articleSubmission.first, articleSubmission.second, selectedDate);
            }
        }
        initTable(selectedDate);
        return true;

    } else {
        return false;
    }
}

writerTimesheetWidget::~writerTimesheetWidget()
{
    delete ui;
}

void writerTimesheetWidget::on_updateWriterTimesheetButton_clicked()
{
    bool updateSuccessful = updateWriterTimesheet(ui->selectIssueDate->date());
    if(updateSuccessful){
        Alert *alert = new Alert;
        alert->showInformationAlert("Updated!", "Writer Timesheet successfully updated");
    } else {
        Alert *alert = new Alert;
        alert->showInformationAlert("Update", "Nothing to update");
    }
}

void writerTimesheetWidget::on_generateTimesheetButton_clicked()
{
    QDate selectedDate = ui->generateTimesheetDate->date();
    generateTimesheet(selectedDate);
    ui->selectIssueDate->setDate(selectedDate);
}

void writerTimesheetWidget::on_selectIssueDate_userDateChanged(const QDate &date)
{
    updateWriterTimesheet(date);
    initTable(date);
}
