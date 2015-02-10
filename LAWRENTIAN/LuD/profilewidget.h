#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#include <QWidget>
#include <string>
#include "mainwindow.h"

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

private slots:
    void on_logOutButton_clicked();

private:
    Ui::profileWidget *ui;
    MainWindow* parentWindow;
};

#endif // PROFILEWIDGET_H
