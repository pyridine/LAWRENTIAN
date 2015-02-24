#ifndef EDITEMPLOYEEINFO_H
#define EDITEMPLOYEEINFO_H

#include <QDialog>

namespace Ui {
class EditEmployeeInfo;
}

class EditEmployeeInfo : public QDialog
{
    Q_OBJECT

public:
    explicit EditEmployeeInfo(QWidget *parent = 0);
    ~EditEmployeeInfo();

private:
    Ui::EditEmployeeInfo *ui;
};

#endif // EDITEMPLOYEEINFO_H
