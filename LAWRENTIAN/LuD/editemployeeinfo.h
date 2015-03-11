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
    explicit EditEmployeeInfo(QWidget *parent = 0);
    ~EditEmployeeInfo() throw();

    //explicit EditEmployeeInfo(QWidget *parent = 0, LoginCredentials *c = new LoginCredentials());
    void initDB(Client *c);
    void init(LoginCredentials *c, employeesWidget *parent);
    void populateNameComboBox();
    void populateAllFields();
    void updateAllFields();
    void initSelectedNameProbation(QString selectedName);
    void initSelectedNameApproval(QString selectedName);
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
    employeesWidget* parentYay;

};

#endif // EDITEMPLOYEEINFO_H
