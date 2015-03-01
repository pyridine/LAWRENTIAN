/********************************************************************************
** Form generated from reading UI file 'editprofilewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPROFILEWIDGET_H
#define UI_EDITPROFILEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditProfileWidget
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QFrame *line;
    QLabel *label_11;
    QPushButton *pushButton;
    QPushButton *resetPushButton;
    QLineEdit *nameTextField;
    QLineEdit *luidTextField;
    QLineEdit *titleTextField;
    QLineEdit *emailTextField;
    QLineEdit *phoneTextField;
    QLineEdit *usernameTextField;
    QLineEdit *oldPasswordTextField;
    QLineEdit *newPasswordTextField;
    QLineEdit *confirmPasswordTextField;

    void setupUi(QDialog *EditProfileWidget)
    {
        if (EditProfileWidget->objectName().isEmpty())
            EditProfileWidget->setObjectName(QStringLiteral("EditProfileWidget"));
        EditProfileWidget->resize(489, 488);
        label = new QLabel(EditProfileWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 50, 62, 16));
        label_2 = new QLabel(EditProfileWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 170, 62, 16));
        label_3 = new QLabel(EditProfileWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 210, 62, 16));
        label_4 = new QLabel(EditProfileWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 90, 62, 16));
        label_5 = new QLabel(EditProfileWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 130, 62, 16));
        label_6 = new QLabel(EditProfileWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(60, 300, 71, 16));
        label_7 = new QLabel(EditProfileWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 10, 141, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_7->setFont(font);
        label_8 = new QLabel(EditProfileWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(40, 340, 101, 16));
        label_9 = new QLabel(EditProfileWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(40, 380, 101, 16));
        label_10 = new QLabel(EditProfileWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 420, 131, 16));
        line = new QFrame(EditProfileWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 240, 461, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_11 = new QLabel(EditProfileWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(40, 260, 161, 16));
        label_11->setFont(font);
        pushButton = new QPushButton(EditProfileWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(360, 450, 114, 32));
        resetPushButton = new QPushButton(EditProfileWidget);
        resetPushButton->setObjectName(QStringLiteral("resetPushButton"));
        resetPushButton->setGeometry(QRect(10, 450, 114, 32));
        resetPushButton->setAutoDefault(false);
        nameTextField = new QLineEdit(EditProfileWidget);
        nameTextField->setObjectName(QStringLiteral("nameTextField"));
        nameTextField->setGeometry(QRect(100, 50, 261, 21));
        luidTextField = new QLineEdit(EditProfileWidget);
        luidTextField->setObjectName(QStringLiteral("luidTextField"));
        luidTextField->setEnabled(false);
        luidTextField->setGeometry(QRect(100, 90, 261, 21));
        titleTextField = new QLineEdit(EditProfileWidget);
        titleTextField->setObjectName(QStringLiteral("titleTextField"));
        titleTextField->setEnabled(false);
        titleTextField->setGeometry(QRect(100, 130, 261, 21));
        emailTextField = new QLineEdit(EditProfileWidget);
        emailTextField->setObjectName(QStringLiteral("emailTextField"));
        emailTextField->setGeometry(QRect(100, 170, 261, 21));
        phoneTextField = new QLineEdit(EditProfileWidget);
        phoneTextField->setObjectName(QStringLiteral("phoneTextField"));
        phoneTextField->setGeometry(QRect(100, 210, 261, 21));
        usernameTextField = new QLineEdit(EditProfileWidget);
        usernameTextField->setObjectName(QStringLiteral("usernameTextField"));
        usernameTextField->setGeometry(QRect(150, 300, 211, 21));
        oldPasswordTextField = new QLineEdit(EditProfileWidget);
        oldPasswordTextField->setObjectName(QStringLiteral("oldPasswordTextField"));
        oldPasswordTextField->setGeometry(QRect(150, 340, 211, 21));
        oldPasswordTextField->setEchoMode(QLineEdit::Password);
        newPasswordTextField = new QLineEdit(EditProfileWidget);
        newPasswordTextField->setObjectName(QStringLiteral("newPasswordTextField"));
        newPasswordTextField->setGeometry(QRect(150, 380, 211, 21));
        newPasswordTextField->setEchoMode(QLineEdit::Password);
        confirmPasswordTextField = new QLineEdit(EditProfileWidget);
        confirmPasswordTextField->setObjectName(QStringLiteral("confirmPasswordTextField"));
        confirmPasswordTextField->setGeometry(QRect(150, 420, 211, 21));
        confirmPasswordTextField->setEchoMode(QLineEdit::Password);

        retranslateUi(EditProfileWidget);

        QMetaObject::connectSlotsByName(EditProfileWidget);
    } // setupUi

    void retranslateUi(QDialog *EditProfileWidget)
    {
        EditProfileWidget->setWindowTitle(QApplication::translate("EditProfileWidget", "Dialog", 0));
        label->setText(QApplication::translate("EditProfileWidget", "Name:", 0));
        label_2->setText(QApplication::translate("EditProfileWidget", "Email:", 0));
        label_3->setText(QApplication::translate("EditProfileWidget", "Phone:", 0));
        label_4->setText(QApplication::translate("EditProfileWidget", "LUID:", 0));
        label_5->setText(QApplication::translate("EditProfileWidget", "Title:", 0));
        label_6->setText(QApplication::translate("EditProfileWidget", "Username:", 0));
        label_7->setText(QApplication::translate("EditProfileWidget", "Personal Information", 0));
        label_8->setText(QApplication::translate("EditProfileWidget", "Old Password:", 0));
        label_9->setText(QApplication::translate("EditProfileWidget", "New Password:", 0));
        label_10->setText(QApplication::translate("EditProfileWidget", "Confirm Password:", 0));
        label_11->setText(QApplication::translate("EditProfileWidget", "Account Information", 0));
        pushButton->setText(QApplication::translate("EditProfileWidget", "Done", 0));
        resetPushButton->setText(QApplication::translate("EditProfileWidget", "Reset", 0));
        oldPasswordTextField->setInputMask(QString());
        oldPasswordTextField->setPlaceholderText(QApplication::translate("EditProfileWidget", "Enter Old Password...", 0));
        newPasswordTextField->setPlaceholderText(QApplication::translate("EditProfileWidget", "Enter New Password...", 0));
        confirmPasswordTextField->setPlaceholderText(QApplication::translate("EditProfileWidget", "Confirm New Password...", 0));
    } // retranslateUi

};

namespace Ui {
    class EditProfileWidget: public Ui_EditProfileWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPROFILEWIDGET_H
