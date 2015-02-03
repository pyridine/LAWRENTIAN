/********************************************************************************
** Form generated from reading UI file 'checkemployeeswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKEMPLOYEESWINDOW_H
#define UI_CHECKEMPLOYEESWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CheckEmployeesWindow
{
public:
    QPushButton *pushButton;
    QLineEdit *nameTextField;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_2;
    QLineEdit *phoneTextField;
    QGraphicsView *idPicture;
    QLineEdit *luIdTextField;
    QLabel *label_3;
    QLineEdit *emailTextField;
    QLabel *label_5;
    QLineEdit *usernameTextField;

    void setupUi(QDialog *CheckEmployeesWindow)
    {
        if (CheckEmployeesWindow->objectName().isEmpty())
            CheckEmployeesWindow->setObjectName(QStringLiteral("CheckEmployeesWindow"));
        CheckEmployeesWindow->resize(520, 272);
        pushButton = new QPushButton(CheckEmployeesWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(390, 230, 114, 32));
        nameTextField = new QLineEdit(CheckEmployeesWindow);
        nameTextField->setObjectName(QStringLiteral("nameTextField"));
        nameTextField->setGeometry(QRect(110, 30, 231, 21));
        label = new QLabel(CheckEmployeesWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 30, 41, 16));
        label_4 = new QLabel(CheckEmployeesWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 150, 41, 16));
        label_2 = new QLabel(CheckEmployeesWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 70, 41, 16));
        phoneTextField = new QLineEdit(CheckEmployeesWindow);
        phoneTextField->setObjectName(QStringLiteral("phoneTextField"));
        phoneTextField->setGeometry(QRect(110, 150, 231, 21));
        idPicture = new QGraphicsView(CheckEmployeesWindow);
        idPicture->setObjectName(QStringLiteral("idPicture"));
        idPicture->setGeometry(QRect(360, 30, 141, 141));
        luIdTextField = new QLineEdit(CheckEmployeesWindow);
        luIdTextField->setObjectName(QStringLiteral("luIdTextField"));
        luIdTextField->setGeometry(QRect(110, 70, 231, 21));
        label_3 = new QLabel(CheckEmployeesWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 110, 41, 16));
        emailTextField = new QLineEdit(CheckEmployeesWindow);
        emailTextField->setObjectName(QStringLiteral("emailTextField"));
        emailTextField->setGeometry(QRect(110, 110, 231, 21));
        label_5 = new QLabel(CheckEmployeesWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 190, 71, 16));
        usernameTextField = new QLineEdit(CheckEmployeesWindow);
        usernameTextField->setObjectName(QStringLiteral("usernameTextField"));
        usernameTextField->setGeometry(QRect(110, 190, 231, 21));

        retranslateUi(CheckEmployeesWindow);

        QMetaObject::connectSlotsByName(CheckEmployeesWindow);
    } // setupUi

    void retranslateUi(QDialog *CheckEmployeesWindow)
    {
        CheckEmployeesWindow->setWindowTitle(QApplication::translate("CheckEmployeesWindow", "Check Employees", 0));
        pushButton->setText(QApplication::translate("CheckEmployeesWindow", "Next", 0));
#ifndef QT_NO_ACCESSIBILITY
        nameTextField->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        nameTextField->setPlaceholderText(QApplication::translate("CheckEmployeesWindow", "Enter Name...", 0));
        label->setText(QApplication::translate("CheckEmployeesWindow", "Name:", 0));
        label_4->setText(QApplication::translate("CheckEmployeesWindow", "Phone:", 0));
        label_2->setText(QApplication::translate("CheckEmployeesWindow", "LU ID#:", 0));
        phoneTextField->setPlaceholderText(QApplication::translate("CheckEmployeesWindow", "Enter Phone#...", 0));
        luIdTextField->setPlaceholderText(QApplication::translate("CheckEmployeesWindow", "Enter LU ID#...", 0));
        label_3->setText(QApplication::translate("CheckEmployeesWindow", "Email:", 0));
        emailTextField->setPlaceholderText(QApplication::translate("CheckEmployeesWindow", "Enter Email...", 0));
        label_5->setText(QApplication::translate("CheckEmployeesWindow", "Username:", 0));
        usernameTextField->setPlaceholderText(QApplication::translate("CheckEmployeesWindow", "Enter Username...", 0));
    } // retranslateUi

};

namespace Ui {
    class CheckEmployeesWindow: public Ui_CheckEmployeesWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKEMPLOYEESWINDOW_H
