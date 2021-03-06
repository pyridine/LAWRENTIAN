#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "loginwindowdbc.h"
#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    void initDB(Client *c);
    ~LoginWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    LoginWindowDBC* dbController;
    Ui::LoginWindow* ui;
};

#endif // LOGINWINDOW_H
