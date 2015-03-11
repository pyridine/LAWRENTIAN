#ifndef ARTICLEWORKSPACEAANDEWIDGET_H
#define ARTICLEWORKSPACEAANDEWIDGET_H

#include <QWidget>
#include "articleworkspacedbc.h"
#include "logincredentials.h"

class articleWorkspace;

namespace Ui {
class ArticleWorkspaceAAndEWidget;
}

class ArticleWorkspaceAAndEWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArticleWorkspaceAAndEWidget(QWidget *parent = 0);
    ~ArticleWorkspaceAAndEWidget();

    void init(articleWorkspace *myparent, Client* c,LoginCredentials* crede);

    void openArticleWorkspace(Article* a);
    bool workspaceExists(int id);

private slots:
    void on_articleTextBrowser_anchorClicked(const QUrl &arg1);

public slots:
    void initTextBrowser();

private:
    Ui::ArticleWorkspaceAAndEWidget *ui;
    ArticleWorkspaceDBC *dbController;
    LoginCredentials *cred;
    Client *client;
    vector<int> existingIds;
    articleWorkspace *parent;
};

#endif // ARTICLEWORKSPACEAANDEWIDGET_H
