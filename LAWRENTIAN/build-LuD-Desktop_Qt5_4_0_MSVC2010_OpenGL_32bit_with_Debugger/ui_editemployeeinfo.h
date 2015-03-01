/********************************************************************************
** Form generated from reading UI file 'editemployeeinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITEMPLOYEEINFO_H
#define UI_EDITEMPLOYEEINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditEmployeeInfo
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *nameComboBox;
    QLineEdit *luidTextField;
    QLineEdit *titleTextField;
    QLineEdit *emailTextField;
    QLineEdit *phoneTextField;
    QComboBox *approvedComboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_7;
    QComboBox *probationComboBox;
    QLabel *label_8;
    QDateEdit *probationStartDate;

    void setupUi(QDialog *EditEmployeeInfo)
    {
        if (EditEmployeeInfo->objectName().isEmpty())
            EditEmployeeInfo->setObjectName(QStringLiteral("EditEmployeeInfo"));
        EditEmployeeInfo->resize(450, 348);
        label = new QLabel(EditEmployeeInfo);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 60, 62, 16));
        label_2 = new QLabel(EditEmployeeInfo);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 20, 62, 16));
        label_3 = new QLabel(EditEmployeeInfo);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 100, 41, 16));
        label_4 = new QLabel(EditEmployeeInfo);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 140, 51, 16));
        label_5 = new QLabel(EditEmployeeInfo);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 180, 62, 16));
        label_6 = new QLabel(EditEmployeeInfo);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 220, 71, 16));
        nameComboBox = new QComboBox(EditEmployeeInfo);
        nameComboBox->setObjectName(QStringLiteral("nameComboBox"));
        nameComboBox->setGeometry(QRect(90, 20, 271, 26));
        luidTextField = new QLineEdit(EditEmployeeInfo);
        luidTextField->setObjectName(QStringLiteral("luidTextField"));
        luidTextField->setGeometry(QRect(100, 60, 231, 21));
        titleTextField = new QLineEdit(EditEmployeeInfo);
        titleTextField->setObjectName(QStringLiteral("titleTextField"));
        titleTextField->setGeometry(QRect(100, 100, 231, 21));
        emailTextField = new QLineEdit(EditEmployeeInfo);
        emailTextField->setObjectName(QStringLiteral("emailTextField"));
        emailTextField->setGeometry(QRect(100, 140, 231, 21));
        phoneTextField = new QLineEdit(EditEmployeeInfo);
        phoneTextField->setObjectName(QStringLiteral("phoneTextField"));
        phoneTextField->setGeometry(QRect(100, 180, 231, 21));
        approvedComboBox = new QComboBox(EditEmployeeInfo);
        approvedComboBox->setObjectName(QStringLiteral("approvedComboBox"));
        approvedComboBox->setGeometry(QRect(100, 220, 81, 26));
        pushButton = new QPushButton(EditEmployeeInfo);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(0, 310, 121, 32));
        pushButton->setAutoDefault(false);
        pushButton_2 = new QPushButton(EditEmployeeInfo);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(330, 310, 114, 32));
        pushButton_2->setAutoDefault(true);
        label_7 = new QLabel(EditEmployeeInfo);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 260, 71, 16));
        probationComboBox = new QComboBox(EditEmployeeInfo);
        probationComboBox->setObjectName(QStringLiteral("probationComboBox"));
        probationComboBox->setGeometry(QRect(100, 260, 81, 26));
        label_8 = new QLabel(EditEmployeeInfo);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(200, 250, 71, 31));
        probationStartDate = new QDateEdit(EditEmployeeInfo);
        probationStartDate->setObjectName(QStringLiteral("probationStartDate"));
        probationStartDate->setGeometry(QRect(290, 260, 110, 24));

        retranslateUi(EditEmployeeInfo);

        QMetaObject::connectSlotsByName(EditEmployeeInfo);
    } // setupUi

    void retranslateUi(QDialog *EditEmployeeInfo)
    {
        EditEmployeeInfo->setWindowTitle(QApplication::translate("EditEmployeeInfo", "Dialog", 0));
        label->setText(QApplication::translate("EditEmployeeInfo", "LU ID:", 0));
        label_2->setText(QApplication::translate("EditEmployeeInfo", "Name:", 0));
        label_3->setText(QApplication::translate("EditEmployeeInfo", "Title:", 0));
        label_4->setText(QApplication::translate("EditEmployeeInfo", "Email:", 0));
        label_5->setText(QApplication::translate("EditEmployeeInfo", "Phone:", 0));
        label_6->setText(QApplication::translate("EditEmployeeInfo", "Approved:", 0));
        pushButton->setText(QApplication::translate("EditEmployeeInfo", "Save Changes", 0));
        pushButton_2->setText(QApplication::translate("EditEmployeeInfo", "Done", 0));
        label_7->setText(QApplication::translate("EditEmployeeInfo", "Probation:", 0));
        label_8->setText(QApplication::translate("EditEmployeeInfo", "Start Date:", 0));
    } // retranslateUi

};

namespace Ui {
    class EditEmployeeInfo: public Ui_EditEmployeeInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITEMPLOYEEINFO_H
