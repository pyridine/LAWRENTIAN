#ifndef NEWARTICLEWORKSPACEWINDOWDBC_H
#define NEWARTICLEWORKSPACEWINDOWDBC_H
#include "databasecontroller.h"
#include "client.h"
#include "article.h"
#include <utility>

using namespace std;

class NewArticleWorkspaceWindowDBC : public DatabaseController
{
public:
    NewArticleWorkspaceWindowDBC(Client* c);
    ~NewArticleWorkspaceWindowDBC();

    void addArticle(Article *newArticle);
    void deleteArticle(Article *newArticle);

    vector<pair<string, int> *>* getListOfWritersForSection(int sec);
    vector<pair<string, int> *>* getListOfPhotographers();


};

#endif // NEWARTICLEWORKSPACEWINDOWDBC_H
