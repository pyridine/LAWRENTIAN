#ifndef EMPLOYEESWIDGET_H
#define EMPLOYEESWIDGET_H

#include <QWidget>
#include "client.h"
#include "logincredentials.h"
#include "employeetabledbc.h"
#include "mainwindow.h"

namespace Ui {
class employeesWidget;
}

class employeesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit employeesWidget(QWidget *parent = 0);
    ~employeesWidget();

    void init(LoginCredentials *l);
    void initDB(Client* c);

    void initNormalView();
    void initPrivilegedView();
    void initTotalView();

    int getNumUnregistered();

    void reUpdateTable();

private slots:
    void on_employeeTable_cellClicked(int row, int column);

    void on_approveRegButton_clicked();

private:
    int viewType; //normal=0,privilieged=1,total=1. Just for edit window.
    void handlePermissions();
    Ui::employeesWidget *ui;
    LoginCredentials* loginCred;
    EmployeeTableDBC* dbController;
    Client *client;

};

#endif // EMPLOYEESWIDGET_H
