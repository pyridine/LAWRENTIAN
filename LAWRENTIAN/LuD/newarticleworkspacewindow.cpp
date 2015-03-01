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
#include "alert.h"

using namespace std;

/*Used to display section names.*/

newArticleWorkspaceWindow::newArticleWorkspaceWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newArticleWorkspaceWindow)
{
    //Set up static strings.
    NEWZ = "News";
    FEATZ = "Features";
    OPEDZ = "Opinions & Editorials";
    ARTSENTZ = "Arts & Entertainment";
    VARIEZ = "Sports";
    SPORTZ = "Variety";

    ui->setupUi(this);

    //TODO: permissions.......
    ui->delete_pushButton->setVisible(false);

    ui->issueDateEdit->setDisplayFormat("dd MMM, yyyy");
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
    //Populate the new article object....
    // </begin date> Maybe put this in an inherited dbcontroller function?
    stringstream s;
    int year = ui->issueDateEdit->date().year();
    stringstream monthstream;
    int month = ui->issueDateEdit->date().month();
    if(month >= 10){
        monthstream << month;
    } else{
        monthstream << "0" << month;
    }
    stringstream daystream;
    int day = ui->issueDateEdit->date().day();
    if(day >= 10){
        daystream << day;
    } else{
        daystream << "0" << day;
    }
    s << year << monthstream.str() << daystream.str();
    string issueDateString = s.str();
    cout << "issueDateString" << issueDateString << endl;
    // </end date>

    string pastTitle = myArticle->getTitle();
    string title = ui->articleTitleTextField->text().toStdString();
    string description = ui->descriptionTextField->toPlainText().toStdString();
    string date = ui->issueDateEdit->text().toStdString();
    int section = this->getSelectedSectionID();
    int writer = this->getSelectedWriterLuid();
    int photographer = this->getSelectedPhotographerLuid();
    int id = myArticle->getId();
    if(!dbController->isArticleTitleAlreadyInUse(title,id))
    {
        if(0 != title.compare("Krebsbach is the best CS teacher in the world"))
        {
            //Do sender things...
            Sender sndr = Sender();
            string sec_this =  dbController->translateSection(section);
            string sec_art = dbController->translateSection(myArticle->getSection());
            if(section != myArticle->getSection() && sec_art.size())
                sndr.moveArtToSection(date, sec_art, sec_this, title);

            string filePath = ui->articleFileTextField->text().toStdString();
            if(filePath.size())
                sndr.sendFile(date, sec_this, title, fs::COPY, filePath);

            QStringList::const_iterator iter = img_paths.begin();
            for(iter; iter!=img_paths.end(); iter++)
                sndr.sendFile(date,sec_this,title,fs::IMAGE,iter->toStdString());

            if(pastTitle.compare(title))
                sndr.renameArticle(date, sec_this, pastTitle, title);
            //done.

            cout << "adding art." << endl;
            myArticle = new Article(issueDateString, title, description, section, writer, photographer);

            myArticle->setId(id);
            //done.

            cout << "Updating the parent window." << endl;
            //Update the article workspace widget...
            if(!parentArticleWorkspaceWidget->workspaceExists(title))
            {
                parentArticleWorkspaceWidget->initArticle(myArticle);
                parentArticleWorkspaceWidget->addArticleButton(myArticle);
                dbController->addArticle(myArticle);
                parentArticleWorkspaceWidget->resetArticleButtons();
            }
            //Done.

            cout << "Adding the article to the DB." << endl;
            //Add the new article to the DB...
            dbController->addArticle(myArticle);
            //Done!

            //We're done.
            closeMe();
            return;
            //Bye bye :()
        }
        else
            Alert::showAlert("Error","Article title is a commonly known fact, and is therefore not newsworthy.");

    }
    else
        Alert::showAlert("Error","Article title is already in use.");

}

void newArticleWorkspaceWindow::closeMe(){
    this->parentArticleWorkspaceWidget->updateArticleList();
    this->close();
}


