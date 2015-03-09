#ifndef ARTICLEWORKSPACEFEATURESWIDGET_H
#define ARTICLEWORKSPACEFEATURESWIDGET_H

#include <QWidget>
#include "articleworkspacedbc.h"
#include "logincredentials.h"

namespace Ui {
class ArticleWorkspaceFeaturesWidget;
}

class ArticleWorkspaceFeaturesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArticleWorkspaceFeaturesWidget(QWidget *parent = 0);
    ~ArticleWorkspaceFeaturesWidget();

    void init(Client* c,LoginCredentials* crede);
    void initTextBrowser();
    void openArticleWorkspace(Article* a);
    bool workspaceExists(int id);

private slots:
    void on_articleTextBrowser_anchorClicked(const QUrl &arg1);

    void on_refreshButton_clicked();

private:
    Ui::ArticleWorkspaceFeaturesWidget *ui;
    ArticleWorkspaceDBC *dbController;
    LoginCredentials *cred;
    Client *client;
    vector<int> existingIds;
};

#endif // ARTICLEWORKSPACEFEATURESWIDGET_H
