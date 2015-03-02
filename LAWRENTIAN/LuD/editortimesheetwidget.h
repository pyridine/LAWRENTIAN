#ifndef EDITORTIMESHEETWIDGET_H
#define EDITORTIMESHEETWIDGET_H

#include <QWidget>
#include "editortimesheetdbc.h"
#include "logincredentials.h"

namespace Ui {
class editorTimesheetWidget;
}

class editorTimesheetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit editorTimesheetWidget(QWidget *parent = 0);
    ~editorTimesheetWidget();

    void init(LoginCredentials* l, Client *c);
    void initDB(Client *c);

private slots:
    void on_submitChangesButton_clicked();

    void on_currentIssueDate_userDateChanged(const QDate &date);

private:
    Ui::editorTimesheetWidget *ui;
    LoginCredentials* loginCred;
    Client *client;
    EditorTimesheetDBC *editorTimesheetDBC;
};

#endif // EDITORTIMESHEETWIDGET_H
