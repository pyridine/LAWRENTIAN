#ifndef EDITROUTEWINDOW_H
#define EDITROUTEWINDOW_H

#include <QDialog>

namespace Ui {
class EditRouteWindow;
}

class EditRouteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditRouteWindow(QWidget *parent = 0);
    ~EditRouteWindow();

private:
    Ui::EditRouteWindow *ui;
};

#endif // EDITROUTEWINDOW_H
