#include "circulationwidget.h"
#include "ui_circulationwidget.h"
#include <iostream>
#include "route.h"

using namespace std;

circulationWidget::circulationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::circulationWidget)
{
    ui->setupUi(this);
}

void circulationWidget::init_ViewAndEditPrivileges(Client* c){
    this->ui->editRouteButton->setVisible(true);
    this->ui->addRouteButton->setVisible(true);
    initDB(c);
    populateRouteList();
}
void circulationWidget::init_ViewPrivileges(Client* c){
    this->ui->editRouteButton->setVisible(false);
    this->ui->addRouteButton->setVisible(false);
    initDB(c);
    populateRouteList();
}

void circulationWidget::initDB(Client* c){
    dbController = new CirculationWindowDBC(c);
}

void circulationWidget::populateRouteList(){

    myRoutes = dbController->getAllRoutes();
    vector<pair<Route*,int>*>::iterator it = myRoutes->begin();

    while(it != myRoutes->end()){
        int nextNum = (**it).second;
        ui->routeSelectorWidget->addItem(
            QString::fromStdString("Route #").append(QString::number(nextNum)));
        ++it;
    }
    on_routeSelectorWidget_currentRowChanged(0);
}


circulationWidget::~circulationWidget()
{
    delete ui;
}

void circulationWidget::on_editRouteButton_clicked()
{

}

void circulationWidget::on_routeSelectorWidget_currentRowChanged(int currentRow)
{
    ui->routeDisplayWidget->clear();
    pair<Route*,int>* thisRouteCon = myRoutes->operator [](currentRow); //Yes, it actually has to be done this way :P

    Route* thisRoute = thisRouteCon->first;
    vector<Route::RoutePoint>::iterator points = thisRoute->begin();
    while(points != thisRoute->end()){
        QString name = QString::fromStdString(dbController->translateLocation(points->first));
        QString dash(" - ");
        name.append(dash);
        name.append(QString("%1").arg(points->second));
        this->ui->routeDisplayWidget->addItem(name);
        points++;
    }
}
