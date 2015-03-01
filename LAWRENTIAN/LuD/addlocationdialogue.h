#ifndef ADDLOCATIONDIALOGUE_H
#define ADDLOCATIONDIALOGUE_H

#include <QDialog>

namespace Ui {
class AddLocationDialogue;
}

class AddLocationDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit AddLocationDialogue(QWidget *parent = 0);
    ~AddLocationDialogue();

private slots:
    void on_cancelButton_clicked();

private:
    Ui::AddLocationDialogue *ui;
};

#endif // ADDLOCATIONDIALOGUE_H
