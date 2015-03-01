#include "circulationwidget.h"
#include "ui_circulationwidget.h"
#include <iostream>
#include "route.h"
#include "editroutewindow.h"

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
    /*
    cout <<":("<<endl;
    myRoutes = dbController->getAllRoutes();
    vector<pair<Route*,int>>::iterator it = myRoutes->begin();

    cout <<":("<<endl;
    while(it != myRoutes->end()){
        cout <<":( DEREFERENCD UNDEREFERENCEABLE :(((((((("<<endl;
        int nextNum = (*it).second;
        cout <<":)"<<endl;
        ui->routeSelectorWidget->addItem(
            QString::fromStdString("Route #").append(QString::number(nextNum)));
        ++it;
    }
    on_routeSelectorWidget_currentRowChanged(0);
    */
}


circulationWidget::~circulationWidget()
{
    delete ui;
}

void circulationWidget::on_editRouteButton_clicked()
{
    int indexOfRoute = this->ui->routeSelectorWidget->currentRow();
    if(indexOfRoute >= 0){
        pair<Route*,int> nextRoutePair = myRoutes->operator[](indexOfRoute); //Only way it works :P
        Route* nextRoute = nextRoutePair.first;
        int nextRouteID = nextRoutePair.second;
        cout << "making w" << endl;
        EditRouteWindow* e = new EditRouteWindow(this,nextRoute,nextRouteID);
        e->setWindowModality(Qt::ApplicationModal);
        e->initDb(dbController->getClient());
        e->show();
    }
}

void circulationWidget::on_routeSelectorWidget_currentRowChanged(int currentRow)
{
    pair<Route*,int> thisRouteCon = myRoutes->operator [](currentRow); //Yes, it actually has to be done this way :P
    Route* thisRoute = thisRouteCon.first;
    vector<Route::RoutePoint>::iterator points = thisRoute->begin();
    while(points != thisRoute->end()){
        QString nextstr = QString::fromStdString(dbController->translateLocation(points->first));
        nextstr.append(QString("%1").arg(points->second));
        this->ui->routeDisplayWidget->addItem(nextstr);
        points++;
    }
}

void circulationWidget::on_addRouteButton_clicked()
{
    Route* newR = new Route();
    int nextRouteID = dbController->getAvailableRouteId();
    EditRouteWindow* e = new EditRouteWindow(this,newR,nextRouteID);
    e->setWindowModality(Qt::ApplicationModal);
    e->initDb(dbController->getClient());
    e->show();
}
