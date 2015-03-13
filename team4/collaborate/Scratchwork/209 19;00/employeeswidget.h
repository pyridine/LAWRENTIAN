#ifndef EMPLOYEESWIDGET_H
#define EMPLOYEESWIDGET_H

#include <QWidget>

namespace Ui {
class employeesWidget;
}

class employeesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit employeesWidget(QWidget *parent = 0);
    ~employeesWidget();

private:
    Ui::employeesWidget *ui;
};

#endif // EMPLOYEESWIDGET_H
