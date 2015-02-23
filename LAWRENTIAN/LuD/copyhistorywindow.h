#ifndef COPYHISTORYWINDOW_H
#define COPYHISTORYWINDOW_H

#include <QDialog>

namespace Ui {
class CopyHistoryWindow;
}

class CopyHistoryWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CopyHistoryWindow(QWidget *parent = 0);
    ~CopyHistoryWindow();

private:
    Ui::CopyHistoryWindow *ui;
};

#endif // COPYHISTORYWINDOW_H
