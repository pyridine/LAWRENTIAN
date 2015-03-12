#include "copyhistorywindow.h"
#include "ui_copyhistorywindow.h"
#include <string.h>
#include <QRadioButton>
#include <QTableWidget>
#include "FileSystem.h"
#include "Sender.h"
#include <iostream>
#include <QFileDialog>
#include <QDate>
#include "diff.h"
#include "DocxmlToString.h"



CopyHistoryWindow::CopyHistoryWindow(QWidget *parent,const std::string& date,
                                     const std::string& sec, const std::string& art) :
    QDialog(parent),
    ui(new Ui::CopyHistoryWindow)
{
    using namespace FileSystem;
    using namespace std;

    setWindowFlags(Qt::WindowStaysOnTopHint);

    Sender sndr = Sender();

    currentRow = -1;

    this->date = date;
    this->sec = sec;
    this->art = art;

    ui->setupUi(this);
    ui->copyHistory_tableWidget->setColumnCount(1);
    ui->copyHistory_tableWidget->setColumnWidth(0,381);
    this->setWindowTitle("Copy History");

    QTableWidgetItem* h1 = new QTableWidgetItem(QString("History"),QTableWidgetItem::Type);
    h1->setTextAlignment(Qt::AlignLeft);
//    QTableWidgetItem* h2 = new QTableWidgetItem(QString("Version"),QTableWidgetItem::Type);
//    h1->setTextAlignment(Qt::AlignCenter);
//    QTableWidgetItem* h3 = new QTableWidgetItem(QString("Date"),QTableWidgetItem::Type);
//    h3->setTextAlignment(Qt::AlignCenter);

    ui->copyHistory_tableWidget->setHorizontalHeaderItem(0,h1);
//    ui->copyHistory_tableWidget->setHorizontalHeaderItem(1,h2);
//    ui->copyHistory_tableWidget->setHorizontalHeaderItem(2,h3);

    ver_seq = sndr.getHistory(date, sec,art,fs::COPY);
    VerSeq::const_iterator iter = ver_seq.begin();
    for(iter; iter != ver_seq.end(); iter++)
    {
        int index = iter - ver_seq.begin();
        int row_count = ui->copyHistory_tableWidget->rowCount();
        ui->copyHistory_tableWidget->insertRow(row_count);

//        QTableWidgetItem* h4 = new QTableWidgetItem(QString(""),QTableWidgetItem::Type);
//        h4->setTextAlignment(Qt::AlignCenter);
//        ui->copyHistory_tableWidget->setVerticalHeaderItem(row_count,h4);

//        QRadioButton *radio_button = new QRadioButton;
//        rb_vec.push_back(radio_button);

//        QWidget *pWidget = new QWidget();
//        QHBoxLayout *pLayout = new QHBoxLayout();
//        pLayout->addWidget(radio_button);
//        pLayout->setAlignment(Qt::AlignLeft);
//        pLayout->setContentsMargins(0,0,0,0);
//        pWidget->setLayout(pLayout);

//        ui->copyHistory_tableWidget->setCellWidget(index,0,pWidget);

//        string s2 = iter->verName;
//        QTableWidgetItem* h5 = new QTableWidgetItem(s2.c_str());
//        h5->setTextAlignment(Qt::AlignCenter);
//        ui->copyHistory_tableWidget->setItem(index,1,h5);

        string articleName = iter->verName;
        TimeIce t = iter->time;
        string author = "SETME!";

//        string month = std::to_string((long long)t.month);
//        month = month.size() ? month : "00";
//        month = month.size() == 1 ? "0"+month : month;
        string month = QDate::longMonthName((int)t.month).toStdString();

        string day = std::to_string((long long)t.day);
        day = day.size() ? day : "00";
        day = day.size() == 1 ? "0"+day : day;

        string year = std::to_string((long long)t.year);
        string hour = std::to_string((long long)t.hour);
        hour = hour.size() ? hour : "00";
        hour = hour.size() == 1 ? "0"+hour : hour;

        string minute = std::to_string((long long)t.minute);
        minute = minute.size() ? minute : "00";
        minute = minute.size() == 1 ? "0"+minute : minute;

        string second = std::to_string((long long)t.second );
        second = second.size() ? second : "00";
        second = second.size() == 1 ? "0"+second : second;

        string s3 =  author + " - " + month + " " + day + " " + year + ". ("
                + hour + ":" + minute + ")"
               /* + t.dayOfTheWeek*/;

        QTableWidgetItem* articleWidget = new QTableWidgetItem(s3.c_str());
        articleWidget->setTextAlignment(Qt::AlignCenter);

        ui->copyHistory_tableWidget->setItem(index,0,articleWidget);
    }

    ui->copyHistory_tableWidget->resizeColumnsToContents();
    ui->copyHistory_tableWidget->resizeRowsToContents();

}

