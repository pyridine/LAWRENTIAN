#include "copyhistorywindow.h"
#include "ui_copyhistorywindow.h"
#include <string.h>
#include <QRadioButton>
#include <QTableWidget>
#include "FileSystem.h"
#include "Sender.h"
#include <QFileDialog>

CopyHistoryWindow::CopyHistoryWindow(QWidget *parent,const std::string& sec,
                                     const std::string& art, const std::string& type,
                                     const std::string& fName) :
    QDialog(parent),
    ui(new Ui::CopyHistoryWindow)
{
    using namespace FileSystem;
    using namespace std;

    Sender sndr = Sender();

    this->sec = sec;
    this->art = art;
    this->type = type;

    ui->setupUi(this);
    ui->copyHistory_tableWidget->setColumnCount(3);

    QTableWidgetItem* h1 = new QTableWidgetItem(QString(""),QTableWidgetItem::Type);
    QTableWidgetItem* h2 = new QTableWidgetItem(QString("Version"),QTableWidgetItem::Type);
    QTableWidgetItem* h3 = new QTableWidgetItem(QString("Date"),QTableWidgetItem::Type);

    ui->copyHistory_tableWidget->setHorizontalHeaderItem(0,h1);
    ui->copyHistory_tableWidget->setHorizontalHeaderItem(1,h2);
    ui->copyHistory_tableWidget->setHorizontalHeaderItem(2,h3);

    ver_seq = sndr.getHistory(sec,art,type,fName);
    // VerSeq ver_seq = sndr.getHistory("News","Not Really","Copy","Yo");
    cout << ver_seq.size() << endl;
    VerSeq::const_iterator iter = ver_seq.begin();
    for(iter; iter != ver_seq.end(); iter++)
    {
        int row_count = ui->copyHistory_tableWidget->rowCount();
        ui->copyHistory_tableWidget->insertRow(row_count);
        int index = iter - ver_seq.begin();

        QRadioButton *radio_button = new QRadioButton;
        rb_vec.push_back(radio_button);
        ui->copyHistory_tableWidget->setCellWidget(index,0,radio_button);

        string s2 = iter->verName;
        ui->copyHistory_tableWidget->setItem(index,1,new QTableWidgetItem(s2.c_str()));

        string s3 = std::to_string((long long)iter->verNum);
        ui->copyHistory_tableWidget->setItem(index,2,new QTableWidgetItem(s3.c_str()));
    }

   // ui->copyHistory_tableWidget->setItem(1,1,radio_button);
}

CopyHistoryWindow::~CopyHistoryWindow()
{
    delete ui;
}

void CopyHistoryWindow::on_download_pushButton_clicked()
{
    using namespace std;
    using namespace FileSystem;

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

    QString Qdown_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    if (Qdown_dir.isEmpty())
        return;

    int ver_num = ver.verNum;
    string temp = getfName(ver.verName) + std::to_string((long long)ver_num) +
            ".docx";
    string down_dir = Qdown_dir.toStdString() + "/" + temp ;
    string fName = ver.verName;

//    int ver_num = 1;
//    string fName = "getfName(ver.verName) + std::to_string((long long)ver_num)";
//    string down_dir = getfName(" Qdown_dir.toStdString() fName") ;


    cout << down_dir << endl << fName << endl << ver_num << endl;
    Sender sndr = Sender();
    sndr.requestFile(sec,art,type,fName,down_dir,ver_num);
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


