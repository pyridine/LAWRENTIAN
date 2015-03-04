#include "newarticleworkspacewindow.h"
#include "ui_newarticleworkspacewindow.h"

#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QDate>
#include "titledef.h"
#include <string>
#include "Sender.h"
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "copyhistorywindow.h"
#include "sectiondef.h"
#include "permissiondef.h"
#include "alert.h"
#include <algorithm>

using namespace std;

/*Used to display section names.*/

newArticleWorkspaceWindow::newArticleWorkspaceWindow(QWidget *parent,LoginCredentials* login) :
    QDialog(parent),
    ui(new Ui::newArticleWorkspaceWindow)
{
    //Set up static strings.
    NEWZ = "News";
    FEATZ = "Features";
    OPEDZ = "Opinions & Editorials";
    ARTSENTZ = "Arts & Entertainment";
    VARIEZ = "Variety";
    SPORTZ = "Sports";

    ui->setupUi(this);

    ui->delete_pushButton->setVisible(false);

    ui->issueDateEdit->setDisplayFormat(df::srvrFormat);

    loginCred = login;

    //Permissions
    handlePermissions();
}



void newArticleWorkspaceWindow::handlePermissions(){
    if(!loginCred->hasPermission(PermissionDef::ADMIN_PTOKEN)
            &&!loginCred->hasPermission(PermissionDef::EDIT_ARTICLE_WORKSPACE)){
        ui->sectionComboBox->setEnabled(false);
        ui->writerComboBox->setEnabled(false);
        ui->photographerComboBox->setEnabled(false);
        ui->deleteAWS_pushButton->setEnabled(false);
        ui->issueDateEdit->setEnabled(false);
        ui->articleTitleTextField->setEnabled(false);
        ui->descriptionTextField->setEnabled(false);
    }

    if(!loginCred->hasPermission(PermissionDef::ADMIN_PTOKEN)
            &&!loginCred->hasPermission(PermissionDef::SUBMIT_COPY)
            &&!loginCred->hasPermission(PermissionDef::EDIT_COPY)){


        ui->chooseFile_pushButton->setEnabled(false);
        ui->copyHistory_pushButton->setEnabled(false);
    }

    //Second pass thru writer permissions occurs in setupfields,
    //when we know who the writer is.

    if(!loginCred->hasPermission(PermissionDef::ADMIN_PTOKEN)
            &&!loginCred->hasPermission(PermissionDef::SUBMIT_GRAPHIC)
            &&!loginCred->hasPermission(PermissionDef::EDIT_GRAPHIC)
            &&!loginCred->hasPermission(PermissionDef::SUBMIT_PHOTO)
            &&!loginCred->hasPermission(PermissionDef::EDIT_PHOTO)){
        ui->addImage_pushButton->setEnabled(false);
    }
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
    // Initializing fields....
    string title = ui->articleTitleTextField->text().toStdString();
    string description = ui->descriptionTextField->toPlainText().toStdString();
    string date = ui->issueDateEdit->text().toStdString();
    int iSection = this->getSelectedSectionID();
    int iWriter = this->getSelectedWriterLuid();
    int iPhotographer = this->getSelectedPhotographerLuid();
    int id = myArticle->getId();
    // done

    if(!dbController->isArticleTitleAlreadyInUse(title,id))
    {
        if(title.compare("Krebsbach is the best CS teacher in the world"))
        {
            cout << "Updating server." << endl;
            // Update Server.
            Sender sndr = Sender();
            string sec_this =  dbController->translateSection(iSection);
            string sec_art = dbController->translateSection(myArticle->getSection());

            string date_art = QDate::fromString(myArticle->QGetIssueDate(),df::dbFormat).toString(df::srvrFormat).toStdString();

            if(date.compare(date_art) && date_art.size())
                sndr.changeArtIssueDate(date_art,date,sec_art,myArticle->getTitle());

            if(iSection != myArticle->getSection() && sec_art.size())
                sndr.changeArtSection(date, sec_art, sec_this, myArticle->getTitle());

            if(title.compare(myArticle->getTitle()))
                sndr.renameArticle(date, sec_this, myArticle->getTitle(), title);

            string filePath = ui->articleFileTextField->text().toStdString();
            if(filePath.size())
                sndr.sendCopy(date, sec_this, title, filePath);

            QStringList::const_iterator iter = img_paths.begin();
            for(iter; iter!=img_paths.end(); iter++)
                sndr.sendImage(date,sec_this,title,getfName(*iter),iter->toStdString());
            // done.

            cout << "adding art." << endl;
            // add article.
            string issueDateForArt = QDate::fromString(ui->issueDateEdit->text(),df::srvrFormat).toString(df::dbFormat).toStdString();
            myArticle = new Article(issueDateForArt, title, description, iSection, iWriter, iPhotographer);
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
            updatePhotoDB(); //Must be done after adding article b/c foreign key constraints.
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
    QString dateFormat(df::dbFormat);
    QDate issueDate = QDate::fromString(issueDateString,dateFormat);
    ui->issueDateEdit->setDate(issueDate);
    setupSectionComboBox(article->getSection());
    this->updatePhotographerList(article->getPhotographer());
    this->updateWriterList(article->getSection(),article->getWriter());
    this->on_sectionComboBox_currentIndexChanged(QString("argument does nothing"));


    if(loginCred->getTitle()==TitleDef::WRITER){
        if(loginCred->getLUID() == getSelectedWriterLuid()){
            this->ui->chooseFile_pushButton->setEnabled(true);
        } else{
            this->ui->chooseFile_pushButton->setEnabled(false);
        }
    }
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
        cout << getfName(*iter) << endl;

        QLabel *text = new QLabel;
        text->setText(QString::fromStdString(getfName(*iter)));

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

string newArticleWorkspaceWindow::getfName(QString s)
{
    using namespace std;

    string str = s.toStdString();
    size_t loc_slash = str.rfind('/');
    loc_slash = loc_slash == string::npos ? str.rfind('\\') : loc_slash;
    if(loc_slash == string::npos)
        return "";

    str = str.substr(loc_slash + 1,str.size() - 1);
    size_t loc_dot = str.rfind('.');
    if(loc_dot == string::npos)
        return "";

    return str.substr(0,loc_dot);

}

void newArticleWorkspaceWindow::on_delete_pushButton_pressed()
{
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
    string date = QDate::fromString(myArticle->QGetIssueDate(),df::dbFormat).toString(df::srvrFormat).toStdString();
    string sec = dbController->translateSection(myArticle->getSection());
    string art = myArticle->getTitle();

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

    //This is so the compiler will shut up about how &arg1 is never referenced
    //start
    QString bif = arg1;
    bif.append('c');
    //end

    //This will in fact work if there is already a writer assigned.
    //The update checks to see if the assigned writer has permissions for the
    //newly selected section.
    this->updateWriterList(this->getSelectedSectionPermissionToken(),
                           myArticle->getWriter());
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

    string issueDate = QDate::fromString(myArticle->QGetIssueDate(),df::dbFormat).toString(df::srvrFormat).toStdString();
    string sec = dbController->translateSection(myArticle->getSection());
    string art = myArticle->getTitle();

    sndr.deleteArt(issueDate,sec,art);
    dbController->deleteArticle(myArticle->getId());
    dbController->deleteMyPhotos(myArticle->getId());
    closeMe();
}

void newArticleWorkspaceWindow::updatePhotoDB(){
    //Yes, I know, I am once again writing a DB update algorithm that
    //just wipes the database and reinputs the correct data.
    //How horrible.
    //However, in this case, I think such an algorithm is best.
    //since so many things can change about articles, it's useless
    //to keep track of them all and only update the affected rows in the photo DB.
    //So, a wipe/redo algorithm is fine.

    QStringList fname_paths;
    for(int i = 0; i < img_paths.size(); i++){
        fname_paths << QString::fromStdString(getfName(img_paths.at(i)));
    }

    dbController->deleteMyPhotos(myArticle->getId());
    dbController->addMyPhotos(fname_paths,myArticle->getId(),getSelectedSectionID(),getSelectedPhotographerLuid());
}

void newArticleWorkspaceWindow::on_delete_pushButton_clicked()
{
    cout << "del" << endl;
    cb_vec_t::iterator iter = cb_vec.begin();
    while(iter != cb_vec.end())
    {
        QCheckBox *c_box = *iter;
        if(c_box->isChecked())
        {
            vert_layout->removeItem(vert_layout->itemAt(iter - cb_vec.begin()));
            img_paths.removeAt(iter - cb_vec.begin());
            cb_vec.erase(iter);
        }
        else
            iter++;

    }

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
