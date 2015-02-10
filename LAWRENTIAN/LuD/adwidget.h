#ifndef ADWIDGET_H
#define ADWIDGET_H

#include <QWidget>

namespace Ui {
class adWidget;
}

class adWidget : public QWidget
{
    Q_OBJECT

public:
    explicit adWidget(QWidget *parent = 0);
    ~adWidget();

private:
    Ui::adWidget *ui;
};

#endif // ADWIDGET_H
