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
    static void showInformationAlert(string title, string msg);
    static int showQuestionAlert(string title, string msg);
    int showWarningAlert(string title, string msg);
};

#endif // ALERT_H
