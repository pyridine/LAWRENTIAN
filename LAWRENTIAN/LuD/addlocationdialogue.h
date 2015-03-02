#ifndef ADDLOCATIONDIALOGUE_H
#define ADDLOCATIONDIALOGUE_H

#include <QDialog>
#include "addlocationwindowdbc.h"
#include "editroutewindow.h"

namespace Ui {
class AddLocationDialogue;
}

class AddLocationDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit AddLocationDialogue(QWidget *parent = 0, int locID = 0, Client *c = new Client(),string def = "");
    ~AddLocationDialogue();

private slots:
    void on_cancelButton_clicked();

    void on_AddLocButton_clicked();

    void on_dropB_clicked();

private:
    Ui::AddLocationDialogue *ui;
    int myLocationID;
    AddLocationWindowDBC* dbController;
    EditRouteWindow* parente;
};

#endif // ADDLOCATIONDIALOGUE_H
