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

QString Article::QGetIssueDate()
{
    return QString::fromStdString(issueDate);
}

void Article::setIssueDate(string issueDate)
{
    Article::issueDate = issueDate;
}

QString Article::QGetTitle()
{
    return QString::fromStdString(title);
}

string Article::getTitle()
{
    return title;
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

int Article::getId()
{
    return id;
}

void Article::setId(int id)
{
    this->id = id;
}

QString Article::QGetDescription()
{
    return QString::fromStdString(description);
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
