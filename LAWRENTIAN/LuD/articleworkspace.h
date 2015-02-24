#ifndef ARTICLEWORKSPACE_H
#define ARTICLEWORKSPACE_H

#include "article.h"
#include "client.h"
#include "articleworkspacedbc.h"
#include "logincredentials.h"

#include <QWidget>
#include <QString>
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
    void initDB(Client* c);
    int x;
    int y;

    void updateArticleList(LoginCredentials* c);

    void resetArticleButtons();

    Article *getNewArticle() const;
    void setNewArticle(Article *value);
    bool workspaceExists(string articleTitle);

private slots:
    void on_pushButton_clicked();
    void handleButton();

private:
    Ui::articleWorkspace *ui;
    vector<Article *> articleVector;
    void __insertArticles(int section, int secPerf, LoginCredentials *c);
    ArticleWorkspaceDBC* dbController;
};

#endif // ARTICLEWORKSPACE_H
