#include "photopoolwindow.h"
#include "ui_photopoolwindow.h"

PhotoPoolWindow::PhotoPoolWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhotoPoolWindow)
{
    ui->setupUi(this);
}

PhotoPoolWindow::~PhotoPoolWindow()
{
    delete ui;
}

