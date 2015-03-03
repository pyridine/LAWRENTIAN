#ifndef MANAGETITLES_H
#define MANAGETITLES_H

#include <QWidget>
#include <QWindow>
#include <QDialog>
#include "permissionswidget.h"
#include <QListWidgetItem>

namespace Ui {
class ManageTitles;
}

class ManageTitles : public QDialog
{
    Q_OBJECT

public:
    explicit ManageTitles(QWidget *Mparent = 0, bool wantTitleEdit = false, int meId = -1);
    void initDB_LOL(PermissionsWidgetDBC* d);
    ~ManageTitles();

private slots:

    void on_cancelButton_clicked();

    void on_applyButton_clicked();

    void on_allPermissions_currentRowChanged(int currentRow);

    void on_titleComboBox_currentIndexChanged(int index);

    void on_allPermissions_itemDoubleClicked(QListWidgetItem *item);

    void on_containedPermissions_itemDoubleClicked(QListWidgetItem *item);

private:
    int QLISTWIDGET_FREEDATA; //See the same-name variable in permissionswidget
    bool isTitle; //The window is the same for title/employee, but we do DB things slightly differently.
    int editeeID; // The ID of the editee (employee or title)
    Ui::ManageTitles *ui;
    PermissionsWidget* parent;
    void updateDatabase();
    void getPermissions();
    void getEditeePermissions();
    void applyChangesToDatabase();
    void tryAddPermission(int a);

    void populateTitleComboBox();

    int getSelectedPermissionPoolToken();
    int getSelectedEiteePermissionToken();



    PermissionsWidgetDBC* dbController; //Why the fuck not? I'm too lazy anyway...

};

#endif // MANAGETITLES_H
