#ifndef EDITPROFILEWIDGET_H
#define EDITPROFILEWIDGET_H

#include <QDialog>
#include "profilewidget.h"
#include "logincredentials.h"
#include "editprofiledbc.h"

namespace Ui {
class EditProfileWidget;
}

class EditProfileWidget : public QDialog
{
    Q_OBJECT

public:
    explicit EditProfileWidget(QWidget *parent = 0);
    ~EditProfileWidget() throw();

    void initDB(Client *c);
    void init(LoginCredentials* l);
    void populateAllFields();
    bool isPasswordSuitable(string s);

    profileWidget *myParent;

private slots:
    void on_resetPushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::EditProfileWidget *ui;
    LoginCredentials *loginCred;
    EditProfileDBC *editProfileDBC;
};

#endif // EDITPROFILEWIDGET_H
