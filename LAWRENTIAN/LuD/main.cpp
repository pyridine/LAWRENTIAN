#include "registrationwindow.h"
#include <QApplication>
#include "client.h"
#include <iostream>
#include "loginwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RegistrationWindow w;
    w.show();


    Client c;
    if(c.connect()){
        w.initDB(&c);

        cout << "Init done. Application should be on-screen." << endl;
    } else{
        cout << "Application failed to start :(" << endl;
    }


    return a.exec();
}
