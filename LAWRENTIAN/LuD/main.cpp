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

using namespace std;
using namespace FileSystem;

int main(int argc, char *argv[])
{
    Sender sndr = Sender(0); // sends to server computer
    //Sender sndr = Sender(0); // send to current computer. Needs Receiver rcvr = Receiver(0); in LuDServer main.
//    sndr.sendFile("1-1-1001","First","Second",fs::COPY, "OMG","C:/Programs/down.docx");
    sndr.deleteArt("1-1-1001","Nws","First");

    return 0;
}

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    LoginWindow* l = new LoginWindow();
//    Client* c = new Client();
//    l->show();

//    if(c->connect()){
//        l->show();
//        l->initDB(c);

//    } else{
//        Alert::showAlert("!!FATAL ERROR!!","I couldn't connect to the database. \n This program will now terminate.");
//        return 1337;
//    }

//    return a.exec();
//}
