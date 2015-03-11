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
    viewMode = true;
    ui->saveChangesButton->hide();
    ui->revertButton->hide();

    ui->selectedIssueDateComboBox->blockSignals(true);
    populateIssueComboBox();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTable()));
    timer->start(10000);

    QDate latestIssue = editorTimesheetDBC->collectLatestIssueDate();
    QString latestIssueString = latestIssue.toString("d MMM yyyy");
    if(!latestIssue.isNull()){
        ui->selectedIssueDateComboBox->setCurrentText(latestIssueString);
        initTable(latestIssue, false);
    }
    ui->selectedIssueDateComboBox->blockSignals(false);
}

void editorTimesheetWidget::initDB(Client *c)
{
    editorTimesheetDBC = new EditorTimesheetDBC(c);
}

void editorTimesheetWidget::populateIssueComboBox()
{
    ui->selectedIssueDateComboBox->clear();
    vector<QDate> timesheetDateList = editorTimesheetDBC->getTimesheetDateList();
    QList<QString> timesheetDateQList;
    for (int i=0; i<timesheetDateList.size(); i++)
    {
        QString dateString = timesheetDateList[i].toString("d MMM yyyy");
        timesheetDateQList.insert(i, dateString);
    }
    ui->selectedIssueDateComboBox->addItems(timesheetDateQList);
}

void editorTimesheetWidget::updateTable()
{
    QString selectedDate = ui->selectedIssueDateComboBox->currentText();
    QDate date = QDate::fromString(selectedDate, "d MMM yyyy");
    initTable(date, false);
}

void editorTimesheetWidget::initTable(QDate date, bool editable)
{
    int NUMBEROFCOLUMNS = 3;
    int NUMBEROFROWS = editorTimesheetDBC->collectEditorForTimesheet(date).size();

    vector<vector<string>>* result_matrix = editorTimesheetDBC->getTimesheet(date);
    ui->editorTimesheetTable->setRowCount(NUMBEROFROWS);
    ui->editorTimesheetTable->setColumnCount(NUMBEROFCOLUMNS); //notice! hardcoded!

    QTableWidgetItem *editorItem = new QTableWidgetItem("Editor");
    ui->editorTimesheetTable->setHorizontalHeaderItem(0, editorItem);
    ui->editorTimesheetTable->setColumnWidth(0, 200);

    QTableWidgetItem *hoursItem = new QTableWidgetItem("Hours");
    ui->editorTimesheetTable->setHorizontalHeaderItem(1, hoursItem);

    QTableWidgetItem *issueDateItem = new QTableWidgetItem("Issue Date");
    ui->editorTimesheetTable->setHorizontalHeaderItem(2, issueDateItem);

    vector<vector<string>>::iterator writerIt = result_matrix->begin();
    for(int i = 0; i < NUMBEROFROWS; ++i){
        vector<string> nextWriter = *writerIt;
        vector<string>::iterator empDataIt = nextWriter.begin();
        for(int z = 0; z < NUMBEROFCOLUMNS; z++){
            string nextItem = *empDataIt;
            if(editable){
                ui->editorTimesheetTable->setItem(i,z,new QTableWidgetItem((nextItem.c_str())));
                if(z==0 || z==2){
                    QTableWidgetItem *item = new QTableWidgetItem(nextItem.c_str());
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    ui->editorTimesheetTable->setItem(i,z,item);
                }
            } else {
                QTableWidgetItem *item = new QTableWidgetItem(nextItem.c_str());
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                ui->editorTimesheetTable->setItem(i,z,item);
            }
            ++empDataIt;
        }
        ++writerIt;
    }
}

editorTimesheetWidget::~editorTimesheetWidget()
{
    delete ui;
}

