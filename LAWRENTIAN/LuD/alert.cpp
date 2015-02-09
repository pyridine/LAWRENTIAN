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
