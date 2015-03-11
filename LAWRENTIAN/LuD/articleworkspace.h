#ifndef ARTICLEWORKSPACE_H
#define ARTICLEWORKSPACE_H

#include "article.h"
#include "client.h"
#include "articleworkspacedbc.h"
#include "logincredentials.h"
#include "mainwindow.h"
#include "articleworkspacenewswidget.h"
#include "articleworkspacefeatureswidget.h"
#include "articleworkspaceopedwidget.h"
#include "articleworkspaceaandewidget.h"
#include "articleworkspacesportswidget.h"
#include "articleworkspacevarietywidget.h"

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <string>
#include <QVBoxLayout>
#include "FileSystem.h"
#include <vector>

using namespace std;

namespace Ui {
class articleWorkspace;
}

class articleWorkspace : public QWidget
{
    Q_OBJECT

public:
    explicit articleWorkspace(QWidget *parent = 0);
    ~articleWorkspace();
    //void initArticle(Article *article);
    //void addArticleButton(Article *article);
    void init(MainWindow* parent, Client* c,LoginCredentials* cred);
    int x;
    int y;
    QDate getSelectedIssueDate();
    void populateIssueComboBox();
    //bool workspaceExists(string articleTitle);

    //void updateArticleList();

    //void resetArticleButtons();

    Article *getNewArticle() const;
    void setNewArticle(Article *value);
    void submitToArchive();
    QTabWidget *tabs;
    ArticleWorkspaceNewsWidget *getNewsWidget();
    ArticleWorkspaceFeaturesWidget *getFeaturesWidget();
    ArticleWorkspaceOpEdWidget *getOpEdWidget();
    ArticleWorkspaceAAndEWidget *getAAndEWidget();
    ArticleWorkspaceSportsWidget *getSportsWidget();
    ArticleWorkspaceVarietyWidget *getVarietyWidget();
    bool getViewingArchive();

private slots:
    void on_addArticleWorkspace_pushButton_clicked();
    //void handleButton();

    void openArticleWorkspace(Article* a);

    void on_submitToArchiveButton_clicked();

    void on_issueDateComboBox_currentIndexChanged(const QString &arg1);

    void on_currentIssueButton_clicked();

private:
    void handlePermissions();
    QVBoxLayout * vert_layout;
    Ui::articleWorkspace *ui;
    MainWindow *parentWindow;
    vector<Article*> articleVector;
    //void __insertArticles(int section, int secPerf);
    ArticleWorkspaceDBC* dbController;
    vector<QPushButton*> buttonVector;
    //void clearLayout(QVBoxLayout* vb_layout);
    LoginCredentials* cred;
    Client *client;
    FileSystem::VerSeq ver_seq;
    ArticleWorkspaceNewsWidget *newsWidget;
    ArticleWorkspaceFeaturesWidget *featuresWidget;
    ArticleWorkspaceOpEdWidget *opEdWidget;
    ArticleWorkspaceAAndEWidget *aAndEWidget;
    ArticleWorkspaceSportsWidget *sportsWidget;
    ArticleWorkspaceVarietyWidget *varietyWidget;
    articleWorkspace *articleWorkspaceParent;
    bool viewingArchive;

};

#endif // ARTICLEWORKSPACE_H
