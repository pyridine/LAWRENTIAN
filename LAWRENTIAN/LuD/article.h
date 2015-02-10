#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

using namespace std;

class Article
{
public:
    Article(string issueDate, string title, string description, string section, string writer, string photographer, string filePath);
    ~Article();

    string getIssueDate();
    void setIssueDate(string issueDate);
    string getTitle();
    void setTitle(string title);
    string getWriter();
    void setWriter(string writer);
    string getPhotographer();
    void setPhotographer(string photographer);

    string getDescription() const;
    void setDescription(const string &value);

    string getSection() const;
    void setSection(const string &value);

    string getFilePath() const;
    void setFilePath(const string &value);

private:
    int id; // Necessary?
    string issueDate;
    string title;
    string description;
    string section;
    string writer; //int?
    string photographer; //int?
    string filePath;
};

#endif // ARTICLE_H
