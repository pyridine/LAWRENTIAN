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
#include "copyhistorywindow.h"
#include "sectiondef.h"
#include "permissiondef.h"

using namespace std;

newArticleWorkspaceWindow::newArticleWorkspaceWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newArticleWorkspaceWindow)
{
    COPY = "Copy";
    IMAGE = "Image";

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

    int section = 0;
    switch(ui->sectionComboBox->currentIndex()){
        case 0:
        section = SectionDef::NEWS_SECTION;
        break;
    case 1:
        section = SectionDef::FEATURES_SECTION;
        break;
    case 2:
        section = SectionDef::OPED_SECTION;
        break;
    case 3:
        section = SectionDef::ARTSENT_SECTION;
        break;
    case 4:
        section = SectionDef::SPORTS_SECTION;
        break;
    case 5:
        section = SectionDef::VARIETY_SECTION;
        break;
    }


    int writer = (*((*currentWriterList)[ui->writerComboBox->currentIndex()])).second;
    int photographer = (*((*currentPhotographerList)[ui->photographerComboBox->currentIndex()])).second;
    string filePath = ui->articleFileTextField->text().toStdString();

    if(filePath.size())
        sndr.sendFile(section, title, COPY, getNameExt(filePath), filePath);

    QDate issueDate = ui->issueDateEdit->date();

    string issueDateString = issueDate.toString().toStdString();
    newArticle = new Article(issueDateString, title, description, section, writer, photographer);

    // Check if article already exists in articleWorkspace (widget)
    if(!parentArticleWorkspaceWidget->workspaceExists(title)){
    parentArticleWorkspaceWidget->initArticle(newArticle);
    parentArticleWorkspaceWidget->addArticleButton(newArticle);

    QStringList::const_iterator iter = img_paths.begin();

    for(iter; iter!=img_paths.end(); iter++)
        sndr.sendFile(section,title,IMAGE,getNameExt(iter->toStdString()),
                      iter->toStdString());
					  
    dbController->addArticle(newArticle);

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
    QStringList* list = new QStringList();
    list->append(QString("News"));
    list->append(QString("Features"));
    list->append(QString("Opinions & Editorials"));
    list->append(QString("Arts & Entertainment"));
    list->append(QString("Sports"));
    list->append(QString("Variety"));
    ui->sectionComboBox->addItems(*list);


    this->updatePhotographerList();

    int fuckingKludge = 0;
    while(fuckingKludge < 10 && (0 != QString::compare(ui->sectionComboBox->currentText(),QString::fromStdString(article->getTitle()),Qt::CaseInsensitive))){
          ui->sectionComboBox->setCurrentIndex(fuckingKludge);
          ++fuckingKludge;
    }

    QString title = QString::fromStdString(article->getTitle());
    QString description = QString::fromStdString(article->getDescription());
    QString section = QString::fromStdString(dbController->translateSection(article->getSection()));
    int writer = article->getWriter();
    int photographer = (article->getPhotographer());
    QString issueDateString = QString::fromStdString(article->getIssueDate());
    QDate issueDate = QDate::fromString(issueDateString);

    ui->articleTitleTextField->setText(title);
    ui->descriptionTextField->setText(description);
    ui->sectionComboBox->setCurrentText(section);
    ui->writerComboBox->setCurrentText(QString::number(writer));
    ui->photographerComboBox->setCurrentText(QString::number(photographer));
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

    cb_vec_t::iterator iter = cb_vec.begin();
    for(iter; iter != cb_vec.end(); iter++)
    {
        QCheckBox *c_box = *iter;
        if(c_box->isChecked())
        {
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

void newArticleWorkspaceWindow::initDB(Client* c){
    dbController = new NewArticleWorkspaceWindowDBC(c);

    //It has to be done now because we need the dbController for it :P

}

void newArticleWorkspaceWindow::on_copyHistory_pushButton_clicked()
{
    CopyHistoryWindow *chw = new CopyHistoryWindow(0,"News","Not Really","Copy","Yo");
    chw->show();
}

void newArticleWorkspaceWindow::updateWriterList(int section){

    currentWriterList = dbController->getListOfWritersForSection(section);

    //clear the combobox.
    for(int i = 0; i < ui->writerComboBox->count(); i++){
        ui->writerComboBox->removeItem(i);
    }

    //rewrite the combobox.
    vector<pair<string, int> *>::iterator it =  currentWriterList->begin();

    while(it != currentWriterList->end()){
        pair<string,int>* next = *it;
        ui->writerComboBox->addItem(QString::fromStdString(next->first));
        ++it;
    }
}

void newArticleWorkspaceWindow::updatePhotographerList(){

    currentPhotographerList = dbController->getListOfPhotographers();

    //clear the combobox.
    for(int i = 0; i < ui->photographerComboBox->count(); i++){
        ui->photographerComboBox->removeItem(i);
    }

    //rewrite the combobox.
    vector<pair<string, int> *>::iterator it =  currentPhotographerList->begin();

    while(it != currentPhotographerList->end()){
        pair<string,int>* next = *it;
        ui->photographerComboBox->addItem(QString::fromStdString(next->first));
        ++it;
    }
}
int newArticleWorkspaceWindow::getSelectedWriterLuid(){
    //writerComboBox
      //      currentWriterList
    return 0;
}

void newArticleWorkspaceWindow::on_sectionComboBox_currentIndexChanged(const QString &arg1)
{
    cout << "UH OH!!" << endl;
    cout << arg1.toStdString() << endl;
    cout << "comp1" << endl;
    cout<< "dbc is " << dbController << endl;

    if(0 == QString::compare(QString("News"),arg1,Qt::CaseInsensitive)){
        cout << "yesnews" << PermissionDef::SEC_NEWS << endl;
        this->updateWriterList(30);
    }
    if(0 == QString::compare(QString("Features"),arg1,Qt::CaseInsensitive)){
        this->updateWriterList(PermissionDef::SEC_FEATURES);
    }
    if(0 == QString::compare(QString("Opinions & Editorials"),arg1,Qt::CaseInsensitive)){
        this->updateWriterList(PermissionDef::SEC_OPED);
    }
    if(0 == QString::compare(QString("Arts & Entertainment"),arg1,Qt::CaseInsensitive)){
        this->updateWriterList(PermissionDef::SEC_ARTS);
    }
    if(0 == QString::compare(QString("Sports"),arg1),Qt::CaseInsensitive){
        this->updateWriterList(PermissionDef::SEC_SPORTS);
    }
    if(0 == QString::compare(QString("Variety"),arg1,Qt::CaseInsensitive)){
        this->updateWriterList(PermissionDef::SEC_VARIETY);
    }

}

std::string newArticleWorkspaceWindow::getNameExt(const std::string& s)
{
    using namespace std;
    string str = s;
    string::const_iterator iter = str.end() - 1;
    while(*iter != '/' && *iter != '\\')
    {
        iter--;
        if(iter == str.begin())
        {
            break; //throw exception.
            cout << "broken" << endl;
        }
    }
    return str.substr(iter - str.begin() + 1,str.end() - iter - 1);
}
