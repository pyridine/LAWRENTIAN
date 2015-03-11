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
    void initTable(QDate date, bool editable);
    void populateIssueComboBox();
    void toggleEditMode();
    void toggleViewMode();

private slots:
    void on_setCurrentIssueButton_clicked();
    void updateTable();
    void on_selectedIssueDateComboBox_currentIndexChanged(const QString &arg1);

    void on_saveChangesButton_clicked();

    void on_revertButton_clicked();

    void on_editModeButton_clicked();

private:
    Ui::editorTimesheetWidget *ui;
    LoginCredentials* loginCred;
    Client *client;
    EditorTimesheetDBC *editorTimesheetDBC;
    QTimer *timer;
    bool viewMode;
};

#endif // EDITORTIMESHEETWIDGET_H
