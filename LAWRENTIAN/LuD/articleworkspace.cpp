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

ArticleWorkspaceNewsWidget* articleWorkspace::getNewsWidget()
{
    return newsWidget;
}

ArticleWorkspaceFeaturesWidget* articleWorkspace::getFeaturesWidget()
{
    return featuresWidget;
}

ArticleWorkspaceOpEdWidget* articleWorkspace::getOpEdWidget()
{
    return opEdWidget;
}

ArticleWorkspaceAAndEWidget* articleWorkspace::getAAndEWidget()
{
    return aAndEWidget;
}

ArticleWorkspaceSportsWidget* articleWorkspace::getSportsWidget()
{
    return sportsWidget;
}

ArticleWorkspaceVarietyWidget* articleWorkspace::getVarietyWidget()
{
    return varietyWidget;
}

bool articleWorkspace::getViewingArchive()
{
    return viewingArchive;
}

void articleWorkspace::init(MainWindow *parent, Client* c,LoginCredentials* crede)
{
    dbController = new ArticleWorkspaceDBC(c);
    cred = crede;
    parentWindow = parent;
    client = c;

    ui->issueDateComboBox->blockSignals(true);
    populateIssueComboBox();
    viewingArchive = false;


    QDate latestIssue = dbController->collectLatestIssueDate();
    if(!latestIssue.isNull()){
        QString latestIssueQString = latestIssue.toString("yyyy-MM-dd");
        ui->issueDateComboBox->setCurrentText(latestIssueQString);
        QString issueDateFormatString = latestIssue.toString("d MMM, yyyy");
        ui->issueTypeLabel->setText("Current Issue Articles: "+issueDateFormatString);
        viewingArchive = false;
    }



    handlePermissions();
    QWidget *mainWorkspaceWidget = new QWidget(this);
    tabs = new QTabWidget(mainWorkspaceWidget);
    tabs->setFixedSize(1100,500);

    newsWidget = new ArticleWorkspaceNewsWidget();
    tabs->addTab(newsWidget, "News");
    cout<<"About to init Widget"<<endl;
    newsWidget->init(this, client, cred);

    featuresWidget = new ArticleWorkspaceFeaturesWidget();
    tabs->addTab(featuresWidget, "Features");
    featuresWidget->init(this, client, cred);

    opEdWidget = new ArticleWorkspaceOpEdWidget();
    tabs->addTab(opEdWidget, "Opinions and Editorials");
    opEdWidget->init(this, client,cred);

    aAndEWidget = new ArticleWorkspaceAAndEWidget();
    tabs->addTab(aAndEWidget, "Arts and Entertainment");
    aAndEWidget->init(this, client, cred);

    sportsWidget = new ArticleWorkspaceSportsWidget();
    tabs->addTab(sportsWidget, "Sports");
    sportsWidget->init(this, client, cred);

    varietyWidget = new ArticleWorkspaceVarietyWidget();
    tabs->addTab(varietyWidget, "Variety");
    varietyWidget->init(this, client,cred);

    ui->issueDateComboBox->blockSignals(false);
}
void articleWorkspace::handlePermissions(){
    //Det whether to hide the add_workspace button.
    if(!cred->hasPermission(PermissionDef::ADMIN_PTOKEN)
            && !cred->hasPermission(PermissionDef::EDIT_ARTICLE_WORKSPACE))
        this->ui->addArticleWorkspace_pushButton->setEnabled(false);
}

void articleWorkspace::populateIssueComboBox()
{
    vector<QString> issueDateList = dbController->getIssueDateList();
    QList<QString> issueDateQList;
    for (int i=0; i<issueDateList.size(); i++)
    {
        issueDateQList.insert(i, issueDateList[i]);
    }
    ui->issueDateComboBox->addItems(issueDateQList);
}

QDate articleWorkspace::getSelectedIssueDate()
{
    QString selectedIssueString = ui->issueDateComboBox->currentText();
    QDate selectedIssue = QDate::fromString(selectedIssueString, "yyyy-MM-dd");
    return selectedIssue;
}

void articleWorkspace::openArticleWorkspace(Article* a){
    //Init data
    newArticleWorkspaceWindow *createArticleWorkspaceWindow = new newArticleWorkspaceWindow();
    createArticleWorkspaceWindow->init(cred, this);
    createArticleWorkspaceWindow->initDB(dbController->getClient());
    createArticleWorkspaceWindow->setupFields(a);

    //Init window
    createArticleWorkspaceWindow->setParentArticleWorkspaceWidget(this);
    createArticleWorkspaceWindow->setWindowModality(Qt::ApplicationModal);
    createArticleWorkspaceWindow->window()->show();
}

