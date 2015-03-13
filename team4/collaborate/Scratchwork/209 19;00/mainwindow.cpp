#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "articleworkspace.h"
#include "profilewidget.h"
#include "employeeswidget.h"
#include "adwidget.h"
#include "editortimesheetwidget.h"
#include "writertimesheetwidget.h"
#include "subscriptionswidget.h"
#include "circulationwidget.h"

#include <QTabWidget>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *mainWidget = new QWidget(ui->centralwidget);
    QTabWidget *tabs = new QTabWidget(mainWidget);


    tabs->setFixedSize(1100,600);
    tabs->addTab(new profileWidget(), "Profile");
    tabs->addTab(new employeesWidget(), "Employees");
    tabs->addTab(new articleWorkspace(), "Article Workspace");
    tabs->addTab(new editorTimesheetWidget(), "Editor Timesheet");
    tabs->addTab(new writerTimesheetWidget(), "Writer Timesheet");
    tabs->addTab(new subscriptionsWidget(), "Subscriptions");
    tabs->addTab(new circulationWidget(), "Circulation");
    tabs->addTab(new adWidget(), "Ads");

}

MainWindow::~MainWindow()
{
    delete ui;
}
