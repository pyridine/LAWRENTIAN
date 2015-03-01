#include "alert.h"

Alert::Alert()
{

}

Alert::~Alert()
{

}
void Alert::showAlert(string title, string msg){
    QMessageBox alertBox;
    QString t = QString::fromUtf8(title.c_str());
    QString m = QString::fromUtf8(msg.c_str());
    alertBox.critical(0, t,m);
    alertBox.setFixedSize(500,200);
}

void Alert::showInformationAlert(string title, string msg)
{
    QMessageBox alertBox;
    QString t = QString::fromStdString(title);
    QString m = QString::fromStdString(msg);
    alertBox.information(0, t, m);
    alertBox.setFixedSize(500,200);
}

int Alert::showQuestionAlert(string title, string msg)
{
    QMessageBox alertBox;
    QString t = QString::fromStdString(title);
    QString m = QString::fromStdString(msg);
    int ret = alertBox.question(0, t, m, QMessageBox::Save | QMessageBox::Cancel, QMessageBox::Save);
    alertBox.setFixedSize(500,200);
    return ret;

}
