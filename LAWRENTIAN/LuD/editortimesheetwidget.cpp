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
}

void editorTimesheetWidget::initDB(Client *c){
    editorTimesheetDBC = new EditorTimesheetDBC(c);
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
    QString hoursString = QString::number(hours);
    ui->hoursWorkedTextEdit->setText(hoursString);
}
