#ifndef ARTICLEWORKSPACEVARIETYWIDGET_H
#define ARTICLEWORKSPACEVARIETYWIDGET_H

#include <QWidget>
#include "articleworkspacedbc.h"
#include "logincredentials.h"

class articleWorkspace;

namespace Ui {
class ArticleWorkspaceVarietyWidget;
}

class ArticleWorkspaceVarietyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArticleWorkspaceVarietyWidget(QWidget *parent = 0);
    ~ArticleWorkspaceVarietyWidget();

    void init(articleWorkspace *myParent, Client* c,LoginCredentials* crede);
    void openArticleWorkspace(Article* a);
    bool workspaceExists(int id);

private slots:
    void on_articleTextBrowser_anchorClicked(const QUrl &arg1);

public slots:
    void initTextBrowser();

private:
    Ui::ArticleWorkspaceVarietyWidget *ui;
    ArticleWorkspaceDBC *dbController;
    LoginCredentials *cred;
    Client *client;
    vector<int> existingIds;
    articleWorkspace *parent;
};

#endif // ARTICLEWORKSPACEVARIETYWIDGET_H
