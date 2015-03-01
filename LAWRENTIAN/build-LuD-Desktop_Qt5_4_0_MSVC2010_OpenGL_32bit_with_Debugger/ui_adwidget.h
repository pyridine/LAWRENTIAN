/********************************************************************************
** Form generated from reading UI file 'adwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADWIDGET_H
#define UI_ADWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_adWidget
{
public:

    void setupUi(QWidget *adWidget)
    {
        if (adWidget->objectName().isEmpty())
            adWidget->setObjectName(QStringLiteral("adWidget"));
        adWidget->resize(1100, 600);

        retranslateUi(adWidget);

        QMetaObject::connectSlotsByName(adWidget);
    } // setupUi

    void retranslateUi(QWidget *adWidget)
    {
        adWidget->setWindowTitle(QApplication::translate("adWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class adWidget: public Ui_adWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADWIDGET_H
