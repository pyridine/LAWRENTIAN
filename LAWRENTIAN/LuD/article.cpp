#include "article.h"

Article::Article(string issueDate, string title, string description, string section, string writer, string photographer, string filePath)
{
issueDate = issueDate;
title = title;
description = description;
section = section;
writer = writer;
photographer = photographer;
filePath = filePath;
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

string Article::getWriter()
{
    return Article::writer;
}

void Article::setWriter(string writer)
{
    Article::writer = writer;
}

string Article::getPhotographer()
{
    return Article::photographer;
}

void Article::setPhotographer(string photographer)
{
    Article::photographer = photographer;
}
string Article::getDescription() const
{
    return description;
}

void Article::setDescription(const string &value)
{
    description = value;
}
string Article::getSection() const
{
    return section;
}

void Article::setSection(const string &value)
{
    section = value;
}
string Article::getFilePath() const
{
    return filePath;
}

void Article::setFilePath(const string &value)
{
    filePath = value;
}



