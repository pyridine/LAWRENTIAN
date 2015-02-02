#include "registrationwindow.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RegistrationWindow w;
    w.show();

    return a.exec();
}
