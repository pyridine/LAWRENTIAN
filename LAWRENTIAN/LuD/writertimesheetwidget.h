#ifndef WRITERTIMESHEETWIDGET_H
#define WRITERTIMESHEETWIDGET_H

#include "writertimesheetdbc.h"
#include "logincredentials.h"
#include <QWidget>
#include "client.h"

namespace Ui {
class writerTimesheetWidget;
}

class writerTimesheetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit writerTimesheetWidget(QWidget *parent = 0);
    ~writerTimesheetWidget();

    void init(LoginCredentials* l, Client *c);
    void initDB(Client *c);
    pair<int, int> calculateArticlesOnTimeAndLate(QDate issueDate, int writerId);

private slots:
    void on_updateWriterTimesheetButton_clicked();

private:
    Ui::writerTimesheetWidget *ui;
    LoginCredentials* loginCred;
    Client *client;
    WriterTimesheetDBC *writerTimesheetDBC;

};

#endif // WRITERTIMESHEETWIDGET_H
