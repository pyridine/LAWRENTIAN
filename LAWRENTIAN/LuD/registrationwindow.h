#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include "employee.h"
#include "checkemployeeswindow.h"

#include <QMainWindow>
#include <vector>

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = 0);
    ~RegistrationWindow();

private slots:
    void on_submitButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::RegistrationWindow *ui;
    std::vector<Employee> employeeVector;
    CheckEmployeesWindow *checkEmployeesWindow;
};

#endif // REGISTRATIONWINDOW_H
