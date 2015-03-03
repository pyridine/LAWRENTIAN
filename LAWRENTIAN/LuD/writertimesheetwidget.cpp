#include "writertimesheetwidget.h"
#include "ui_writertimesheetwidget.h"

#include "alert.h"
#include <iostream>
#include "Sender.h"
#include "FileSystem.h"

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
            pair<int, int> articleSubmission = calculateArticlesOnTimeAndLate(currentDate, writerIds[i]);
            writerTimesheetDBC->generateWriterTimesheet(writerIds[i], articleSubmission.first, articleSubmission.second, currentDate);
        }
        Alert *alert = new Alert;
        alert->showInformationAlert("Updated!", "Writer Timesheet successfully updated");
    }
}
