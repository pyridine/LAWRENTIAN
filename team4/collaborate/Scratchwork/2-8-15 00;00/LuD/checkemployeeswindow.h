#ifndef CHECKEMPLOYEESWINDOW_H
#define CHECKEMPLOYEESWINDOW_H

#include "employee.h"

#include <QDialog>
#include <vector>

namespace Ui {
class CheckEmployeesWindow;
}

class CheckEmployeesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CheckEmployeesWindow(QWidget *parent = 0);
    void initCheckEmployeesWindow(vector<Employee>);
    ~CheckEmployeesWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CheckEmployeesWindow *ui;
    vector<Employee> employeeVector;
    int employeeCount;

    void iterateThroughEmployees(int employeeCount);
};

#endif // CHECKEMPLOYEESWINDOW_H