void articleWorkspace::on_addArticleWorkspace_pushButton_clicked()
{
    string dateString;
    QDate latestDate = dbController->collectLatestIssueDate();

    // Checks if an issue date has already been determined by editor-in-chief
    if(!latestDate.isNull()){
        QString dateFormat(df::dbFormat);
        dateString = latestDate.toString(dateFormat).toStdString();
    } else {
        //Set the article's date for the next Wednesday.
        QDate todate = QDate::currentDate();
        if(todate.dayOfWeek() == 3)
            todate = todate.addDays(7);
        while(todate.dayOfWeek() != 3 /*Wednesday*/)
            todate = todate.addDays(1);
        QString dateFormat(df::dbFormat);
        dateString = todate.toString(dateFormat).toStdString();
    }
    Article* newArticle = new Article(dateString,"","",
                                      0 /*Default to first section*/,
                                      -1 /*Nobody assigned*/,
                                      -1 /*Nobody assigned*/);
    newArticle->setId(dbController->getNextAvailableArticleID());
    openArticleWorkspace(newArticle);
}

/*
void articleWorkspace::initArticle(Article *article)
{
    articleVector.push_back(article);
} */

/*
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
}*/

/*
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
} */

/*
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
} */

/*
void articleWorkspace::addArticleButton(Article *article)
{
    QString title = article->QGetTitle();
    QString section = QString::fromStdString(dbController->translateSection(article->getSection()));
    QString buttonTitle = section+": "+title;
    QPushButton *newArticleButton = new QPushButton(buttonTitle, this);
    newArticleButton->setObjectName(title);

    newArticleButton->setGeometry(x, y, 500, 32);

    vert_layout->addWidget(newArticleButton);
    QWidget *layout_widget = new QWidget;
    layout_widget->setLayout(vert_layout);
    //ui->buttons_scrollArea->setWidget(layout_widget);

    connect(newArticleButton, SIGNAL(clicked()), this, SLOT(handleButton()));
    y = y+30;
} */

/*
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
} */

/*
void articleWorkspace::clearLayout(QVBoxLayout* vb_layout)
{
    while(!vb_layout->isEmpty())
    {
        QLayoutItem* item = vb_layout->itemAt(0);
        vb_layout->removeItem(item);
    }
    cout << "layout cleared." << endl;
} */

/*
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
} */

void articleWorkspace::submitToArchive()
{
    Sender sndr = Sender();
    //sndr.archiveIssue(issueDate)
}

void articleWorkspace::on_issueDateComboBox_currentIndexChanged(const QString &arg1)
{
    newsWidget->initTextBrowser();
    featuresWidget->initTextBrowser();
    aAndEWidget->initTextBrowser();
    opEdWidget->initTextBrowser();
    sportsWidget->initTextBrowser();
    varietyWidget->initTextBrowser();

    QDate latestIssue = dbController->collectLatestIssueDate();
    if(!latestIssue.isNull()){
        QString latestIssueQString = latestIssue.toString("yyyy-MM-dd");
        QDate selectedIssueDate = QDate::fromString(ui->issueDateComboBox->currentText(), "yyyy-MM-dd");
        QString selectedIssueDateFormat = QDate::fromString(ui->issueDateComboBox->currentText(), "yyyy-MM-dd").toString("d MMM yyyy");
        if(selectedIssueDate==latestIssue){
            QString formatLatestIssue = latestIssue.toString("d MMM yyyy");
            ui->issueTypeLabel->setText("Current Issue Articles: "+formatLatestIssue);
            viewingArchive = false;
        }
        if(selectedIssueDate>latestIssue){
            ui->issueTypeLabel->setText("<font color='green'>Upcoming Issue Articles: "+selectedIssueDateFormat+"</font>");
            viewingArchive = false;
        }
        if(selectedIssueDate<latestIssue){
            ui->issueTypeLabel->setText("<font color='red'>Archived Issue Articles: "+selectedIssueDateFormat+"</font>");
            viewingArchive = true;
        }
    }

}

void articleWorkspace::on_currentIssueButton_clicked()
{
    QDate latestIssue = dbController->collectLatestIssueDate();
    QString latestIssueString = latestIssue.toString("yyyy-MM-dd");
        if(!latestIssue.isNull()){
            ui->issueDateComboBox->setCurrentText(latestIssueString);
        } else {
        Alert *alert = new Alert;
        alert->showInformationAlert("No Set Issue Date", "No current issue date set.\nSetting to latest available issue");
        ui->issueDateComboBox->setCurrentIndex(0);
        }
}
