#include "newarticleworkspacewindow.h"
#include "ui_newarticleworkspacewindow.h"

#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QDate>
#include <string>
#include "Sender.h"
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

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
    ui->delete_pushButton->setVisible(false);

}

newArticleWorkspaceWindow::~newArticleWorkspaceWindow()
{
    delete ui;
}

void newArticleWorkspaceWindow::on_chooseFile_pushButton_clicked()
{
    QString articlePath = QFileDialog::getOpenFileName(this, tr("Select"), "/home", tr("Text Files (*.txt *.rtf *.docx)"));
    ui->articleFileTextField->setText(articlePath);
}

void newArticleWorkspaceWindow::on_submit_pushButton_clicked()
{
    Sender sndr = Sender();

    string title = ui->articleTitleTextField->text().toStdString();
    string description = ui->descriptionTextField->toPlainText().toStdString();
    string section = ui->sectionComboBox->currentText().toStdString();
    string writer = ui->writerComboBox->currentText().toStdString();
    string photographer = ui->photographerComboBox->currentText().toStdString();
    string filePath = ui->articleFileTextField->text().toStdString();
    if(filePath.size())
        sndr.sendFile(section, title, "Copy", "new.dox", filePath);

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


void newArticleWorkspaceWindow::on_addImage_pushButton_clicked()
{
    using namespace std;

    img_paths = QFileDialog::getOpenFileNames(this, "Select", "/home", "Images (*.png *.jpg)");

    if(img_paths.isEmpty())
        return;
    ui->delete_pushButton->setVisible(true);

    QStringList::const_iterator iter = img_paths.begin();
    vert_layout = new QVBoxLayout;
    while (iter != img_paths.end())
    {
        QLabel *text = new QLabel;
        text->setText(getfName(*iter));

        QCheckBox *check_box = new QCheckBox;
        cb_vec.push_back(check_box);

        QHBoxLayout *horz_layout = new QHBoxLayout;
        horz_layout->addWidget(check_box);
        horz_layout->addWidget(text);

        QWidget *temp_widget = new QWidget;
        temp_widget->setLayout(horz_layout);
        vert_layout->addWidget(temp_widget);

        iter++;
    }

    QWidget *widget = new QWidget;
    widget->setLayout(vert_layout);

    ui->img_scrollArea->setWidget(widget);
}

QString newArticleWorkspaceWindow::getfName(QString s)
{
    using namespace std;

    string str = s.toStdString();
    string::const_iterator iter = str.end() - 1;

    while(*iter != '/' && *iter != '\\')
    {
        iter--;
        if(iter == str.begin())
        {
            break; //throw exception.
        }
    }
    string ret = str.substr(iter - str.begin() + 1,str.end() - iter - 1);
    return QString::fromStdString(ret);
}

void newArticleWorkspaceWindow::on_delete_pushButton_pressed()
{

    QVector<QCheckBox*>::iterator iter = cb_vec.begin();
    for(iter; iter != cb_vec.end(); iter++)
    {
        QCheckBox *c_box = *iter;
        if(c_box->isChecked())
        {
            cout << iter - cb_vec.begin() << " " << cb_vec.length() << endl;
            vert_layout->removeItem(vert_layout->itemAt(iter - cb_vec.begin()));
            img_paths.removeAt(iter - cb_vec.begin());
            cb_vec.erase(iter,iter+1);

            iter--;
        }
        if (iter == cb_vec.end())
            break;
    }

    QWidget *widget = new QWidget;
    widget->setLayout(vert_layout);
    ui->img_scrollArea->setWidget(widget);

    bool isVisible = img_paths.isEmpty() ? false : true;
    ui->delete_pushButton->setVisible(isVisible);
}
