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
    vector<int> collectWriterForTimesheet(QDate currentDate);
    void generateWriterTimesheet(int writerId, int articlesOnTime, int articlesLate, QDate issueDate);
    string collectArticleSection(int articleId);
    string collectArticleTitle(int articleId);
    vector<int> collectArticleIdForTimesheet(QDate currentDate, int writerId);

private:
    vector<int> *getAllArticleIDs();


};

#endif // ARTICLEWORKSPACEDBC_H
