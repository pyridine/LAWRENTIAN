#include "article.h"

article::article()
{

}

article::~article()
{

}

string article::getIssueDate()
{
    return article::issueDate;
}

void article::setIssueDate(string issueDate)
{
    article::issueDate = issueDate;
}

string article::getIssueVolume()
{
    return article::issueVolume;
}

void article::setIssueVolume(string issueVolume)
{
    article::issueVolume = issueVolume;
}

string article::getTitle()
{
    return article::title;
}

void article::setTitle(string title)
{
    article::title = title;
}

string article::getWriter()
{
    return article::writer;
}

void article::setWriter(string writer)
{
    article::writer = writer;
}

string article::getPhotographer()
{
    return article::photographer;
}

void article::setPhotographer(string photographer)
{
    article::photographer = photographer;
}
