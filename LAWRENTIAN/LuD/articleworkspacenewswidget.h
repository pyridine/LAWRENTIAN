#ifndef ARTICLEWORKSPACENEWSWIDGET_H
#define ARTICLEWORKSPACENEWSWIDGET_H

#include <QWidget>
#include "client.h"
#include "logincredentials.h"
#include "articleworkspacedbc.h"

class articleWorkspace;

namespace Ui {
class ArticleWorkspaceNewsWidget;
}

class ArticleWorkspaceNewsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArticleWorkspaceNewsWidget(QWidget *parent = 0);
    ~ArticleWorkspaceNewsWidget();

    void init(articleWorkspace *myParent, Client* c,LoginCredentials* crede);
    void openArticleWorkspace(Article* a);
    bool workspaceExists(int id);

private slots:
    void on_articleTextBrowser_anchorClicked(const QUrl &arg1);

public slots:
    void initTextBrowser();

private:
    Ui::ArticleWorkspaceNewsWidget *ui;
    ArticleWorkspaceDBC *dbController;
    LoginCredentials *cred;
    Client *client;
    vector<int> existingIds;
    articleWorkspace *parent;
};

#endif // ARTICLEWORKSPACENEWSWIDGET_H
