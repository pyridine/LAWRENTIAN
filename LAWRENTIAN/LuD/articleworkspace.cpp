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
Article *articleWorkspace::getNewArticle() const
{
    return newArticle;
}

void articleWorkspace::setNewArticle(Article *value)
{
    newArticle = value;
}


void articleWorkspace::initArticle(Article *article)
{
    articleWorkspace::setNewArticle(article);
    cout<<getNewArticle()->getIssueDate()<<endl;
    cout<<getNewArticle()->getTitle()<<endl;
    cout<<getNewArticle()->getDescription()<<endl;
    cout<<getNewArticle()->getSection()<<endl;
    cout<<getNewArticle()->getWriter()<<endl;
    cout<<getNewArticle()->getPhotographer()<<endl;
    cout<<getNewArticle()->getFilePath()<<endl;
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
    int i = 0;
    for (i; i < articleVector.size(); i++);{
        Article* send = articleVector[i];
        QString sendTitle = QString::fromStdString(send->getTitle());
        if(sendTitle == senderObjName){
            newArticleWorkspaceWindow *editArticleWorkspaceWindow = new newArticleWorkspaceWindow();
            editArticleWorkspaceWindow->setParentArticleWorkspaceWidget(this);
            editArticleWorkspaceWindow->setupFields(send);
            editArticleWorkspaceWindow->window()->show();
        }
    }
}
