#include "registrationwindow.h"
#include <QApplication>
#include "remotedbconnection.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RegistrationWindow w;
    w.show();

    RemoteDBConnection con;
    if(con.Connect())
    {
    con.sampleQuery();
    }

    return a.exec();
}
