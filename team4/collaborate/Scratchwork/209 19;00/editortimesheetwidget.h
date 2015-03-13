#ifndef EDITORTIMESHEETWIDGET_H
#define EDITORTIMESHEETWIDGET_H

#include <QWidget>

namespace Ui {
class editorTimesheetWidget;
}

class editorTimesheetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit editorTimesheetWidget(QWidget *parent = 0);
    ~editorTimesheetWidget();

private:
    Ui::editorTimesheetWidget *ui;
};

#endif // EDITORTIMESHEETWIDGET_H
