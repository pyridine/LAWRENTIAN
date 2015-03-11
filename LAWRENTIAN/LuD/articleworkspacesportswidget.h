#ifndef ARTICLEWORKSPACESPORTSWIDGET_H
#define ARTICLEWORKSPACESPORTSWIDGET_H

#include <QWidget>
#include "articleworkspacedbc.h"
#include "logincredentials.h"

class articleWorkspace;

namespace Ui {
class ArticleWorkspaceSportsWidget;
}

class ArticleWorkspaceSportsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArticleWorkspaceSportsWidget(QWidget *parent = 0);
    ~ArticleWorkspaceSportsWidget();

    void init(articleWorkspace *myParent, Client* c,LoginCredentials* crede);
    void openArticleWorkspace(Article* a);
    bool workspaceExists(int id);

private slots:
    void on_articleTextBrowser_anchorClicked(const QUrl &arg1);

public slots:
    void initTextBrowser();

private:
    Ui::ArticleWorkspaceSportsWidget *ui;
    ArticleWorkspaceDBC *dbController;
    LoginCredentials *cred;
    Client *client;
    vector<int> existingIds;
    articleWorkspace *parent;
};

#endif // ARTICLEWORKSPACESPORTSWIDGET_H
