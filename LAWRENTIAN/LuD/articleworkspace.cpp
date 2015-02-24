#include "articleworkspace.h"
#include "ui_articleworkspace.h"
#include "newarticleworkspacewindow.h"
#include "article.h"
#include "permissiondef.h"
#include "sectiondef.h"

#include <QPushButton>
#include <QString>
#include <QHBoxLayout>
#include <iostream>
#include <vector>

using namespace std;

articleWorkspace::articleWorkspace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::articleWorkspace)
{
    ui->setupUi(this);
    x = 50;
    y = 50;
}

articleWorkspace::~articleWorkspace()
{
    delete ui;
}

void articleWorkspace::initDB(Client* c){
    dbController = new ArticleWorkspaceDBC(c);
}

void articleWorkspace::on_pushButton_clicked()
{
    newArticleWorkspaceWindow *createArticleWorkspaceWindow = new newArticleWorkspaceWindow();
    createArticleWorkspaceWindow->initDB(dbController->getClient());
    createArticleWorkspaceWindow->setParentArticleWorkspaceWidget(this);
    createArticleWorkspaceWindow->setWindowModality(Qt::ApplicationModal);
    createArticleWorkspaceWindow->window()->show();
}

void articleWorkspace::initArticle(Article *article)
{
    articleVector.push_back(article);
}

void articleWorkspace::updateArticleList(LoginCredentials* c){

    //Didn't I need to initialize articlevector? :TODO :DEBUG :HEY_SEGFAULT
    __insertArticles(SectionDef::ARTSENT_SECTION,PermissionDef::SEC_ARTS,c);
    __insertArticles(SectionDef::FEATURES_SECTION,PermissionDef::SEC_FEATURES,c);
    __insertArticles(SectionDef::NEWS_SECTION,PermissionDef::SEC_NEWS,c);
    __insertArticles(SectionDef::OPED_SECTION,PermissionDef::SEC_OPED,c);
    __insertArticles(SectionDef::SPORTS_SECTION,PermissionDef::SEC_SPORTS,c);
    __insertArticles(SectionDef::VARIETY_SECTION,PermissionDef::SEC_VARIETY,c);

    resetArticleButtons();
}
void articleWorkspace::resetArticleButtons(){
    //TODO: delete all buttons.
    vector<Article*>::iterator it = articleVector.begin();
    while(it != articleVector.end()){
        this->addArticleButton(*it);
        it++;
    }
}

void articleWorkspace::__insertArticles(int section, int secPerf, LoginCredentials* c){
    if(c->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||c->hasPermission(PermissionDef::SEC_ALL)
            ||c->hasPermission(secPerf)){
        vector<Article*>* newvit = dbController->getSectionArticles(section);
        articleVector.insert(articleVector.end(),newvit->begin(),newvit->end());
    }
}



void articleWorkspace::addArticleButton(Article *article)
{
    QString title = QString::fromStdString(article->getTitle());
    QString section = QString::fromStdString(dbController->translateSection(article->getSection()));
    QString buttonTitle = section+": "+title;
    QPushButton *newArticleButton = new QPushButton(buttonTitle, this);
    newArticleButton->setObjectName(title);

    newArticleButton->setGeometry(x, y, 500, 32);
    newArticleButton->show();
    connect(newArticleButton, SIGNAL(clicked()), this, SLOT(handleButton()));
    y = y+30;
}

void articleWorkspace::handleButton()
{
    QObject *senderObj = sender();
    QString senderObjName = senderObj->objectName();
    int count = 0;
    int size = articleVector.size();
    while (count != size){
        Article* send = articleVector[count];
        QString sendTitle = QString::fromStdString(send->getTitle());
        if(sendTitle == senderObjName){
            newArticleWorkspaceWindow *editArticleWorkspaceWindow = new newArticleWorkspaceWindow();
            editArticleWorkspaceWindow->initDB(dbController->getClient());
            editArticleWorkspaceWindow->setParentArticleWorkspaceWidget(this);
            editArticleWorkspaceWindow->setupFields(send);
            editArticleWorkspaceWindow->window()->show();
        }
        count++;
    }
}

bool articleWorkspace::workspaceExists(string articleTitle)
{
    int count = 0;
    int size = articleVector.size();
    while (count != size){
        Article* send = articleVector[count];
        string sendTitle = send->getTitle();
        if(sendTitle == articleTitle){
            return true;
        }
        count++;
    }
    return false;
}
