#ifndef PHOTOPOOLWINDOW_H
#define PHOTOPOOLWINDOW_H

#include <QDialog>

namespace Ui {
class PhotoPoolWindow;
}

class PhotoPoolWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PhotoPoolWindow(QWidget *parent = 0);
    ~PhotoPoolWindow();

private:
    Ui::PhotoPoolWindow *ui;
};

#endif // PHOTOPOOLWINDOW_H
