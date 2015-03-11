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
    ui->frozenModeLabel->hide();
    ui->saveButton->hide();

    ui->selectIssueDateComboBox->blockSignals(true);
    populateIssueComboBox();
    ui->selectIssueDateComboBox->blockSignals(false);

    QDate latestIssue = writerTimesheetDBC->collectLatestIssueDate();
    if(!latestIssue.isNull()){
        ui->generateTimesheetDate->setDate(latestIssue);
    } else {
        ui->generateTimesheetDate->setDate(QDate::currentDate());
    }

    QDate latestDate = writerTimesheetDBC->collectLatestTimesheetDate();
    QString latestDateString = latestDate.toString("d MMM yyyy");
    if(!latestDate.isNull()){
        ui->selectIssueDateComboBox->setCurrentText(latestDateString);
        updateWriterTimesheet(latestDate);
        if(writerTimesheetDBC->getFrozen(latestDate)){
            initTable(latestDate, true);
            ui->freezeInformationButton->hide();
            ui->frozenModeLabel->show();
            ui->saveButton->show();
        } else {
            initTable(latestDate, false);
        }
    }

    QString latestTimesheetDateString = ui->selectIssueDateComboBox->itemText(0);
    QDate latestTimesheetQDate = QDate::fromString(latestTimesheetDateString, "d MMM yyyy");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimesheetAndView()));
    timer->start(10000);

}

void writerTimesheetWidget::updateTimesheetAndView()
{
    QString dateString = ui->selectIssueDateComboBox->currentText();
    QDate date = QDate::fromString(dateString, "d MMM yyyy");
    if(!writerTimesheetDBC->getFrozen(date)){
        cout<<"Updating writer timesheet"<<endl;
    updateWriterTimesheet(date);
    }
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

void writerTimesheetWidget::initTable(QDate selectedDate, bool editable)
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
                if(editable){
                    ui->writerTimesheetTable->setItem(i,z,new QTableWidgetItem((nextItem.c_str())));
                    if(z==0 || z==3){
                        QTableWidgetItem *item = new QTableWidgetItem(nextItem.c_str());
                        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                        ui->writerTimesheetTable->setItem(i,z,item);
                    }
                } else {
                    QTableWidgetItem *item = new QTableWidgetItem(nextItem.c_str());
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    ui->writerTimesheetTable->setItem(i,z,item);
                }
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
    populateIssueComboBox();
    Alert *alert = new Alert;
    alert->showInformationAlert("Generated!", "Writer Timesheet successfully generated");

    QString issueDateString = issueDate.toString("d MM yyyy");
    ui->selectIssueDateComboBox->setCurrentText(issueDateString);
    timer->blockSignals(false);
}

void writerTimesheetWidget::updateWriterTimesheet(QDate selectedDate)
{
    if(!writerTimesheetDBC->getFrozen(selectedDate)){
//        vector<int> writerIds = writerTimesheetDBC->collectWriterForTimesheet(selectedDate);
//        int alreadyExists = writerTimesheetDBC->writerTimesheetExists(selectedDate);
//        if(alreadyExists>0){
//            if(writerIds.size()>0 && alreadyExists>0){
//                writerTimesheetDBC->deleteWriterTimesheetRecords(selectedDate);
//                for(int i = 0; i<writerIds.size(); i++){
//                    pair<int, int> articleSubmission = calculateArticlesOnTimeAndLate(selectedDate, writerIds[i]);
//                    writerTimesheetDBC->generateWriterTimesheet(writerIds[i], articleSubmission.first, articleSubmission.second, selectedDate);
//                }
//            }
//            if(writerTimesheetDBC->getFrozen(selectedDate)){
//                initTable(selectedDate, true);
//            } else {
//                initTable(selectedDate, false);
//            }
//        }

        vector<int> writerIds = writerTimesheetDBC->collectWriterForTimesheet(selectedDate);
                for(int i = 0; i<writerIds.size(); i++){
                    pair<int, int> articleSubmission = calculateArticlesOnTimeAndLate(selectedDate, writerIds[i]);
                    writerTimesheetDBC->updateWriterTimesheet(writerIds[i], articleSubmission.first, articleSubmission.second, selectedDate);
                }
            if(writerTimesheetDBC->getFrozen(selectedDate)){
                initTable(selectedDate, true);
            } else {
                initTable(selectedDate, false);
            }
    }
}

