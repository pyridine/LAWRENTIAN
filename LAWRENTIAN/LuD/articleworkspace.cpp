#include "articleworkspace.h"
#include "ui_articleworkspace.h"
#include "newarticleworkspacewindow.h"
#include "article.h"
#include "permissiondef.h"
#include "sectiondef.h"
#include "alert.h"
#include "Sender.h"
#include "FileSystem.h"

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
    vert_layout = new QVBoxLayout;
}

articleWorkspace::~articleWorkspace()
{
    delete ui;
}

void articleWorkspace::init(MainWindow *parent, Client* c,LoginCredentials* crede)
{
    dbController = new ArticleWorkspaceDBC(c);
    cred = crede;
    parentWindow = parent;

    handlePermissions();
}
void articleWorkspace::handlePermissions(){
    //Det whether to hide the add_workspace button.
    if(!cred->hasPermission(PermissionDef::ADMIN_PTOKEN)
            && !cred->hasPermission(PermissionDef::EDIT_ARTICLE_WORKSPACE))
        this->ui->addArticleWorkspace_pushButton->setEnabled(false);
}


void articleWorkspace::openArticleWorkspace(Article* a){
    //Init data
    newArticleWorkspaceWindow *createArticleWorkspaceWindow = new newArticleWorkspaceWindow(this,cred);
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
    if(todate.dayOfWeek() == 3)
        todate = todate.addDays(7);
    while(todate.dayOfWeek() != 3 /*Wednesday*/)
        todate = todate.addDays(1);
    QString dateFormat(df::dbFormat);
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

void articleWorkspace::updateArticleList()
{
    articleVector.clear();

    __insertArticles(SectionDef::ARTSENT_SECTION,PermissionDef::SEC_ARTS);

    __insertArticles(SectionDef::FEATURES_SECTION,PermissionDef::SEC_FEATURES);
    __insertArticles(SectionDef::NEWS_SECTION,PermissionDef::SEC_NEWS);
    __insertArticles(SectionDef::OPED_SECTION,PermissionDef::SEC_OPED);
    __insertArticles(SectionDef::SPORTS_SECTION,PermissionDef::SEC_SPORTS);
    __insertArticles(SectionDef::VARIETY_SECTION,PermissionDef::SEC_VARIETY);

    resetArticleButtons();
}
void articleWorkspace::resetArticleButtons()
{
    //TODO: delete all buttons.
    //buttonVector.empty();
    clearLayout(vert_layout);
    vector<Article*>::iterator it = articleVector.begin();
    while(it != articleVector.end())
    {
        this->addArticleButton(*it);
        it++;
    }
    cout << "number of article buttons" << vert_layout->count() << endl;
}

void articleWorkspace::__insertArticles(int section, int secPerf)
{

    if(cred->hasPermission(PermissionDef::ADMIN_PTOKEN)
            ||cred->hasPermission(PermissionDef::SEC_ALL)
            ||cred->hasPermission(secPerf))
    {
        // nice.
        //I know, right? This is a really great function.
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

    vert_layout->addWidget(newArticleButton);
    QWidget *layout_widget = new QWidget;
    layout_widget->setLayout(vert_layout);
    ui->buttons_scrollArea->setWidget(layout_widget);

    connect(newArticleButton, SIGNAL(clicked()), this, SLOT(handleButton()));
    y = y+30;
}

void articleWorkspace::handleButton()
{
    QObject *senderObj = sender();
    QString senderObjName = senderObj->objectName();
    int count = 0;
    int size = articleVector.size();
    while (count != size)
    {
        Article* send = articleVector[count];
        QString sendTitle = send->QGetTitle();
        if(sendTitle == senderObjName)
        {
            openArticleWorkspace(send);
        }
        count++;
    }
}

void articleWorkspace::clearLayout(QVBoxLayout* vb_layout)
{
    while(!vb_layout->isEmpty())
    {
        QLayoutItem* item = vb_layout->itemAt(0);
        vb_layout->removeItem(item);
    }
    cout << "layout cleared." << endl;
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

void articleWorkspace::submitToArchive()
{

}

void articleWorkspace::generateTimesheet()
{
    QDate currentDate = QDate::currentDate();
    vector<int> writerIds = dbController->collectWriterForTimesheet(currentDate);

        for(int i = 0; i<writerIds.size(); i++){
            pair<int, int> submissionDate = calculateArticlesOnTimeAndLate(currentDate, writerIds[i]);
            dbController->generateWriterTimesheet(writerIds[i], submissionDate.first, submissionDate.second, currentDate);
        }
        Alert *alert = new Alert;
        alert->showInformationAlert("Generated!", "Writer Timesheet successfully generated");
        this->parentWindow->tabs->setCurrentIndex(4);
}

pair<int, int> articleWorkspace::calculateArticlesOnTimeAndLate(QDate issueDate, int writerId)
{
    pair<int, int> articlesOnTimeAndLate;
    int articlesOnTime = 0;
    int articlesLate = 0;
    QDate deadline = issueDate.addDays(-3);

    QString issueDateQString = issueDate.toString("yyyy-MM-dd");
    string issueDateString = issueDateQString.toStdString();
    Sender *sndr = new Sender;
    vector<int> articleIds = dbController->collectArticleIdForTimesheet(issueDate, writerId);
    cout<<"Writer with id: "<<writerId<<" has "<<articleIds.size()<<" articles for this issue"<<endl;
    for(int i = 0; i < articleIds.size(); i++){
        string sectionName = dbController->collectArticleSection(articleIds[i]);
        string articleName = dbController->collectArticleTitle(articleIds[i]);
        FileSystem::VerSeq versions;
        versions = sndr->getHistory(issueDateString, sectionName, articleName, fs::COPY);

        // Reads in first submitted file (assumed its submitted by writer)
        if(versions.size()>0){
            FileSystem::TimeIce submissionTime = versions[0].time;
            QDate submissionDate;
            submissionDate.setDate(submissionTime.year, submissionTime.month, submissionTime.day);

            if(submissionDate <= deadline){
                articlesOnTime++;
            } else {
                articlesLate++;
            }
        }
        articlesOnTimeAndLate = make_pair (articlesOnTime, articlesLate);
        return articlesOnTimeAndLate;
    }
}

void articleWorkspace::on_submitToArchiveButton_clicked()
{
    Alert *alert = new Alert;
    int ret = alert->showWarningAlert("Submit to archive", "Are you sure you want to continue? \n\n"
                                                           "All article workspaces will be removed and a writer "
                                                           "timesheet will be generated. \n\n"
                                                           "This action cannot be undone.");
    switch(ret){
    case QMessageBox::Apply:
    {
        generateTimesheet();
        submitToArchive();
        break;
    }
    case QMessageBox::Cancel:
        break;
    }
}
