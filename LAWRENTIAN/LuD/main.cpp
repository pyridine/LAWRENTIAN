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

//    sndr.sendFile("First","Second","Copy","OMG.docx",
//                "C:/Programs/OMG.docx");

//    sndr.requestFile("First","Second","Copy","OMG","C:/Programs/t1.docx");

//    sndr.requestFile("First","Second","Copy","OMG","C:/Programs/t2.docx",1);

//    FileSystem::VerSeq v_seq = sndr.getHistory("First","Second","Copy","OMG");

//    for (int i = 0; i != v_seq.size(); i++)
//    {
//        FileSystem::Version vr = v_seq.at(i);
//        cout << "Name: " << vr.verName << " Num: " << vr.verNum << endl;
//        cout << vr.time.hour << ":" << vr.time.minute << ":" << vr.time.second << " " << vr.time.dayOfTheWeek << endl;
//    }

//    sndr.sendFile("First","Second","Image","fixed.jpg",
//                "C:/Programs/fixed.jpg");

//    sndr.requestFile("First","Second","Image","fixed","C:/Programs/f1.jpg");

//    sndr.requestFile("First","Second","Image","fixed","C:/Programs/f2.jpg",4);

//    v_seq = sndr.getHistory("First","Second","Image","fixed");

//    for (int i = 0; i != v_seq.size(); i++)
//    {
//        FileSystem::Version vr = v_seq.at(i);
//        cout << "Name: " << vr.verName << " Num: " << vr.verNum << endl;
//        cout << vr.time.hour << ":" << vr.time.minute << ":" << vr.time.second << " " << vr.time.dayOfTheWeek << endl;
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