writerTimesheetWidget::~writerTimesheetWidget()
{
    delete ui;
}

void writerTimesheetWidget::on_generateTimesheetButton_clicked()
{
    timer->blockSignals(true);
    QDate selectedDate = ui->generateTimesheetDate->date();
    generateTimesheet(selectedDate);
}

void writerTimesheetWidget::on_selectIssueDateComboBox_currentIndexChanged(const QString &arg1)
{
    QDate date = QDate::fromString(arg1, "d MMM yyyy");
    updateWriterTimesheet(date);
    if(writerTimesheetDBC->getFrozen(date)){
        initTable(date, true);
        ui->frozenModeLabel->show();
    } else {
        initTable(date, false);
        ui->frozenModeLabel->hide();
    }
}

void writerTimesheetWidget::on_freezeInformationButton_clicked()
{
    QMessageBox alertBox;
    alertBox.setFixedSize(1000,700);
    QString information = "Freeze Information:\n\n"
                          "\"Freezing information\" consists of stopping the automatic writer timesheet updates and submission "
                          "calculations so that you can make manual changes.\n"
                          "This is only recommended if you "
                          "do not need the system to calculate any more submissions for this issue date.\n\n"
                          "Are you sure you want to proceed? This cannot be undone.";
    int ret = alertBox.information(0, "Freeze Information", information, QMessageBox::Cancel | QMessageBox::Apply, QMessageBox::Cancel);
    switch(ret){
    case QMessageBox::Apply: {
        timer->blockSignals(true);
        QString selectedDateString = ui->selectIssueDateComboBox->currentText();
        QDate selectedDate = QDate::fromString(selectedDateString, "d MMM yyyy");
        updateWriterTimesheet(selectedDate); // Update last time before freeze
        writerTimesheetDBC->setFrozen(selectedDate);
        ui->frozenModeLabel->show();
        ui->freezeInformationButton->hide();
        ui->saveButton->show();
        Alert *alert = new Alert;
        alert->showInformationAlert("Success!", "Freeze mode successfully toggled. You can now make manual changes.");
            initTable(selectedDate, true);
        break;
    }
    case QMessageBox::Cancel: {
        break;
    }
    }

}

void writerTimesheetWidget::on_saveButton_clicked()
{
    QString selectedDate = ui->selectIssueDateComboBox->currentText();
    QDate date = QDate::fromString(selectedDate, "d MMM yyyy");

    Alert *confirm = new Alert;
    int ret = confirm->showQuestionAlert("Save", "Are you sure you want to save changes?");
    switch(ret){
    case QMessageBox::Save: {
        // Must iterate through all rows
        int NUMBEROFCOLUMNS = 4;
        int NUMBEROFROWS = ui->writerTimesheetTable->rowCount();

        for(int row = 0; row < NUMBEROFROWS; row++){
            QString writerName = ui->writerTimesheetTable->item(row,0)->text();
            int articlesOnTime = ui->writerTimesheetTable->item(row, 1)->text().toInt();
            int articlesLate = ui->writerTimesheetTable->item(row, 2)->text().toInt();
            QString issueDate = ui->writerTimesheetTable->item(row,3)->text();
            QDate issueDateQDate = QDate::fromString(issueDate, "yyyy-MM-dd");
            int luid = writerTimesheetDBC->getLuidForName(writerName.toStdString());
            writerTimesheetDBC->setArticleSubmissionsForLuid(luid, articlesOnTime, articlesLate);
        }
        initTable(date, true);
        Alert *alert = new Alert;
        alert->showInformationAlert("Update Successful", "Changes successfully saved");
        break;
    }
    case QMessageBox::Cancel: {
        initTable(date, true);
        Alert *editModeOff = new Alert;
        editModeOff->showInformationAlert("Update Canceled", "Changes reverted and edit mode turned off");
        break;
    }
    }

}
