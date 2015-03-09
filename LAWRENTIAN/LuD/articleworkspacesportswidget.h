#ifndef ARTICLEWORKSPACESPORTSWIDGET_H
#define ARTICLEWORKSPACESPORTSWIDGET_H

#include <QWidget>
#include "articleworkspacedbc.h"
#include "logincredentials.h"

namespace Ui {
class ArticleWorkspaceSportsWidget;
}

class ArticleWorkspaceSportsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArticleWorkspaceSportsWidget(QWidget *parent = 0);
    ~ArticleWorkspaceSportsWidget();

    void init(Client* c,LoginCredentials* crede);
    void initTextBrowser();
    void openArticleWorkspace(Article* a);
    bool workspaceExists(int id);

private slots:
    void on_articleTextBrowser_anchorClicked(const QUrl &arg1);

    void on_refreshButton_clicked();

private:
    Ui::ArticleWorkspaceSportsWidget *ui;
    ArticleWorkspaceDBC *dbController;
    LoginCredentials *cred;
    Client *client;
    vector<int> existingIds;
};

#endif // ARTICLEWORKSPACESPORTSWIDGET_H
