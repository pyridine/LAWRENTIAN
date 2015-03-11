#include "articleworkspacevarietywidget.h"
#include "ui_articleworkspacevarietywidget.h"

#include "newarticleworkspacewindow.h"
#include "articleworkspace.h"
#include <iostream>

ArticleWorkspaceVarietyWidget::ArticleWorkspaceVarietyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArticleWorkspaceVarietyWidget)
{
    ui->setupUi(this);
}

ArticleWorkspaceVarietyWidget::~ArticleWorkspaceVarietyWidget()
{
    delete ui;
}

void ArticleWorkspaceVarietyWidget::init(articleWorkspace *myParent, Client* c,LoginCredentials* crede)
{
    cred = crede;
    client = c;
    parent = myParent;
    dbController = new ArticleWorkspaceDBC(client);

    QDate selectedIssue = parent->getSelectedIssueDate();

    // Gets article titles for section
    vector<string> articleTitles = dbController->getArticleTitlesForSectionAndIssue("VARIETY_SECTION", selectedIssue);
    for (int i = 0; i < articleTitles.size(); i++){
        int articleId = dbController->getArticleId(articleTitles[i]);
        existingIds.push_back(articleId); // Keeps track of articles that already exist in database
    }
    QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(initTextBrowser()));
     timer->start(10000);
    initTextBrowser();
}

void ArticleWorkspaceVarietyWidget::initTextBrowser()
{
    ui->articleTextBrowser->clear();
    ui->articleTextBrowser->setOpenLinks(false);
    existingIds.clear();
    QDate selectedIssue = parent->getSelectedIssueDate();

    // Gets article titles for section
    vector<string> articleTitles = dbController->getArticleTitlesForSectionAndIssue("VARIETY_SECTION", selectedIssue);
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

bool ArticleWorkspaceVarietyWidget::workspaceExists(int id)
{
    for(int i = 0; i <existingIds.size(); i++){
        if(existingIds[i] == id){
            return true;
        }
    }
    return false;
}

void ArticleWorkspaceVarietyWidget::openArticleWorkspace(Article* a)
{
    //Init data
    newArticleWorkspaceWindow *createArticleWorkspaceWindow = new newArticleWorkspaceWindow();
    createArticleWorkspaceWindow->init(cred, this->parent);
    createArticleWorkspaceWindow->initDB(dbController->getClient());
    createArticleWorkspaceWindow->setupFields(a);

    //Init window
    //createArticleWorkspaceWindow->setParentVarietyWorkspaceWidget(this);
    createArticleWorkspaceWindow->setWindowModality(Qt::ApplicationModal);
    createArticleWorkspaceWindow->window()->show();
}

void ArticleWorkspaceVarietyWidget::on_articleTextBrowser_anchorClicked(const QUrl &arg1)
{
    string urlString = arg1.toString().toStdString();
    int urlInt = stoi(urlString); // Reads in articleId
    Article *article = dbController->getArticleById(urlInt);
    openArticleWorkspace(article);

}
