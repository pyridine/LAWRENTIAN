#ifndef CIRCULATIONWIDGET_H
#define CIRCULATIONWIDGET_H

#include <QWidget>

namespace Ui {
class circulationWidget;
}

class circulationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit circulationWidget(QWidget *parent = 0);
    ~circulationWidget();

private:
    Ui::circulationWidget *ui;
};

#endif // CIRCULATIONWIDGET_H
