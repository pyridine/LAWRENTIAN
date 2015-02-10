#ifndef EMPLOYEESWIDGET_H
#define EMPLOYEESWIDGET_H

#include <QWidget>
#include "client.h"
#include "logincredentials.h"
#include "employeetabdbcontroller.h"
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

private slots:
    void on_employeeTable_cellClicked(int row, int column);

private:
    Ui::employeesWidget *ui;
    LoginCredentials* loginCred;
    EmployeeTabDBController* dbController;

};

#endif // EMPLOYEESWIDGET_H
