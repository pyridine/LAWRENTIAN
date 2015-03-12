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
    void deleteArticle(int articleID);
    void addMyPhotos(QStringList &imgPaths, int articleID,
                     int sectionID, int photographerID);
    void deleteMyPhotos(int articleId);
    bool isArticleTitleExistent(string title);
    bool isArticleTitleAlreadyInUse(string title, int id);
    QDate collectLatestIssueDate();


    string translateWriterName(int luid);

    vector<pair<string, int> *>* getListOfWritersForSection(int section, int currentWriter); //See documentation
    vector<pair<string, int> *>* getListOfPhotographers(int curentPhotographer); //See documentation


};

#endif // NEWARTICLEWORKSPACEWINDOWDBC_H
