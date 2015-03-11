#ifndef WRITERTIMESHEETWIDGET_H
#define WRITERTIMESHEETWIDGET_H

#include "writertimesheetdbc.h"
#include "logincredentials.h"
#include <QWidget>
#include "client.h"
#include "mainwindow.h"
#include <iostream>

namespace Ui {
class writerTimesheetWidget;
}

class writerTimesheetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit writerTimesheetWidget(QWidget *parent = 0);
    ~writerTimesheetWidget();

    void init(MainWindow* parent, LoginCredentials* l, Client *c);
    void initDB(Client *c);
    pair<int, int> calculateArticlesOnTimeAndLate(QDate issueDate, int writerId);
    void generateTimesheet(QDate issueDate);    
    void initTable(QDate selectedDate, bool editable);
    void populateIssueComboBox();
    void updateWriterTimesheet(QDate selectedDate);


private slots:
    void on_generateTimesheetButton_clicked();
    void on_selectIssueDateComboBox_currentIndexChanged(const QString &arg1);
    void updateTimesheetAndView();

    void on_freezeInformationButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::writerTimesheetWidget *ui;
    LoginCredentials* loginCred;
    Client *client;
    MainWindow *parentWindow;
    WriterTimesheetDBC *writerTimesheetDBC;
    QTimer *timer;

};

#endif // WRITERTIMESHEETWIDGET_H