articleWorkspace* newArticleWorkspaceWindow::getParentArticleWorkspaceWidget() const
{
    return parentArticleWorkspaceWidget;
}

void newArticleWorkspaceWindow::setParentArticleWorkspaceWidget(articleWorkspace *value)
{
    parentArticleWorkspaceWidget = value;
}

void newArticleWorkspaceWindow::setupFields(Article *article)
{
    myArticle = article;
    ui->articleTitleTextField->setText(article->QGetTitle());
    ui->descriptionTextField->setText(QString::fromStdString(article->getDescription()));

    QString issueDateString = QString::fromStdString(article->getIssueDate());
    QString dateFormat("yyyy-MM-dd");
    QDate issueDate = QDate::fromString(issueDateString,dateFormat);
    ui->issueDateEdit->setDate(issueDate);
    setupSectionComboBox(article->getSection());
    this->updatePhotographerList(article->getPhotographer());
    this->updateWriterList(article->getSection(),article->getWriter());
    this->on_sectionComboBox_currentIndexChanged(QString("a")); //argument does nothing
}

void newArticleWorkspaceWindow::setupSectionComboBox(int section)
{
    //Put them all in a list, and then bubble (cf. bubblesort) the one
    //that is supposed to be first.

    vector<pair<string,int>>* sections = new vector<pair<string,int>>();
    sections->push_back(std::make_pair(NEWZ,SectionDef::NEWS_SECTION));
    sections->push_back(std::make_pair(FEATZ,SectionDef::FEATURES_SECTION));
    sections->push_back(std::make_pair(OPEDZ,SectionDef::OPED_SECTION));
    sections->push_back(std::make_pair(ARTSENTZ,SectionDef::ARTSENT_SECTION));
    sections->push_back(std::make_pair(VARIEZ,SectionDef::VARIETY_SECTION));
    sections->push_back(std::make_pair(SPORTZ,SectionDef::SPORTS_SECTION));

    vector<pair<string,int>>::iterator secPairs = sections->begin();
    if(section > 0){
        //Now find the index of the assigned section...
        while((*secPairs).second != section){
            secPairs++;
        }

        //...And bubble it up to the top.
        while(secPairs != (sections->begin())){
            std::iter_swap(secPairs,secPairs-1);
            --secPairs;
        }
        secPairs= sections->begin();
    }
    while(secPairs != sections->end()){
        ui->sectionComboBox->addItem(QString::fromStdString((*secPairs).first),QVariant((*secPairs).second));
        secPairs++;
    }
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
    cout << "del" << endl;
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

    bool isVisible = !img_paths.isEmpty();
    ui->delete_pushButton->setVisible(isVisible);
}

void newArticleWorkspaceWindow::initDB(Client* c){
    dbController = new NewArticleWorkspaceWindowDBC(c);
}


int newArticleWorkspaceWindow::getSelectedSectionID(){
    return ui->sectionComboBox->itemData(ui->sectionComboBox->currentIndex()).toInt();
}

int newArticleWorkspaceWindow::getSelectedSectionPermissionToken(){
    //Note: unfortunately, you can't do switch statements with non-constant values (the SectionDefs),
    //So I had to to this ugly if sequence.

    int section = getSelectedSectionID();

    if (section == SectionDef::NEWS_SECTION)
        return PermissionDef::SEC_NEWS;
    if (section ==  SectionDef::ARTSENT_SECTION)
        return PermissionDef::SEC_ARTS;
    if (section ==  SectionDef::FEATURES_SECTION)
        return PermissionDef::SEC_FEATURES;
    if (section ==  SectionDef::OPED_SECTION)
        return PermissionDef::SEC_OPED;
    if (section ==  SectionDef::SPORTS_SECTION)
        return PermissionDef::SEC_SPORTS;
    if (section ==  SectionDef::VARIETY_SECTION)
        return PermissionDef::SEC_VARIETY;
    return -1;
}



