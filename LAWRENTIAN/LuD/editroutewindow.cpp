#include "editroutewindow.h"
#include "ui_editroutewindow.h"
#include "route.h";
#include "circulationwidget.h"
#include <iostream>

using namespace std;
EditRouteWindow::EditRouteWindow(QWidget *parent, Route *r,int routeId) :
    QDialog(parent),
    ui(new Ui::EditRouteWindow)
{
    ui->setupUi(this);
    myRoute = r;
    myRouteID = routeId;
    myParent = static_cast<circulationWidget*>(parent);
    this->ui->routeLabel->setText(QString::fromStdString("Route # ").append(QString::number(myRouteID)));
}

EditRouteWindow::~EditRouteWindow()
{
    delete ui;
}

void EditRouteWindow::updateRouteDisplay(){
    this->ui->routePointList->clear();
    vector<Route::RoutePoint>::iterator it = myRoute->begin();
    while(it != myRoute->end()){
        string locName = dbController->translateLocation((*it).first);
        int numIssues = (*it).second;
        QString display = QString::fromStdString(locName).append(" - ").append(QString::number(numIssues));
        this->ui->routePointList->addItem(display);
        ++it;
    }
}

void EditRouteWindow::updateLocationList(){
    locIDs = dbController->getAllLocationIDs();
    vector<int>::iterator locIt = locIDs->begin();
    while(locIt != locIDs->end()){

        ui->locationList->addItem(QString::fromStdString(dbController->translateLocation(*locIt)));
        locIt++;

    }
}

void EditRouteWindow::initDb(Client* c){
    dbController = new EditRouteWindowDBC(c);
    updateLocationList();
    updateRouteDisplay();
}

void EditRouteWindow::on_upButton_clicked()
{
    int currentIndex = this->ui->routePointList->currentRow();
    if(currentIndex >= 1){
        myRoute->swapPoints(myRoute->at(currentIndex),myRoute->at(currentIndex-1));
        this->updateRouteDisplay();
        this->ui->routePointList->setCurrentRow(currentIndex-1);
    }
}

void EditRouteWindow::on_downButton_clicked()
{
    int currentIndex = this->ui->routePointList->currentRow();
    std::cout <<"count is "<<this->ui->routePointList->count();
    if(currentIndex < this->ui->routePointList->count()-1){
        myRoute->swapPoints(myRoute->at(currentIndex+1),myRoute->at(currentIndex));
        this->updateRouteDisplay();
        this->ui->routePointList->setCurrentRow(currentIndex+1);
    }

}

void EditRouteWindow::on_addPointButton_clicked()
{
    int locIDIndex = this->ui->locationList->currentRow();
    if(locIDIndex >= 0){
        int locID = this->locIDs->operator [](locIDIndex);
        int numIssues = 0; //TODO
        Route::RoutePoint* nextPoint = static_cast<Route::RoutePoint*>
                (new pair<int,int>(locID,numIssues));
        myRoute->insert(nextPoint,myRoute->end());
        this->updateRouteDisplay();
    }
}

void EditRouteWindow::on_removePointButton_clicked()
{
    if(myRoute->begin() != myRoute->end()){
        myRoute->deleteNode(myRoute->at(ui->routePointList->currentRow()));
        this->updateRouteDisplay();
    }
}

void EditRouteWindow::on_cancelButton_clicked()
{
    this->hide();

}

void EditRouteWindow::on_applyButton_clicked()
{
    dbController->insertRoute(myRoute,myRouteID);
    this->hide();
    delete(this);
}
