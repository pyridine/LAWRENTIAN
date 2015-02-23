#include "copyhistorywindow.h"
#include "ui_copyhistorywindow.h"

CopyHistoryWindow::CopyHistoryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CopyHistoryWindow)
{
    ui->setupUi(this);
    ui->copyHistory_tableWidget->setColumnCount(3);
    // first column -> radio buttos
    // second column -> version name
    // third column -> date info
}

CopyHistoryWindow::~CopyHistoryWindow()
{
    delete ui;
}
