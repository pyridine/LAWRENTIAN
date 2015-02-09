#ifndef WRITERTIMESHEET_H
#define WRITERTIMESHEET_H

#include <string>

using namespace std;

class writerTimesheet
{
public:
    writerTimesheet();
    ~writerTimesheet();

    int getWriterId();
    void setWriterId(int writerId);

    bool getStaff() const;
    void setStaff(bool staff);

    int getArticlesOnTime() const;
    void setArticlesOnTime(int articlesOnTime);

    int getArticlesLate() const;
    void setArticlesLate(int articlesLate);

    string getIssueDate() const;
    void setIssueDate(const string &issueDate);

private:
    int writerId;
    bool staff;
    int articlesOnTime;
    int articlesLate;
    string issueDate;
};

#endif // WRITERTIMESHEET_H
