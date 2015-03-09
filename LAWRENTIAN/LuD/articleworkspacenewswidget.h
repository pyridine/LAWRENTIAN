#ifndef ARTICLEWORKSPACENEWSWIDGET_H
#define ARTICLEWORKSPACENEWSWIDGET_H

#include <QWidget>
#include "client.h"
#include "logincredentials.h"
#include "articleworkspacedbc.h"


namespace Ui {
class ArticleWorkspaceNewsWidget;
}

class ArticleWorkspaceNewsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArticleWorkspaceNewsWidget(QWidget *parent = 0);
    ~ArticleWorkspaceNewsWidget();

    void init(Client* c,LoginCredentials* crede);
    void initTextBrowser();
    void openArticleWorkspace(Article* a);
    bool workspaceExists(int id);

private slots:
    void on_articleTextBrowser_anchorClicked(const QUrl &arg1);

    void on_refreshButton_clicked();

private:
    Ui::ArticleWorkspaceNewsWidget *ui;
    ArticleWorkspaceDBC *dbController;
    LoginCredentials *cred;
    Client *client;
    vector<int> existingIds;
};

#endif // ARTICLEWORKSPACENEWSWIDGET_H
