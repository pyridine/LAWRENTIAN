#ifndef SUBSCRIPTIONSWIDGET_H
#define SUBSCRIPTIONSWIDGET_H

#include <QWidget>

namespace Ui {
class subscriptionsWidget;
}

class subscriptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit subscriptionsWidget(QWidget *parent = 0);
    ~subscriptionsWidget();

private:
    Ui::subscriptionsWidget *ui;
};

#endif // SUBSCRIPTIONSWIDGET_H
