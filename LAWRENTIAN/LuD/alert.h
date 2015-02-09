#ifndef ALERT_H
#define ALERT_H
#include <string>
#include <qmessagebox.h>
#include <qstring.h>

using namespace std;

class Alert
{
public:
    Alert();
    ~Alert();
    static void showAlert(string title, string msg);
};

#endif // ALERT_H
