#ifndef EDITROUTEWINDOW_H
#define EDITROUTEWINDOW_H

#include <QDialog>
#include "editroutewindowdbc.h"
#include "route.h"
#include "circulationwidget.h"
#include <QWidgetItem>
#include <QListWidgetItem>

namespace Ui {
class EditRouteWindow;
}

class EditRouteWindow : public QDialog
{
    Q_OBJECT

public:
    void updateRouteDisplay();
    void updateLocationList();
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

    void on_dropRouteWindow_clicked();

    void on_locationList_itemDoubleClicked(QListWidgetItem *item);

    void on_routePointList_itemDoubleClicked(QListWidgetItem *item);


    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::EditRouteWindow *ui;
    EditRouteWindowDBC* dbController;
    int myRouteID;

    circulationWidget* myParent;
    Route* myRoute;
    vector<int>* locIDs;

};

#endif // EDITROUTEWINDOW_H
