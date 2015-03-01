#ifndef EDITROUTEWINDOW_H
#define EDITROUTEWINDOW_H

#include <QDialog>
#include "editroutewindowdbc.h"
#include "route.h"
#include "circulationwidget.h"

namespace Ui {
class EditRouteWindow;
}

class EditRouteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditRouteWindow(QWidget *parent = 0,Route* r = new Route(),int routeId = 0);
    void initDb(Client* c);
    ~EditRouteWindow();

private slots:

    void on_upButton_clicked();

    void on_downButton_clicked();

    void on_addPointButton_clicked();


    void on_removePointButton_clicked();

    void on_cancelButton_clicked();

    void on_applyButton_clicked();

private:
    Ui::EditRouteWindow *ui;
    EditRouteWindowDBC* dbController;
    void updateRouteDisplay();
    void updateLocationList();
    int myRouteID;

    circulationWidget* myParent;
    Route* myRoute;
    vector<int>* locIDs;

};

#endif // EDITROUTEWINDOW_H
