#include "articleworkspace.h"
#include "ui_articleworkspace.h"
#include "newarticleworkspacewindow.h"
#include "article.h"

#include <QPushButton>
#include <QString>
#include <QHBoxLayout>
#include <iostream>

using namespace std;

articleWorkspace::articleWorkspace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::articleWorkspace)
{
    ui->setupUi(this);
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
}

void articleWorkspace::addArticleButton(Article *article)
{
    QString title = QString::fromStdString(article->getTitle());
    QPushButton *newArticleButton = new QPushButton(title, this);
    newArticleButton->setGeometry(QRect(QPoint(100, 100),
                                        QSize(200, 50)));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(newArticleButton);
    setLayout(mainLayout);

}
