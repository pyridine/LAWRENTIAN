#ifndef CIRCULATIONWIDGET_H
#define CIRCULATIONWIDGET_H

#include <QWidget>
#include <utility>
#include "route.h"
#include "client.h"
#include "circulationwindowdbc.h"

using namespace std;

namespace Ui {
class circulationWidget;
}

class circulationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit circulationWidget(QWidget *parent = 0);
    ~circulationWidget();

    void init_ViewPrivileges(Client* c);
    void init_ViewAndEditPrivileges(Client* c);

private slots:
    void on_editRouteButton_clicked();

    void on_routeSelectorWidget_currentRowChanged(int currentRow);

private:
    void initDB(Client* c);
    void populateRouteList();
    vector<pair<Route*,int>>* myRoutes;
    Ui::circulationWidget *ui;
    vector<Route> routes;
    CirculationWindowDBC* dbController;

};

#endif // CIRCULATIONWIDGET_H
