#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

using namespace std;

class article
{
public:
    article();
    ~article();

    string getIssueDate();
    void setIssueDate(string issueDate);
    string getIssueVolume();
    void setIssueVolume(string issueVolume);
    string getTitle();
    void setTitle(string title);
    string getWriter();
    void setWriter(string writer);
    string getPhotographer();
    void setPhotographer(string photographer);

private:
    int id; // Necessary?
    string issueDate;
    string issueVolume;
    string title;
    string writer; //int?
    string photographer; //int?
};

#endif // ARTICLE_H
