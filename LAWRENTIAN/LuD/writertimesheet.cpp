#include "writertimesheet.h"

writerTimesheet::writerTimesheet()
{

}

writerTimesheet::~writerTimesheet()
{

}
int writerTimesheet::getWriterId()
{
    return writerId;
}

void writerTimesheet::setWriterId(int writerId)
{
    writerTimesheet::writerId = writerId;
}
bool writerTimesheet::getStaff() const
{
    return staff;
}

void writerTimesheet::setStaff(bool staff)
{
    writerTimesheet::staff = staff;
}
int writerTimesheet::getArticlesOnTime() const
{
    return articlesOnTime;
}

void writerTimesheet::setArticlesOnTime(int articlesOnTime)
{
    writerTimesheet::articlesOnTime = articlesOnTime;
}
int writerTimesheet::getArticlesLate() const
{
    return articlesLate;
}

void writerTimesheet::setArticlesLate(int articlesLate)
{
    writerTimesheet::articlesLate = articlesLate;
}
string writerTimesheet::getIssueDate() const
{
    return issueDate;
}

void writerTimesheet::setIssueDate(const string &issueDate)
{
    writerTimesheet::issueDate = issueDate;
}






