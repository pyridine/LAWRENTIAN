/********************************************************************************
** Form generated from reading UI file 'addlocationdialogue.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDLOCATIONDIALOGUE_H
#define UI_ADDLOCATIONDIALOGUE_H

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

class Ui_AddLocationDialogue
{
public:
    QPushButton *AddLocButton;
    QPushButton *cancelButton;
    QLineEdit *nameField;
    QLabel *label;

    void setupUi(QDialog *AddLocationDialogue)
    {
        if (AddLocationDialogue->objectName().isEmpty())
            AddLocationDialogue->setObjectName(QStringLiteral("AddLocationDialogue"));
        AddLocationDialogue->resize(260, 99);
        AddLocButton = new QPushButton(AddLocationDialogue);
        AddLocButton->setObjectName(QStringLiteral("AddLocButton"));
        AddLocButton->setGeometry(QRect(40, 60, 80, 21));
        cancelButton = new QPushButton(AddLocationDialogue);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(130, 60, 80, 21));
        nameField = new QLineEdit(AddLocationDialogue);
        nameField->setObjectName(QStringLiteral("nameField"));
        nameField->setGeometry(QRect(100, 20, 113, 21));
        label = new QLabel(AddLocationDialogue);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 91, 16));

        retranslateUi(AddLocationDialogue);

        QMetaObject::connectSlotsByName(AddLocationDialogue);
    } // setupUi

    void retranslateUi(QDialog *AddLocationDialogue)
    {
        AddLocationDialogue->setWindowTitle(QApplication::translate("AddLocationDialogue", "Dialog", 0));
        AddLocButton->setText(QApplication::translate("AddLocationDialogue", "Add Location", 0));
        cancelButton->setText(QApplication::translate("AddLocationDialogue", "Cancel", 0));
        label->setText(QApplication::translate("AddLocationDialogue", "Location Name:", 0));
    } // retranslateUi

};

namespace Ui {
    class AddLocationDialogue: public Ui_AddLocationDialogue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDLOCATIONDIALOGUE_H
