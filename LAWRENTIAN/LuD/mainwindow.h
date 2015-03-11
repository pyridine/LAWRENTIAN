#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logincredentials.h"
#include "client.h"
#include "loginwindow.h"
#include "mainwindowdbc.h"
#include <QThread>

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
    Client* getClient();
    QTabWidget *tabs;

    ~MainWindow();

private:
    Ui::MainWindow* ui;
    LoginCredentials* loginCredo;
    Client* client;


    MainWindowDBC* dbController;

    LoginWindow* parentWindow;
};

#endif // MAINWINDOW_H