CopyHistoryWindow::~CopyHistoryWindow()
{
    delete ui;
}

void CopyHistoryWindow::on_download_pushButton_clicked()
{
    using namespace std;
    using namespace FileSystem;
    if(currentRow >= 0){
/*
    rb_vec_t::const_iterator iter = rb_vec.begin();

    Version ver;
    for(iter; iter != rb_vec.end(); iter++)
    {
        QRadioButton *rb = *iter;
        if(rb->isChecked())
        {
            ver = ver_seq[iter - rb_vec.begin()];
            break;
        }
    }

    if(!ver.verName.size())
        return;
*/
    QString Qdown_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                          "/home",
                                                          QFileDialog::ShowDirsOnly
                                                          | QFileDialog::DontResolveSymlinks);
    if (Qdown_dir.isEmpty())
        return;


    int ver_num = currentRow;
    stringstream inter;
    inter<<ver_num; //this is the only way I know how to make an int into a str...
    string temp = art + inter.str() + fs::extCOPY;
    string down_dir = Qdown_dir.toStdString() + "/" + temp ;

    //    int ver_num = 1;
    //    string fName = "getfName(ver.verName) + std::to_string((long long)ver_num)";
    //    string down_dir = getfName(" Qdown_dir.toStdString() fName") ;


    Sender sndr = Sender();
    sndr.requestCopy(date,sec,art,down_dir,currentRow);

    this->close();
    }
}

std::string CopyHistoryWindow::getfName(const std::string& str)
{
    using namespace std;

    string s = str;
    string::const_iterator iter = str.begin();
    for (iter; iter!= str.end(); iter++)
    {
        if(*iter == '*')
            break;
    }

    s.resize(iter - str.begin());
    return s;
}



void CopyHistoryWindow::on_cancel_pushButton_clicked()
{
    this->close();
}

void CopyHistoryWindow::on_copyHistory_tableWidget_cellClicked(int row, int column)
{
    int b = column;
    b++; //This is just so the compiler doesn't complain about an unused variable.

    ui->previewWindow->setText("Preview is loading...");
    if(ui->ifDifCheckBox->isChecked())
         displayPreview(row,row-1);
    else displayPreview(row,-1);
}

void CopyHistoryWindow::displayPreview(int new_index,int past_index){
    using namespace std; //why the hell is this file structured like this
    currentRow = new_index;

    if(new_index >= 0){
        if(past_index >= 0){
            //Compare one text with another.
            string newText = getArticleText(new_index);
            string oldText = getArticleText(past_index);

            //split strings into queues here, and then call makediffhtml.
            queue<string>* newSQ = JDiff::splitStringToQueue(newText);
            queue<string>* oldSQ = JDiff::splitStringToQueue(oldText);

            queue<string>* diffQ = JDiff::makeHTMLDiff_Q(*oldSQ,*newSQ);
            stringstream diff;
            while(diffQ->size()){
                diff<<diffQ->front();
                diffQ->pop();
            }
            ui->previewWindow->setHtml(diff.str().c_str());
        } else{
            //COMPARE THE TEXT WITH ITSELF LOL
            string newText = getArticleText(new_index);

            ui->previewWindow->setText(JDiff::makeHTML(newText).c_str());
        }
    }
}



std::string CopyHistoryWindow::getArticleText(int articleNum){
    string articleNumString;

    //conv articleNum to string
    std::stringstream out;
    out << articleNum;
    articleNumString = out.str();

    using namespace std;
    Sender sndr = Sender();
    if(articleNum >= 0){
        string fileName = art;
        if(articleNum != 0) fileName += articleNumString;
        string fileNameNoExt = fileName;
        fileName += ".xml";

        string filePath = QDir::currentPath().toStdString();
        filePath+="/";filePath+=fileName;

        sndr.requestXML(this->date,this->sec,this->art,filePath,articleNum);

        //string xmlLoc = DocxmlToString::unzipDocx(QDir::currentPath().toStdString(),fileNameNoExt);
        string doc = DocxmlToString::parse(filePath);
        if(!QFile::remove(fileName.c_str())){
               cout << "Failed to remove xml." << endl;
        }

        return doc;
    } else{
        return "ERROR!!";
    }

}



void CopyHistoryWindow::on_ifDifCheckBox_clicked()
{
    this->on_copyHistory_tableWidget_cellClicked(currentRow,0);
}
