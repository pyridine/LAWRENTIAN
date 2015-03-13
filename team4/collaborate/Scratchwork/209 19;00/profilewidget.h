#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#include <QWidget>

namespace Ui {
class profileWidget;
}

class profileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit profileWidget(QWidget *parent = 0);
    ~profileWidget();

private:
    Ui::profileWidget *ui;
};

#endif // PROFILEWIDGET_H
