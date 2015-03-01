#include "addlocationdialogue.h"
#include "ui_addlocationdialogue.h"

AddLocationDialogue::AddLocationDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLocationDialogue)
{
    ui->setupUi(this);
}

AddLocationDialogue::~AddLocationDialogue()
{
    delete ui;
}

void AddLocationDialogue::on_cancelButton_clicked()
{
    this->hide();
    delete(this);
}
