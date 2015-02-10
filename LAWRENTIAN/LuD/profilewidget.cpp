#include "profilewidget.h"
#include "ui_profilewidget.h"
#include <string>
#include <qstring.h>

using namespace std;

profileWidget::profileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profileWidget)
{
    ui->setupUi(this);
}

void profileWidget::init(MainWindow *parent, QString name, string title){
    ui->welcomeLabel->setText((QString::fromStdString("Welcome, ")+(name)+(QString::fromStdString("!"))));
    ui->titleLabel->setText((QString::fromStdString("(")+QString::fromStdString(title)+QString::fromStdString(")")));

    parentWindow = parent;
}

profileWidget::~profileWidget()
{
    delete ui;
}

void profileWidget::on_logOutButton_clicked()
{
    parentWindow->logOut();
}
