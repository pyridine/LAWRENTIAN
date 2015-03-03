#ifndef WRITERTIMESHEETWIDGET_H
#define WRITERTIMESHEETWIDGET_H

#include "writertimesheetdbc.h"
#include "logincredentials.h"
#include <QWidget>
#include "client.h"
#include <thread>
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
    void initTable();
    pair<int, int> calculateArticlesOnTimeAndLate(QDate issueDate, int writerId);
    void updateWriterTimesheet();

private slots:
    void on_updateWriterTimesheetButton_clicked();

private:
    Ui::writerTimesheetWidget *ui;
    LoginCredentials* loginCred;
    Client *client;
    MainWindow *parentWindow;
    WriterTimesheetDBC *writerTimesheetDBC;

};

#endif // WRITERTIMESHEETWIDGET_H
