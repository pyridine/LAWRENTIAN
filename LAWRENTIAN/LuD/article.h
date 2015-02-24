#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
#include <QString>

using namespace std;

class Article
{
public:
    Article(string issueDate, string title, string description, int section, int writerLUID, int photographerLUID);
    ~Article();

    string getIssueDate();
    QString QGetIssueDate();
    void setIssueDate(string issueDate);
    string getTitle();
    QString QGetTitle();
    void setTitle(string title);
    int getWriter();
    void setWriter(int writerLUID);
    int getPhotographer();
    void setPhotographer(int photographerLUID);
    int getId();
    void setId(int id);
    QString QGetDescription();
    string getDescription() const;
    void setDescription(const string &value);

    int getSection() const;
    void setSection(int value);

private:
    int id;
    string issueDate;
    string title;
    string description;
    int section;
    int writerLUID;
    int photographerLUID;
};

#endif // ARTICLE_H
