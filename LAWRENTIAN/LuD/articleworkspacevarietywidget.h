#ifndef ARTICLEWORKSPACEVARIETYWIDGET_H
#define ARTICLEWORKSPACEVARIETYWIDGET_H

#include <QWidget>
#include "articleworkspacedbc.h"
#include "logincredentials.h"

namespace Ui {
class ArticleWorkspaceVarietyWidget;
}

class ArticleWorkspaceVarietyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArticleWorkspaceVarietyWidget(QWidget *parent = 0);
    ~ArticleWorkspaceVarietyWidget();

    void init(Client* c,LoginCredentials* crede);
    void initTextBrowser();
    void openArticleWorkspace(Article* a);
    bool workspaceExists(int id);

private slots:
    void on_articleTextBrowser_anchorClicked(const QUrl &arg1);

    void on_refreshButton_clicked();

private:
    Ui::ArticleWorkspaceVarietyWidget *ui;
    ArticleWorkspaceDBC *dbController;
    LoginCredentials *cred;
    Client *client;
    vector<int> existingIds;
};

#endif // ARTICLEWORKSPACEVARIETYWIDGET_H
