#include "registrationwindow.h"
#include <QApplication>
#include "client.h"
#include <iostream>
#include "loginwindow.h"
#include <qmessagebox.h>
#include "alert.h"
#include "mainwindow.h"
#include "Sender.h"
#include "newarticleworkspacewindow.h"
#include "FileSystem.h"
#include <thread>

using namespace std;
using namespace FileSystem;

/*int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    return 0;
}*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow* l = new LoginWindow();
    Client* c = new Client();
    //l->show();

    if(c->connect()){
        l->show();
        l->initDB(c);

    } else{
        Alert::showAlert("!!FATAL ERROR!!","I couldn't connect to the database. \n"
                                           "Please check your internet connection. \n\n"
                                           "This program will now terminate.");
        return 1337;
    }

    return a.exec();
}


