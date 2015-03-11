#ifndef ARTICLEWORKSPACEOPEDWIDGET_H
#define ARTICLEWORKSPACEOPEDWIDGET_H

#include <QWidget>
#include "articleworkspacedbc.h"
#include "logincredentials.h"

class articleWorkspace;

namespace Ui {
class ArticleWorkspaceOpEdWidget;
}

class ArticleWorkspaceOpEdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArticleWorkspaceOpEdWidget(QWidget *parent = 0);
    ~ArticleWorkspaceOpEdWidget();

    void init(articleWorkspace *myParent, Client* c,LoginCredentials* crede);
    void openArticleWorkspace(Article* a);
    bool workspaceExists(int id);

private slots:
    void on_articleTextBrowser_anchorClicked(const QUrl &arg1);

public slots:
    void initTextBrowser();

private:
    Ui::ArticleWorkspaceOpEdWidget *ui;
    ArticleWorkspaceDBC *dbController;
    LoginCredentials *cred;
    Client *client;
    vector<int> existingIds;
    articleWorkspace *parent;
};

#endif // ARTICLEWORKSPACEOPEDWIDGET_H
