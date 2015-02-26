#ifndef ARTICLEWORKSPACEDBC_H
#define ARTICLEWORKSPACEDBC_H

#include <utility>
#include "databasecontroller.h"
#include "article.h"

using namespace std;

class ArticleWorkspaceDBC : public DatabaseController
{
public:
    ArticleWorkspaceDBC(Client *c);
    ~ArticleWorkspaceDBC();
    vector<Article*>* getSectionArticles(int section);
    int getNextAvailableArticleID();

private:
    vector<int> *getAllArticleIDs();


};

#endif // ARTICLEWORKSPACEDBC_H
