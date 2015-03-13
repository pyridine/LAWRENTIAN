#include "registrationwindow.h"
#include <QApplication>
#include "client.h"
#include <iostream>
#include "loginwindow.h"
#include <qmessagebox.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow w;
    w.show();

    Client c;
    if(c.connect()){
        w.initDB(&c);

    } else{
        QMessageBox alertBox;
        QString t = QString::fromUtf8("FATAL ERROR");
        QString m = QString::fromUtf8("I couldn't connect to the database. \n This program will now terminate.");
        alertBox.critical(0, t,m);
        alertBox.setFixedSize(500,200);
        return 0;
    }


    return a.exec();
}
