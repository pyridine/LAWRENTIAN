#ifndef ARTICLEWORKSPACEAANDEWIDGET_H
#define ARTICLEWORKSPACEAANDEWIDGET_H

#include <QWidget>
#include "articleworkspacedbc.h"
#include "logincredentials.h"

namespace Ui {
class ArticleWorkspaceAAndEWidget;
}

class ArticleWorkspaceAAndEWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArticleWorkspaceAAndEWidget(QWidget *parent = 0);
    ~ArticleWorkspaceAAndEWidget();

    void init(Client* c,LoginCredentials* crede);
    void initTextBrowser();
    void openArticleWorkspace(Article* a);
    bool workspaceExists(int id);

private slots:
    void on_articleTextBrowser_anchorClicked(const QUrl &arg1);

    void on_refreshButton_clicked();

private:
    Ui::ArticleWorkspaceAAndEWidget *ui;
    ArticleWorkspaceDBC *dbController;
    LoginCredentials *cred;
    Client *client;
    vector<int> existingIds;
};

#endif // ARTICLEWORKSPACEAANDEWIDGET_H
