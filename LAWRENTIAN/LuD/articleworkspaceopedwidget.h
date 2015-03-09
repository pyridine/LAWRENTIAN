#ifndef ARTICLEWORKSPACEOPEDWIDGET_H
#define ARTICLEWORKSPACEOPEDWIDGET_H

#include <QWidget>
#include "articleworkspacedbc.h"
#include "logincredentials.h"

namespace Ui {
class ArticleWorkspaceOpEdWidget;
}

class ArticleWorkspaceOpEdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArticleWorkspaceOpEdWidget(QWidget *parent = 0);
    ~ArticleWorkspaceOpEdWidget();

    void init(Client* c,LoginCredentials* crede);
    void initTextBrowser();
    void openArticleWorkspace(Article* a);
    bool workspaceExists(int id);

private slots:
    void on_articleTextBrowser_anchorClicked(const QUrl &arg1);

    void on_refreshButton_clicked();

private:
    Ui::ArticleWorkspaceOpEdWidget *ui;
    ArticleWorkspaceDBC *dbController;
    LoginCredentials *cred;
    Client *client;
    vector<int> existingIds;
};

#endif // ARTICLEWORKSPACEOPEDWIDGET_H
