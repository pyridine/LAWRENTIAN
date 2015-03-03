#ifndef PERMISSIONSWIDGET_H
#define PERMISSIONSWIDGET_H

#include <QWidget>
#include "permissionswidgetdbc.h"
#include "client.h"

namespace Ui {
class PermissionsWidget;
}

class PermissionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PermissionsWidget(QWidget *parent = 0);
    void initDB(Client* c);
    ~PermissionsWidget();
    void updateEmployeeList();

private slots:
    void on_employeeCombobox_currentIndexChanged(int index);

    void on_permissionList_currentRowChanged(int currentRow);

private:
    void populateEmployeeList();
    int QLISTWIDGET_FREEDATA;
    int getSelectedPermissionToken();
    int getSelectedEmployee_ID();
    int getSelectedEmployee_TitleID();
    Ui::PermissionsWidget *ui;


    PermissionsWidgetDBC* dbController;

};

#endif // PERMISSIONSWIDGET_H
