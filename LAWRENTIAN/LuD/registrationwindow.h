#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QMainWindow>

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = 0);
    ~RegistrationWindow();

private:
    Ui::RegistrationWindow *ui;
};

#endif // REGISTRATIONWINDOW_H
