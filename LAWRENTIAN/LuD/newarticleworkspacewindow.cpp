#include "newarticleworkspacewindow.h"
#include "ui_newarticleworkspacewindow.h"

#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QDate>
#include <string>
#include "Sender.h"

using namespace std;

newArticleWorkspaceWindow::newArticleWorkspaceWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newArticleWorkspaceWindow)
{
    ui->setupUi(this);
    QStringList list;
    list <<"Associate News"<<"Features"<<"Opinions & Editorials"<<"Arts & Entertainment"
                        <<"Sports"<<"Variety";
    list.sort();
    ui->sectionComboBox->addItems(list);
}

newArticleWorkspaceWindow::~newArticleWorkspaceWindow()
{
    delete ui;
}

void newArticleWorkspaceWindow::on_pushButton_clicked()
{
    QString articlePath = QFileDialog::getOpenFileName(this, tr("Select"), "/home", tr("Text Files (*.txt *.rtf *.docx)"));
    ui->articleFileTextField->setText(articlePath);
}

void newArticleWorkspaceWindow::on_pushButton_2_clicked()
{
    Sender sndr = Sender();

    string title = ui->articleTitleTextField->text().toStdString();
    string description = ui->descriptionTextField->toPlainText().toStdString();
    string section = ui->sectionComboBox->currentText().toStdString();
    string writer = ui->writerComboBox->currentText().toStdString();
    string photographer = ui->photographerComboBox->currentText().toStdString();
    string filePath = ui->articleFileTextField->text().toStdString();
    if(filePath.size())
        sndr.sendFile(filePath,"LuD.docx");

    QDate issueDate = ui->issueDateEdit->date();
    string issueDateString = issueDate.toString().toStdString();
    newArticle = new Article(issueDateString, title, description, section, writer, photographer, filePath);

    // Check if article already exists in articleWorkspace (widget)
    if(!parentArticleWorkspaceWidget->workspaceExists(title)){
    parentArticleWorkspaceWidget->initArticle(newArticle);
    parentArticleWorkspaceWidget->addArticleButton(newArticle);
    }
    this->close();
}
articleWorkspace *newArticleWorkspaceWindow::getParentArticleWorkspaceWidget() const
{
    return parentArticleWorkspaceWidget;
}

void newArticleWorkspaceWindow::setParentArticleWorkspaceWidget(articleWorkspace *value)
{
    parentArticleWorkspaceWidget = value;
}

void newArticleWorkspaceWindow::setupFields(Article *article)
{
    QString title = QString::fromStdString(article->getTitle());
    QString description = QString::fromStdString(article->getDescription());
    QString section = QString::fromStdString(article->getSection());
    QString writer = QString::fromStdString(article->getWriter());
    QString photographer = QString::fromStdString(article->getPhotographer());
    QString filePath = QString::fromStdString(article->getFilePath());
    QString issueDateString = QString::fromStdString(article->getIssueDate());
    QDate issueDate = QDate::fromString(issueDateString);

    ui->articleTitleTextField->setText(title);
    ui->descriptionTextField->setText(description);
    ui->sectionComboBox->setCurrentText(section);
    ui->writerComboBox->setCurrentText(writer);
    ui->photographerComboBox->setCurrentText(photographer);
    ui->articleFileTextField->setText(filePath);
    ui->issueDateEdit->setDate(issueDate);
}

