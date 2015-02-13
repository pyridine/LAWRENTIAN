#include "registrationwindow.h"
#include <QApplication>
#include "client.h"
#include <iostream>
#include "loginwindow.h"
#include <qmessagebox.h>
#include "alert.h"
#include "mainwindow.h"
#include "Sender.h"

using namespace std;

int main(int argc, char *argv[])
{
    Sender sndr = Sender(); // sens to server computer
    // Sender sndr = Sender(0); // send to current computer. Needs Receiver rcvr = Receiver(0); in LuDServer main.

    // sendFile(file_to_send, new_name)
    sndr.sendFile("C:/Users/lenovo/Dropbox/Hello.docx","Works.docx");

    // requestFile(file_to_request, download_name)
    sndr.requestFile("C:/Users/Briggs 419 Server/Dropbox/Article/Document/Copy/Implement","C:/Programs/doesit.docx");

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
