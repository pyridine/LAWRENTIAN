#ifndef COPYHISTORYWINDOW_H
#define COPYHISTORYWINDOW_H

#include <QDialog>
#include <vector>
#include <QRadioButton>

#include "FileSystem.h"

namespace Ui {
class CopyHistoryWindow;
}

class CopyHistoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CopyHistoryWindow(QWidget *parent = 0,const std::string& sec = "",
                               const std::string& art = "", const std::string& type = "",
                               const std::string& fName = "");
    ~CopyHistoryWindow();

private slots:
    void on_download_pushButton_clicked();

    void on_cancel_pushButton_clicked();

private:
    typedef std::vector<QRadioButton*> rb_vec_t;

    Ui::CopyHistoryWindow *ui;
    rb_vec_t rb_vec;
    FileSystem::VerSeq ver_seq;

    std::string sec;
    std::string art;
    std::string type;

    std::string getfName(const std::string& str);
};

#endif // COPYHISTORYWINDOW_H
