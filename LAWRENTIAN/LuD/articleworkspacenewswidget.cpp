#include "articleworkspacenewswidget.h"
#include "ui_articleworkspacenewswidget.h"

#include "newarticleworkspacewindow.h"
#include "articleworkspace.h"
#include <iostream>

ArticleWorkspaceNewsWidget::ArticleWorkspaceNewsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArticleWorkspaceNewsWidget)
{
    ui->setupUi(this);
}

void ArticleWorkspaceNewsWidget::init(articleWorkspace *myParent, Client* c,LoginCredentials* crede)
{
    cout<<"About to initialize stuff"<<endl;
    cred = crede;
    client = c;
    parent = myParent;
    dbController = new ArticleWorkspaceDBC(client);

    cout<<"About to get selected date"<<endl;
    QDate selectedIssue = parent->getSelectedIssueDate();

    // Gets article titles for section
    vector<string> articleTitles = dbController->getArticleTitlesForSectionAndIssue("NEWS_SECTION", selectedIssue);
    for (int i = 0; i < articleTitles.size(); i++){
        int articleId = dbController->getArticleId(articleTitles[i]);
        existingIds.push_back(articleId); // Keeps track of articles that already exist in database
    }
    QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(initTextBrowser()));
     timer->start(10000);
    initTextBrowser();
}

ArticleWorkspaceNewsWidget::~ArticleWorkspaceNewsWidget()
{
    delete ui;
}

void ArticleWorkspaceNewsWidget::initTextBrowser()
{
    ui->articleTextBrowser->clear();
    ui->articleTextBrowser->setOpenLinks(false);
    existingIds.clear();
    QDate selectedIssue = parent->getSelectedIssueDate();

    // Gets article titles for section
    vector<string> articleTitles = dbController->getArticleTitlesForSectionAndIssue("NEWS_SECTION", selectedIssue);
    for(int i = 0; i < articleTitles.size(); i++)
    {
        QString articleTitle = QString::fromStdString(articleTitles[i]);
        QString articleWriter = QString::fromStdString(dbController->getArticleWriter(articleTitles[i]));
        int articleId = dbController->getArticleId(articleTitles[i]);
        existingIds.push_back(articleId); // Keeps track of articles that already exist in the textBrowser
        QString articleIdQString = QString::number(articleId);
        QString articleGeneralTitle = "<html><strong>"+articleTitle+"</ins></strong></html>";
        QString url = "<a href="+articleIdQString+">"+articleGeneralTitle+"</a>";
        if(cred->getName()==articleWriter){
            QString assignedText = "<font color=\"#00CC00\">Assigned</font>";
            QString titleText = "<table width=\"100%\" cellspacing=\"0\" border=\"0\"><tr class=\"address\"> "
                    "<td width=\"80%\" align=\"left\">"+url+" - "+articleWriter+"</td> "
                    "<td width=\"20%\" align=\"right\">"+assignedText+"</td></tr></table>";
            ui->articleTextBrowser->append(titleText);
        } else {
            ui->articleTextBrowser->append(url+" - "+articleWriter);
        }
        QString articleDescription = QString::fromStdString(dbController->getArticleDescription(articleTitles[i]));
        QString descriptionText = articleDescription;
        ui->articleTextBrowser->append("<span><table><div align=\"left\">"+descriptionText+"</div></table></span>");
        ui->articleTextBrowser->append("<table width=\"100%\"><tr><td><hr /></td></tr></table>");
    }
}

bool ArticleWorkspaceNewsWidget::workspaceExists(int id)
{
    for(int i = 0; i <existingIds.size(); i++){
        cout<<"Checking workspaceExists for id: "<<i<<endl;
        if(existingIds[i] == id){
            return true;
        }
    }
    return false;
}

void ArticleWorkspaceNewsWidget::openArticleWorkspace(Article* a)
{
    //Init data
    newArticleWorkspaceWindow *createArticleWorkspaceWindow = new newArticleWorkspaceWindow();
    createArticleWorkspaceWindow->init(cred, this->parent);
    createArticleWorkspaceWindow->initDB(dbController->getClient());
    createArticleWorkspaceWindow->setupFields(a);

    //Init window
    //createArticleWorkspaceWindow->setParentNewsWorkspaceWidget(this);
    createArticleWorkspaceWindow->setWindowModality(Qt::ApplicationModal);
    createArticleWorkspaceWindow->window()->show();
}

void ArticleWorkspaceNewsWidget::on_articleTextBrowser_anchorClicked(const QUrl &arg1)
{
    string urlString = arg1.toString().toStdString();
    int urlInt = stoi(urlString); // Reads in articleId
    Article *article = dbController->getArticleById(urlInt);
    openArticleWorkspace(article);

}
