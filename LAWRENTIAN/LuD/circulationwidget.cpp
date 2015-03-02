#include "circulationwidget.h"
#include "ui_circulationwidget.h"
#include <iostream>
#include <string>
#include <sstream>
#include "permissiondef.h"
#include "route.h"
#include "editroutewindow.h"

using namespace std;

circulationWidget::circulationWidget(QWidget *parent, LoginCredentials *c) :
    QWidget(parent),
    ui(new Ui::circulationWidget)
{
    ui->setupUi(this);
    login = c;
    handlePermissions();
}

void circulationWidget::handlePermissions(){
    if(!login->hasPermission(PermissionDef::ADMIN_PTOKEN)
            &&!login->hasPermission(PermissionDef::EDIT_CIRCULATIONS)){
        this->ui->addRouteButton->setEnabled(false);
        this->ui->editRouteButton->setEnabled(false);
    }
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

    this->ui->routeSelectorWidget->clear();
    this->ui->routeDisplayWidget->clear();

    myRoutes = dbController->getAllRoutes();
    vector<pair<Route*,int>>::iterator it = myRoutes->begin();
    while(it != myRoutes->end()){
        int nextNum = (*it).second;
        ui->routeSelectorWidget->addItem(
            QString::fromStdString(dbController->translateRoute(nextNum)));
        ++it;
    }

    updateTotalCirculates();
}

void circulationWidget::updateTotalCirculates(){
    int total = dbController->sumTotalCopies();
    stringstream ss;
    ss << "Total copies to circulate: " <<total;
    QString Qlabel = QString::fromStdString(ss.str());
    this->ui->total->setText(Qlabel);
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
        EditRouteWindow* e = new EditRouteWindow(this,nextRoute,nextRouteID);
        e->setWindowModality(Qt::ApplicationModal);
        e->initDb(dbController->getClient());
        e->show();
    }
}

void circulationWidget::on_routeSelectorWidget_currentRowChanged(int currentRow)
{
    if(myRoutes->size() > 0 && currentRow >= 0){
        ui->routeDisplayWidget->clear();
        pair<Route*,int> thisRouteCon = myRoutes->operator [](currentRow); //Yes, it actually has to be done this way :P

        Route* thisRoute = thisRouteCon.first;
        vector<Route::RoutePoint>::iterator points = thisRoute->begin();
        int nextPointNum  = 1;
        while(points != thisRoute->end()){
            stringstream strs;
            strs << nextPointNum << ". " << dbController->translateLocation(points->first);
            strs << " (" << points->second << ")";

            this->ui->routeDisplayWidget->addItem(QString::fromStdString(strs.str()));

            points++;
            nextPointNum++;
        }
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
