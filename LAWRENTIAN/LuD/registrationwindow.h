#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include "employee.h"
#include "checkemployeeswindow.h"
#include "registrationwindowdbcontroller.h"

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

    void initDB(Client *c);

private slots:
    void on_submitButton_clicked();
    void on_passwordTextField_textChanged(const QString &arg1);

private:
    Ui::RegistrationWindow *ui;
    RegistrationWindowDBController* dbController;

    bool isValidUsername(string s);
    bool isPasswordSuitable(string s);
    bool isPhoneNumberDubiouslyValid(string s); //"dubiously" because the method is not garaunteed to give a valid phone number.
    bool isEmailValid(string s);
    bool isLuIDDubiouslyValid(std::string inputID); //"dubiously" because it's not garaunteed to be a real LU id.

};

#endif // REGISTRATIONWINDOW_H
