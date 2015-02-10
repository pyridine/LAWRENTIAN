#ifndef WRITERTIMESHEETWIDGET_H
#define WRITERTIMESHEETWIDGET_H

#include <QWidget>

namespace Ui {
class writerTimesheetWidget;
}

class writerTimesheetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit writerTimesheetWidget(QWidget *parent = 0);
    ~writerTimesheetWidget();

private:
    Ui::writerTimesheetWidget *ui;
};

#endif // WRITERTIMESHEETWIDGET_H
