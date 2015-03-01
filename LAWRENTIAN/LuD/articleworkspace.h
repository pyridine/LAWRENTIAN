#ifndef ARTICLEWORKSPACE_H
#define ARTICLEWORKSPACE_H

#include "article.h"
#include "client.h"
#include "articleworkspacedbc.h"
#include "logincredentials.h"

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <string>

using namespace std;

namespace Ui {
class articleWorkspace;
}

class articleWorkspace : public QWidget
{
    Q_OBJECT

public:
    explicit articleWorkspace(QWidget *parent = 0);
    ~articleWorkspace();
    void initArticle(Article *article);
    void addArticleButton(Article *article);
    void initDB(Client* c,LoginCredentials* cred);
    int x;
    int y;

    void updateArticleList();

    void resetArticleButtons();

    Article *getNewArticle() const;
    void setNewArticle(Article *value);
    bool workspaceExists(string articleTitle);

private slots:
    void on_addArticleWorkspace_pushButton_clicked();
    void handleButton();

    void openArticleWorkspace(Article* a);

private:
    LoginCredentials* credentials;
    Ui::articleWorkspace *ui;
    vector<Article*> articleVector;
    void __insertArticles(int section, int secPerf);
    ArticleWorkspaceDBC* dbController;
    vector<QPushButton*> buttonVector;
};

#endif // ARTICLEWORKSPACE_H
