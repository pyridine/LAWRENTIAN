#include "editprofilewidget.h"
#include "ui_editprofilewidget.h"

#include <iostream>
#include "alert.h"

EditProfileWidget::EditProfileWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditProfileWidget)
{
    ui->setupUi(this);
}

void EditProfileWidget::init(LoginCredentials* l){
    loginCred = l;
}

void EditProfileWidget::initDB(Client *c){
    editProfileDBC = new EditProfileDBC(c);
}

void EditProfileWidget::populateAllFields()
{
    int loginId = loginCred->getLUID();

    string name = editProfileDBC->collectName(loginId);
    ui->nameTextField->setText(QString::fromStdString(name));

    int employeeID = editProfileDBC->collectLuid(loginId);
    ui->luidTextField->setText(QString::number(employeeID));

    string title = editProfileDBC->collectTitle(loginId);
    ui->titleTextField->setText(QString::fromStdString(title));

    string phone = editProfileDBC->collectPhone(loginId);
    ui->phoneTextField->setText(QString::fromStdString(phone));

    string email = editProfileDBC->collectEmail(loginId);
    ui->emailTextField->setText(QString::fromStdString(email));

    string username = editProfileDBC->collectUsername(loginId);
    ui->usernameTextField->setText(QString::fromStdString(username));
}

EditProfileWidget::~EditProfileWidget()
{
    delete ui;
}

void EditProfileWidget::on_resetPushButton_clicked()
{
    populateAllFields();
}

void EditProfileWidget::on_pushButton_clicked()
{
    int loginId = loginCred->getLUID();

    string oldPasswordTyped = ui->oldPasswordTextField->text().toStdString();
    string oldPasswordDB = editProfileDBC->collectOldPassword(loginId);
    string newPassword = ui->newPasswordTextField->text().toStdString();
    string confirmPassword = ui->confirmPasswordTextField->text().toStdString();

    bool fieldsAreSatisfied = true;

    if(newPassword != ""){
        //Check to see if passwords match.
        if(newPassword.compare(confirmPassword) != 0){
            Alert::showAlert("Error", "Your passwords don't match!");
            fieldsAreSatisfied = false;
        }
        // Check to see if inputted oldPassword is the same as the password in the database
        if(oldPasswordTyped.compare(oldPasswordDB) != 0){
            Alert::showAlert("Error", "Incorrect password entered");
            fieldsAreSatisfied = false;
        }
        //Check to see if password conforms to standards.
        if(!isPasswordSuitable(newPassword)){
            Alert::showAlert("Error", "Password must contain at least one number (0-9), one upper case character (A-Z), and one lower case character (a-z)");
            fieldsAreSatisfied = false;
        }
    }

    if(fieldsAreSatisfied){
        int loginId = loginCred->getLUID();
        string name = ui->nameTextField->text().toStdString();
        string email = ui->emailTextField->text().toStdString();
        string phone = ui->phoneTextField->text().toStdString();
        string username = ui->usernameTextField->text().toStdString();
        if(newPassword == ""){
            editProfileDBC->saveEmployeeChangesWithoutPassword(name, email, phone, username, loginId);
        }
        else{
            editProfileDBC->saveEmployeeChangesWithPassword(name, email, phone, username, newPassword, loginId);
        }
        this->close();
        myParent->setWelcomeLabel();
    }

}

bool EditProfileWidget::isPasswordSuitable(string s){
    string::iterator itr;
    bool containsNum = false;
    bool containsLow = false;
    bool containsUp = false;

    if(s.begin() == s.end()){
        return false;
    }

    for(itr = s.begin(); itr < s.end(); itr++){
        if(islower(*itr)){
            containsLow = true;
        }
        if(isupper(*itr)){
            containsUp = true;
        }
        if(!isdigit(*itr)){
            containsNum = true;
        }
    }

    return (containsNum && containsLow && containsUp);
}

