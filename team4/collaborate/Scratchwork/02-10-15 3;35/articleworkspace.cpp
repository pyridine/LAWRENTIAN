#include "articleworkspace.h"
#include "ui_articleworkspace.h"
#include "newarticleworkspacewindow.h"
#include "article.h"

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

void articleWorkspace::on_pushButton_clicked()
{
    newArticleWorkspaceWindow *createArticleWorkspaceWindow = new newArticleWorkspaceWindow();
    createArticleWorkspaceWindow->setParentArticleWorkspaceWidget(this);
    createArticleWorkspaceWindow->window()->show();
}

void articleWorkspace::initArticle(Article *article)
{
    articleVector.push_back(article);
}

void articleWorkspace::addArticleButton(Article *article)
{
    QString title = QString::fromStdString(article->getTitle());
    QString section = QString::fromStdString(article->getSection());
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
