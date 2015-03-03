#include "addlocationdialogue.h"
#include "ui_addlocationdialogue.h"
#include "alert.h"

AddLocationDialogue::AddLocationDialogue(QWidget *parent, int locID, Client* c,string def) :
    QDialog(parent),
    ui(new Ui::AddLocationDialogue)
{
    ui->setupUi(this);
    dbController = new AddLocationWindowDBC(c);
    myLocationID = locID;
    parente = static_cast<EditRouteWindow*>(parent);
    ui->nameField->setText(QString::fromStdString(def));
}

AddLocationDialogue::~AddLocationDialogue()
{
    delete ui;
}

void AddLocationDialogue::on_cancelButton_clicked()
{
    this->hide();
    this->close();
    delete(this);
}

void AddLocationDialogue::on_AddLocButton_clicked()
{
    string inpText = this->ui->nameField->text().toStdString();
    if(inpText.size()){
        dbController->dropLocation(myLocationID);
        dbController->addLocation(myLocationID,inpText);
        parente->updateLocationList();
        this->hide();
        this->close();
        delete(this);
        return;
    }
    Alert::showAlert("Error","You must input a string, or hit cancel.");
}

void AddLocationDialogue::on_dropB_clicked()
{
    dbController->dropLocation(myLocationID);
    parente->updateLocationList();
    this->hide();
    this->close();
    delete(this);
    return;
}
