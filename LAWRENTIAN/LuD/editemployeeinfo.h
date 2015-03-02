#ifndef EDITEMPLOYEEINFO_H
#define EDITEMPLOYEEINFO_H

#include "employeeswidget.h"

#include <QDialog>
#include "editemployeeinfodbc.h"
#include "client.h"

namespace Ui {
class EditEmployeeInfo;
}

class EditEmployeeInfo : public QDialog
{
    Q_OBJECT

public:
    explicit EditEmployeeInfo(QWidget *parent = 0, LoginCredentials *c = new LoginCredentials());
    ~EditEmployeeInfo() throw();

    void initDB(Client *c);
    void populateNameComboBox();
    void populateAllFields();
    void updateAllFields();
    void initSelectedName(QString selectedName);
    employeesWidget *myParent;
    string getSelectedName();

private slots:
    void on_nameComboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_probationComboBox_currentIndexChanged(int index);

private:
    void handlePermissions();
    LoginCredentials* login;
    Ui::EditEmployeeInfo *ui;
    EditEmployeeInfoDBC *editEmployeeInfoDBC;

};

#endif // EDITEMPLOYEEINFO_H
