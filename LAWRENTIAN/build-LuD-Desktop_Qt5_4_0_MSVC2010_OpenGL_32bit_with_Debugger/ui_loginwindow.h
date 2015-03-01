/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLineEdit *usernamebox;
    QLineEdit *passwordbox;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QStringLiteral("LoginWindow"));
        LoginWindow->resize(401, 174);
        pushButton = new QPushButton(LoginWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(110, 120, 80, 21));
        pushButton_2 = new QPushButton(LoginWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(210, 120, 80, 21));
        label = new QLabel(LoginWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 20, 161, 16));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        usernamebox = new QLineEdit(LoginWindow);
        usernamebox->setObjectName(QStringLiteral("usernamebox"));
        usernamebox->setGeometry(QRect(180, 60, 113, 21));
        passwordbox = new QLineEdit(LoginWindow);
        passwordbox->setObjectName(QStringLiteral("passwordbox"));
        passwordbox->setGeometry(QRect(180, 90, 113, 21));
        passwordbox->setEchoMode(QLineEdit::Password);
        label_2 = new QLabel(LoginWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(110, 60, 71, 20));
        label_3 = new QLabel(LoginWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 90, 51, 16));

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QDialog *LoginWindow)
    {
        LoginWindow->setWindowTitle(QApplication::translate("LoginWindow", "Dialog", 0));
        pushButton->setText(QApplication::translate("LoginWindow", "Login", 0));
        pushButton_2->setText(QApplication::translate("LoginWindow", "Register...", 0));
        label->setText(QApplication::translate("LoginWindow", "L.A.W.R.E.N.T.I.A.N.", 0));
        label_2->setText(QApplication::translate("LoginWindow", "Username:", 0));
        label_3->setText(QApplication::translate("LoginWindow", "Password:", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
