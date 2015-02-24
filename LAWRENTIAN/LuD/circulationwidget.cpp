#include "circulationwidget.h"
#include "ui_circulationwidget.h"
#include <iostream>

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
    cout << "circ route list not implemented yet. use the controller." << endl;
}


circulationWidget::~circulationWidget()
{
    delete ui;
}

void circulationWidget::on_editRouteButton_clicked()
{

}
