#include "profilewidget.h"
#include "ui_profilewidget.h"
#include <string>
#include <qstring.h>

#include "editprofilewidget.h"

using namespace std;

profileWidget::profileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profileWidget)
{
    ui->setupUi(this);
}

void profileWidget::init(LoginCredentials* l, Client *c){
    loginCred = l;
    this->client = c;
}

void profileWidget::initDB(Client *c){
    profileWidgetDBC = new ProfileWidgetDBC(c);
}

void profileWidget::init(MainWindow *parent, QString name, string title){
    setWelcomeLabel();
    parentWindow = parent;
}

void profileWidget::setWelcomeLabel()
{
    QString name = QString::fromStdString(profileWidgetDBC->collectName(loginCred->getLUID()));
    QString title = QString::fromStdString(profileWidgetDBC->collectTitle(loginCred->getLUID()));
    ui->welcomeLabel->setText((QString::fromStdString("Welcome, ")+(name)+(QString::fromStdString("!"))));
    ui->titleLabel->setText((QString::fromStdString("(")+title+QString::fromStdString(")")));
}

profileWidget::~profileWidget()
{
    delete ui;
}

void profileWidget::on_logOutButton_clicked()
{
    parentWindow->logOut();
}

void profileWidget::on_editProfileButton_clicked()
{
    EditProfileWidget *editProfileWidget = new EditProfileWidget;
    editProfileWidget->myParent = this;
    editProfileWidget->init(loginCred);
    editProfileWidget->initDB(this->client);
    editProfileWidget->populateAllFields();
    editProfileWidget->show();

}
