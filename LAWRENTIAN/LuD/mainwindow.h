#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logincredentials.h"
#include "client.h"
#include "loginwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void init(LoginWindow* parent, LoginCredentials* l);
    void initDB(Client* c);
    void logOut();
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    LoginCredentials* loginCredo;
    Client* client;

    LoginWindow* parentWindow;
};

#endif // MAINWINDOW_H
