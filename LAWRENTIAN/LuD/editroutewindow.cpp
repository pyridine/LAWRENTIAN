#include "editroutewindow.h"
#include "ui_editroutewindow.h"

EditRouteWindow::EditRouteWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditRouteWindow)
{
    ui->setupUi(this);
}

EditRouteWindow::~EditRouteWindow()
{
    delete ui;
}