void editorTimesheetWidget::on_setCurrentIssueButton_clicked()
{
    QDate latestIssue = editorTimesheetDBC->collectLatestIssueDate();
    QString latestIssueString = latestIssue.toString("d MMM yyyy");
    if(!latestIssue.isNull()){
        ui->selectedIssueDateComboBox->setCurrentText(latestIssueString);
    } else {
        Alert *alert = new Alert;
        alert->showInformationAlert("No Set Issue Date", "No current issue date set.\nSetting to previous timesheet");
        vector<QDate> timesheetDateList = editorTimesheetDBC->getTimesheetDateList();
        if(timesheetDateList.size()>0){
            QDate lastAvailableDate = timesheetDateList[0];
            QString lastAvailableDateString = lastAvailableDate.toString("d MMM yyyy");
            ui->selectedIssueDateComboBox->setCurrentText(lastAvailableDateString);
        } else {
            Alert *alert2 = new Alert;
            alert2->showInformationAlert("No Set Issue Date", "No date set.\nNo previous timesheet available");
        }
    }
}

void editorTimesheetWidget::on_selectedIssueDateComboBox_currentIndexChanged(const QString &arg1)
{
    QDate date = QDate::fromString(arg1, "d MMM yyyy");
    initTable(date, false);
}

void editorTimesheetWidget::on_saveChangesButton_clicked()
{
    QString selectedDate = ui->selectedIssueDateComboBox->currentText();
    QDate date = QDate::fromString(selectedDate, "d MMM yyyy");

    Alert *confirm = new Alert;
    int ret = confirm->showQuestionAlert("Save", "Are you sure you want to save changes?");
    switch(ret){
    case QMessageBox::Save: {
        // Must iterate through all rows
        int NUMBEROFCOLUMNS = 3;
        int NUMBEROFROWS = ui->editorTimesheetTable->rowCount();

        for(int row = 0; row < NUMBEROFROWS; row++){
            QString editorName = ui->editorTimesheetTable->item(row,0)->text();
            int hours = ui->editorTimesheetTable->item(row, 1)->text().toInt();
            QString issueDate = ui->editorTimesheetTable->item(row,2)->text();
            QDate issueDateQDate = QDate::fromString(issueDate, "yyyy-MM-dd");
            int luid = editorTimesheetDBC->getLuidForName(editorName.toStdString());
            editorTimesheetDBC->setHoursWorked(luid, issueDateQDate, hours);
        }
        initTable(date, true);
        Alert *alert = new Alert;
        alert->showInformationAlert("Update Successful", "Changes successfully saved");
        toggleViewMode();
        break;
    }
    case QMessageBox::Cancel: {
        Alert *editModeOff = new Alert;
        editModeOff->showInformationAlert("Update Canceled", "Changes reverted and edit mode turned off");
        toggleViewMode();
        break;
    }
    }

}

void editorTimesheetWidget::on_revertButton_clicked()
{
    QString selectedDate = ui->selectedIssueDateComboBox->currentText();
    QDate date = QDate::fromString(selectedDate, "d MMM yyyy");
    initTable(date, true);
    Alert *editModeOff = new Alert;
    editModeOff->showInformationAlert("Update Canceled", "Changes reverted.");

}

void editorTimesheetWidget::toggleEditMode()
{
    viewMode = false;
    timer->blockSignals(true);
    ui->saveChangesButton->show();
    ui->revertButton->show();
    ui->editModeButton->setText("Toggle View Mode");
    ui->viewModeLabel->setText("<font color='red'>CURRENT MODE: EDIT</font>");
    QString selectedDate = ui->selectedIssueDateComboBox->currentText();
    QDate date = QDate::fromString(selectedDate, "d MMM yyyy");
    initTable(date, true);
}

void editorTimesheetWidget::toggleViewMode()
{
    viewMode = true;
    timer->blockSignals(false);
    ui->saveChangesButton->hide();
    ui->revertButton->hide();
    ui->editModeButton->setText("Toggle Edit Mode");
    ui->viewModeLabel->setText("CURRENT MODE: VIEW ONLY");
    QString selectedDate = ui->selectedIssueDateComboBox->currentText();
    QDate date = QDate::fromString(selectedDate, "d MMM yyyy");
    initTable(date, false);
}

void editorTimesheetWidget::on_editModeButton_clicked()
{
    if(viewMode){
        toggleEditMode();
    } else {
        toggleViewMode();
    }
}
