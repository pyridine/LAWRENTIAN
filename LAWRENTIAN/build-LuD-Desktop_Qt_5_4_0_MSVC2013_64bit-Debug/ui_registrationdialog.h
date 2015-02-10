/********************************************************************************
** Form generated from reading UI file 'registrationdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATIONDIALOG_H
#define UI_REGISTRATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_RegistrationDialog
{
public:
    QLabel *label;

    void setupUi(QDialog *RegistrationDialog)
    {
        if (RegistrationDialog->objectName().isEmpty())
            RegistrationDialog->setObjectName(QStringLiteral("RegistrationDialog"));
        RegistrationDialog->resize(400, 300);
        label = new QLabel(RegistrationDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 47, 13));

        retranslateUi(RegistrationDialog);

        QMetaObject::connectSlotsByName(RegistrationDialog);
    } // setupUi

    void retranslateUi(QDialog *RegistrationDialog)
    {
        RegistrationDialog->setWindowTitle(QApplication::translate("RegistrationDialog", "Dialog", 0));
        label->setText(QApplication::translate("RegistrationDialog", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class RegistrationDialog: public Ui_RegistrationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATIONDIALOG_H
