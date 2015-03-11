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
    vector<string> getArticleTitlesForSectionAndIssue(string section, QDate issueDate);
    string getArticleDescription(string title);
    string getArticleWriter(string title);
    int getArticleId(string title);
    Article* getArticleById(int articleId);
    QDate collectLatestIssueDate();
    vector<QString> getIssueDateList();

private:
    vector<int> *getAllArticleIDs();


};

#endif // ARTICLEWORKSPACEDBC_H
