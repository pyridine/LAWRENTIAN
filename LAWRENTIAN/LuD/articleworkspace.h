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
#include <QVBoxLayout>

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
    void init(Client* c,LoginCredentials* cred);
    int x;
    int y;
    bool workspaceExists(string articleTitle);

    void updateArticleList();

    void resetArticleButtons();

    Article *getNewArticle() const;
    void setNewArticle(Article *value);

private slots:
    void on_addArticleWorkspace_pushButton_clicked();
    void handleButton();

    void openArticleWorkspace(Article* a);

private:
    void handlePermissions();
    QVBoxLayout * vert_layout;
    Ui::articleWorkspace *ui;
    vector<Article*> articleVector;
    void __insertArticles(int section, int secPerf);
    ArticleWorkspaceDBC* dbController;
    vector<QPushButton*> buttonVector;
    void clearLayout(QVBoxLayout* vb_layout);
    LoginCredentials* cred;

};

#endif // ARTICLEWORKSPACE_H
