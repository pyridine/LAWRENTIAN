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

using namespace std;

//int main(int argc, char *argv[])
//{
//    Sender sndr = Sender(); // sends to server computer
//    // Sender sndr = Sender(0); // send to current computer. Needs Receiver rcvr = Receiver(0); in LuDServer main.

//    sndr.sendFile("News","Not Really","Copy","Yo.docx",
//                "C:/Users/Briggs 419 Server/Dropbox/TwoComps.docx");

//    sndr.requestFile("Article","Document","Copy","Works","C:/Programs/doesit.docx");

//    sndr.requestFile("Article","Document","Copy","Works","C:/Programs/doesit3.docx",3);

//    FileSystem::VerSeq v_seq = sndr.getHistory("Article","Document","Copy","Works");

//    for (int i = 0; i != v_seq.size(); i++)
//    {
//        FileSystem::Version vr = v_seq.at(i);
//        cout << "Name: " << vr.verName << " Num: " << vr.verNum << endl;
//    }

//    return 0;
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow* l = new LoginWindow();
    Client* c = new Client();
    l->show();

    if(c->connect()){
        l->show();
        l->initDB(c);

    } else{
        Alert::showAlert("!!FATAL ERROR!!","I couldn't connect to the database. \n This program will now terminate.");
        return 1337;
    }

    return a.exec();
}
