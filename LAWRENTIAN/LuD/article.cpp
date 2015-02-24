#include "article.h"

Article::Article(string issueDate, string title, string description, int section, int writerLUID, int photographerLUID)
{
Article::issueDate = issueDate;
Article::title = title;
Article::description = description;
Article::section = section;
Article::writerLUID = writerLUID;
Article::photographerLUID = photographerLUID;
}

Article::~Article()
{

}

string Article::getIssueDate()
{
    return Article::issueDate;
}

void Article::setIssueDate(string issueDate)
{
    Article::issueDate = issueDate;
}

string Article::getTitle()
{
    return Article::title;
}

void Article::setTitle(string title)
{
    Article::title = title;
}

int Article::getWriter()
{
    return Article::writerLUID;
}

void Article::setWriter(int writer)
{
    Article::writerLUID = writer;
}

int Article::getPhotographer()
{
    return Article::photographerLUID;
}

void Article::setPhotographer(int photographer)
{
    Article::photographerLUID = photographer;
}
string Article::getDescription() const
{
    return description;
}

void Article::setDescription(const string &value)
{
    description = value;
}
int Article::getSection() const
{
    return section;
}

void Article::setSection(int value)
{
    section = value;
}
