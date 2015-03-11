#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#include <QWidget>
#include <string>
#include "mainwindow.h"
#include "logincredentials.h"
#include "client.h"
#include "profilewidgetdbc.h"
#include "employeeswidget.h"

using namespace std;

namespace Ui {
class profileWidget;
}

class profileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit profileWidget(QWidget *parent = 0);
    void init(MainWindow* parent, QString name, string title);
    ~profileWidget();

    void init(LoginCredentials* l, Client *c, employeesWidget *ew);
    void initDB(Client *c);
    void setWelcomeLabel();
    pair<int, int> calculateArticlesOnTimeAndLate(QDate issueDate, int writerId);

private slots:
    void on_logOutButton_clicked();
    void on_editProfileButton_clicked();
    void on_systemNotificationsTextBrowser_anchorClicked(const QUrl &arg1);
    void on_setDateButton_clicked();
    void updateNotifications();

    void on_submitChangesButton_clicked();

    void on_setCurrentIssueButton_clicked();

    void on_selectTimesheetDate_userDateChanged(const QDate &date);

private:
    Ui::profileWidget *ui;
    MainWindow* parentWindow;
    LoginCredentials* loginCred;
    Client *client;
    ProfileWidgetDBC *profileWidgetDBC;
    employeesWidget *ew;
};

#endif // PROFILEWIDGET_H
