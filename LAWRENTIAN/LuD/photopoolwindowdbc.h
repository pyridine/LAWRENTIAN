#ifndef PHOTOPOOLDBC_H
#define PHOTOPOOLDBC_H

#include "databasecontroller.h"
#include <QStringList>
#include <vector>
#include <string>

class PhotoPoolWindowDBC : public DatabaseController
{
public:
    typedef std::pair<int,std::string> Sec_t;

    PhotoPoolWindowDBC(Client* c);
    //PhotoPoolWindowDBC();
    ~PhotoPoolWindowDBC();
    QStringList getArtsFromSec(int sec, const QString& fromIssueDate, const QString& toIssueDate);
    QStringList getArtsFromSec(int sec);
    QStringList getIssueDates();
    string getIssueDateOfArt(QString title);
    std::vector<PhotoPoolWindowDBC::Sec_t> getSections();
};

#endif // PHOTOPOOLDBC_H
