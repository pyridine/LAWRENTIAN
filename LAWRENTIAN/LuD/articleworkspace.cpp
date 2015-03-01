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

void articleWorkspace::initDB(Client* c,LoginCredentials* cred){
    dbController = new ArticleWorkspaceDBC(c);
    credentials = cred;

}


void articleWorkspace::openArticleWorkspace(Article* a){
    //Init data
    newArticleWorkspaceWindow *createArticleWorkspaceWindow = new newArticleWorkspaceWindow();
    createArticleWorkspaceWindow->initDB(dbController->getClient());
    createArticleWorkspaceWindow->setupFields(a);

    //Init window
    createArticleWorkspaceWindow->setParentArticleWorkspaceWidget(this);
    createArticleWorkspaceWindow->setWindowModality(Qt::ApplicationModal);
    createArticleWorkspaceWindow->window()->show();


}

void articleWorkspace::on_addArticleWorkspace_pushButton_clicked()
{

    //Set the article's date for the next Wednesday.
    QDate todate = QDate::currentDate();
    while(todate.dayOfWeek() != 3 /*Wednesday*/){
        todate = todate.addDays(1);
    }
    QString dateFormat("yyyy-MM-dd");
    string dateString = todate.toString(dateFormat).toStdString();
    Article* newArticle = new Article(dateString,"Article Title","Article Description",
                                      0 /*Default to first section*/,
                                      -1 /*Nobody assigned*/,
                                      -1 /*Nobody assigned*/);
    newArticle->setId(dbController->getNextAvailableArticleID());
    openArticleWorkspace(newArticle);
}

void articleWorkspace::initArticle(Article *article)
{
    articleVector.push_back(article);
}

void articleWorkspace::updateArticleList(){
    vector<Article*> newArtVect;
    articleVector = newArtVect;


    //Didn't I need to initialize articlevector? :TODO :DEBUG :HEY_SEGFAULT
    __insertArticles(SectionDef::ARTSENT_SECTION,PermissionDef::SEC_ARTS);
    __insertArticles(SectionDef::FEATURES_SECTION,PermissionDef::SEC_FEATURES);
    __insertArticles(SectionDef::NEWS_SECTION,PermissionDef::SEC_NEWS);
    __insertArticles(SectionDef::OPED_SECTION,PermissionDef::SEC_OPED);
    __insertArticles(SectionDef::SPORTS_SECTION,PermissionDef::SEC_SPORTS);
    __insertArticles(SectionDef::VARIETY_SECTION,PermissionDef::SEC_VARIETY);

    resetArticleButtons();
}
void articleWorkspace::resetArticleButtons(){
    //TODO: delete all buttons.
   //buttonVector.empty();
    vector<Article*>::iterator it = articleVector.begin();
    while(it != articleVector.end()){
        this->addArticleButton(*it);
        it++;
    }
}

void articleWorkspace::__insertArticles(int section, int secPerf){

    if(credentials->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||credentials->hasPermission(PermissionDef::SEC_ALL)
            ||credentials->hasPermission(secPerf)){
        vector<Article*>* newvit = dbController->getSectionArticles(section);
        articleVector.insert(articleVector.end(),newvit->begin(),newvit->end());
    }
}

void articleWorkspace::addArticleButton(Article *article)
{
    QString title = article->QGetTitle();
    QString section = QString::fromStdString(dbController->translateSection(article->getSection()));
    QString buttonTitle = section+": "+title;
    /*QPushButton *newArticleButton;
    buttonVector.push_back(newArticleButton);
    buttonVector.back() = new QPushButton(buttonTitle, this);
    buttonVector.back()->setObjectName(title);

    buttonVector.back()->setGeometry(x, y, 500, 32);
    buttonVector.back()->show();
    connect(buttonVector.back(), SIGNAL(clicked()), this, SLOT(handleButton()));*/
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
        QString sendTitle = send->QGetTitle();
        if(sendTitle == senderObjName){
            openArticleWorkspace(send);
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
