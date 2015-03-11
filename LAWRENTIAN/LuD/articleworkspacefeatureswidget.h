#ifndef ARTICLEWORKSPACEFEATURESWIDGET_H
#define ARTICLEWORKSPACEFEATURESWIDGET_H

#include <QWidget>
#include "articleworkspacedbc.h"
#include "logincredentials.h"

class articleWorkspace;

namespace Ui {
class ArticleWorkspaceFeaturesWidget;
}

class ArticleWorkspaceFeaturesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArticleWorkspaceFeaturesWidget(QWidget *parent = 0);
    ~ArticleWorkspaceFeaturesWidget();

    void init(articleWorkspace *myParent, Client* c,LoginCredentials* crede);
    void openArticleWorkspace(Article* a);
    bool workspaceExists(int id);

private slots:
    void on_articleTextBrowser_anchorClicked(const QUrl &arg1);

public slots:
    void initTextBrowser();

private:
    Ui::ArticleWorkspaceFeaturesWidget *ui;
    ArticleWorkspaceDBC *dbController;
    LoginCredentials *cred;
    Client *client;
    vector<int> existingIds;
    articleWorkspace *parent;
};

#endif // ARTICLEWORKSPACEFEATURESWIDGET_H
