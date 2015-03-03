#include "photopoolwindow.h"
#include "ui_photopoolwindow.h"
#include "photopoolwindowdbc.h"
#include "Sender.h"
#include <iostream>
#include <QVariant>
#include <QListWidgetItem>

PhotoPoolWindow::PhotoPoolWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhotoPoolWindow)
{
    ui->setupUi(this);
}

PhotoPoolWindow::~PhotoPoolWindow()
{
    delete ui;
}

void PhotoPoolWindow::init(Client *c)
{
    using namespace std;

    dbController = new PhotoPoolWindowDBC(c);
    vector<PhotoPoolWindowDBC::Sec_t> all_sections = dbController->getSections();
    vector<PhotoPoolWindowDBC::Sec_t>::const_iterator iter = all_sections.begin();

    while(iter != all_sections.end())
    {
        int index = iter - all_sections.begin();
        QVariant secId(iter->first);
        QString secName(QString::fromStdString(iter->second));

        ui->section_comboBox->insertItem(index, secName);
        ui->section_comboBox->setItemData(index, secId);

        iter++;
    }

    QStringList allIssueDates = dbController->getIssueDates();
    ui->fromIssueDate_comboBox->addItems(allIssueDates);
    ui->toIssueDate_comboBox->addItems(allIssueDates);

    drawArtsOnListView();
}

void PhotoPoolWindow::on_section_comboBox_currentIndexChanged(int index)
{
    drawArtsOnListView();
}

void PhotoPoolWindow::on_fromIssueDate_comboBox_activated(int index)
{
    drawArtsOnListView();
}

void PhotoPoolWindow::on_toIssueDate_comboBox_activated(int index)
{
    drawArtsOnListView();
}


void PhotoPoolWindow::drawArtsOnListView()
{
    int secID = ui->section_comboBox->currentData().toInt();
    QString fromDate = ui->fromIssueDate_comboBox->currentText();
    QString toDate = ui->toIssueDate_comboBox->currentText();

    QStringList filteredArticles = dbController->getArtsFromSec(secID, fromDate, toDate);
    ui->article_listWidget->clear();
    ui->article_listWidget->addItems(filteredArticles);
}

void PhotoPoolWindow::drawImages(const string &issueDate, const string &section, const string &title)
{
    using namespace FileSystem;
    using namespace std;

    Sender sndr = Sender();
    StrSeq imgNames = sndr.getImageList(issueDate, section, title);

    StrSeq::const_iterator iter = imgNames.begin();
    while(iter != imgNames.end())
    {
        setupImage(*iter + fs::extIMAGE);
        iter++;
    }
}

void PhotoPoolWindow::setupImage(const string &fNameExt)
{

}

void PhotoPoolWindow::on_allArt_pushButton_clicked()
{
    int secID = ui->section_comboBox->currentData().toInt();
    QStringList allArts = dbController->getArtsFromSec(secID);

    ui->article_listWidget->clear();
    ui->article_listWidget->addItems(allArts);
}

void PhotoPoolWindow::on_article_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    using namespace std;

    string title = item->text().toStdString();
    string section = ui->section_comboBox->currentText().toStdString();
    QString QIssueDate = QString::fromStdString(dbController->getIssueDateOfArt(item->text()));
    string issueDate = QDate::fromString(QIssueDate,df::dbFormat).toString(df::srvrFormat).toStdString();

    drawImages(issueDate, section, title);

}
