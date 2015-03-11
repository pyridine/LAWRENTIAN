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

void writerTimesheetWidget::updateLatestTimesheetDate()
{
    QDate latestDate = writerTimesheetDBC->collectLatestTimesheetDate();
    if(!latestDate.isNull()){
        latestTimesheetDate = latestDate;
    }

}

void writerTimesheetWidget::init(MainWindow* parent, LoginCredentials* l, Client *c){
    loginCred = l;
    this->client = c;
    parentWindow = parent;

    ui->selectIssueDateComboBox->blockSignals(true);
    populateIssueComboBox();
    ui->selectIssueDateComboBox->blockSignals(false);

    QDate latestIssue = writerTimesheetDBC->collectLatestIssueDate();
    if(!latestIssue.isNull()){
    ui->generateTimesheetDate->setDate(latestIssue);
    } else {
    ui->generateTimesheetDate->setDate(QDate::currentDate());
    }
    updateLatestTimesheetDate();
    QTimer *timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(updateLatestTimesheetDate()));
    timer1->start(1000);


    QString latestDateString = latestTimesheetDate.toString("d MMM yyyy");
    if(!latestTimesheetDate.isNull()){
        ui->selectIssueDateComboBox->setCurrentText(latestDateString);
        initTable(latestTimesheetDate);
        updateWriterTimesheet();
    }

    QString latestTimesheetDateString = ui->selectIssueDateComboBox->itemText(0);
    QDate latestTimesheetQDate = QDate::fromString(latestTimesheetDateString, "d MMM yyyy");
    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(updateWriterTimesheet()));
    timer2->start(10000);

}

void writerTimesheetWidget::initDB(Client *c){
    writerTimesheetDBC = new WriterTimesheetDBC(c);
}

void writerTimesheetWidget::populateIssueComboBox()
{
    ui->selectIssueDateComboBox->clear();
    vector<QDate> timesheetDateList = writerTimesheetDBC->getTimesheetDateList();
    QList<QString> timesheetDateQList;
    for (int i=0; i<timesheetDateList.size(); i++)
    {
        QString dateString = timesheetDateList[i].toString("d MMM yyyy");
        timesheetDateQList.insert(i, dateString);
    }
    ui->selectIssueDateComboBox->addItems(timesheetDateQList);
}

void writerTimesheetWidget::initTable(QDate selectedDate)
{
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
    populateIssueComboBox();
    QString issueDateString = issueDate.toString("d MM yyyy");
    ui->selectIssueDateComboBox->setCurrentText(issueDateString);
}

void writerTimesheetWidget::updateWriterTimesheet()
{
    vector<int> writerIds = writerTimesheetDBC->collectWriterForTimesheet(latestTimesheetDate);
    int alreadyExists = writerTimesheetDBC->writerTimesheetExists(latestTimesheetDate);
    if(alreadyExists>0){
        if(writerIds.size()>0 && alreadyExists>0){
            writerTimesheetDBC->deleteWriterTimesheetRecords(latestTimesheetDate);
            for(int i = 0; i<writerIds.size(); i++){
                pair<int, int> articleSubmission = calculateArticlesOnTimeAndLate(latestTimesheetDate, writerIds[i]);
                writerTimesheetDBC->generateWriterTimesheet(writerIds[i], articleSubmission.first, articleSubmission.second, latestTimesheetDate);
            }
        }
        initTable(latestTimesheetDate);
    }
}

writerTimesheetWidget::~writerTimesheetWidget()
{
    delete ui;
}

void writerTimesheetWidget::on_generateTimesheetButton_clicked()
{
    QDate selectedDate = ui->generateTimesheetDate->date();
    generateTimesheet(selectedDate);
}

void writerTimesheetWidget::on_selectIssueDateComboBox_currentIndexChanged(const QString &arg1)
{
    QDate date = QDate::fromString(arg1, "d MMM yyyy");
    updateWriterTimesheet();
    initTable(date);
}