void newArticleWorkspaceWindow::on_copyHistory_pushButton_clicked()
{
    int section = this->getSelectedSectionID();

    string date = ui->issueDateEdit->text().toStdString();
    string sec = dbController->translateSection(section);
    string art = ui->articleTitleTextField->text().toStdString();

    cout << sec << endl;
    cout << art << endl;

    CopyHistoryWindow *chw = new CopyHistoryWindow(0,date,sec,art);
    chw->activateWindow();
    chw->setWindowModality(Qt::ApplicationModal);
    chw->show();
}

void newArticleWorkspaceWindow::updateWriterList(int section, int currentWriter){

    vector<pair<string, int> *>* newWriterList = dbController->getListOfWritersForSection(section,currentWriter);

    //rewrite the combobox.
    ui->writerComboBox->clear();
    vector<pair<string, int> *>::iterator it =  newWriterList->begin();
    while(it != newWriterList->end()){
        pair<string,int>* next = *it;
        //Adds both the displayed name (first) and the associated LUID (second)
        ui->writerComboBox->addItem(QString::fromStdString(next->first),QVariant(next->second));
        ++it;
    }
    ui->writerComboBox->setCurrentIndex(0);
}

void newArticleWorkspaceWindow::updatePhotographerList(int currentPhotographer){

    vector<pair<string, int> *>* newPhotographerList = dbController->getListOfPhotographers(currentPhotographer);

    ui->photographerComboBox->clear();
    vector<pair<string, int> *>::iterator it =  newPhotographerList->begin();
    while(it != newPhotographerList->end()){
        pair<string,int>* next = *it;
        //Adds both the displayed name (first) and the associated LUID (second)
        ui->photographerComboBox->addItem(QString::fromStdString(next->first),QVariant(next->second));
        ++it;
    }

    ui->photographerComboBox->setCurrentIndex(0);
}
int newArticleWorkspaceWindow::getSelectedWriterLuid(){
    return ui->writerComboBox->itemData(ui->writerComboBox->currentIndex()).toInt();
}
int newArticleWorkspaceWindow::getSelectedPhotographerLuid(){
    return ui->photographerComboBox->itemData(ui->photographerComboBox->currentIndex()).toInt();
}

void newArticleWorkspaceWindow::on_sectionComboBox_currentIndexChanged(const QString &arg1)
{
    //This will in fact work if there is already a writer assigned.
    //The update checks to see if the assigned writer has permissions for the
    //newly selected section.
    this->updateWriterList(this->getSelectedSectionPermissionToken(),
                           myArticle->getWriter());
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

std::string newArticleWorkspaceWindow::getExt(const string &s)
{
    using namespace std;

    string::const_iterator iter = s.end() - 1;
    while(*iter != '.')
    {
        if(iter == s.begin())
            return "";
        iter--;
    }
    return s.substr(iter - s.begin(), s.end() - s.begin());
}

std::string newArticleWorkspaceWindow::getNameColon(const std::string& s)
{
    string str = s;
    cout << str << endl;
    string::const_iterator iter = str.begin();
    for (iter; iter != str.end(); iter++)
    {
        if(*iter == ':')
        {
            iter++;
            break;
        }
    }
    string ret= str.substr(iter - str.begin(),str.length());
    cout << ret << "!!!!!!" << endl;
    return ret;
}

void newArticleWorkspaceWindow::on_deleteAWS_pushButton_clicked()
{

    Sender sndr = Sender();

    QString date = myArticle->QGetIssueDate();
    string issueDate = QDate::fromString(date,"yyyy-MM-dd").toString("dd MMM, yyyy").toStdString();
    string sec = dbController->translateSection(myArticle->getSection());
    string art = myArticle->getTitle();

    sndr.deleteArt(issueDate,sec,art);
    dbController->deleteArticle(myArticle->getId());

    cout << issueDate << endl << sec << endl << art << endl;
    closeMe();
}

