#ifndef IDEA_H
#define IDEA_H

#include <string>

using namespace std;

class idea
{
public:
    idea();
    ~idea();

    string getTitle();
    void setTitle(string title);
    string getDescription();
    void setDescription(string description);
    string getExpirationDate();
    void setExpirationDate(string expirationDate);
    string getSection();
    void setSection(string section);

private:
    string title;
    string description;
    string expirationDate;
    string section;
};

#endif // IDEA_H
