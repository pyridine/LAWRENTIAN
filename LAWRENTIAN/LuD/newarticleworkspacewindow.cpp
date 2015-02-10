#include "newarticleworkspacewindow.h"
#include "ui_newarticleworkspacewindow.h"

#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <string>

using namespace std;

newArticleWorkspaceWindow::newArticleWorkspaceWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newArticleWorkspaceWindow)
{
    ui->setupUi(this);
    QStringList list;
    list <<"News"<<"Associate News"<<"Features"<<"Opinions & Editorials"<<"Arts & Entertainment"
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
    string title = ui->articleTitleTextField->text().toStdString();
    string description = ui->descriptionTextField->toPlainText().toStdString();
    string section = ui->sectionComboBox->currentText().toStdString();
    string writer = ui->writerComboBox->currentText().toStdString();
    string photographer = ui->photographerComboBox->currentText().toStdString();
    string filePath = ui->articleFileTextField->text().toStdString();
    string issueDate = ui->issueDateEdit->text().toStdString();
    newArticle = new Article(issueDate, title, description, section, writer, photographer, filePath);
    parentArticleWorkspaceWidget->initArticle(newArticle);
    parentArticleWorkspaceWidget->addArticleButton(newArticle);
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

