/********************************************************************************
** Form generated from reading UI file 'circulationwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CIRCULATIONWIDGET_H
#define UI_CIRCULATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_circulationWidget
{
public:

    void setupUi(QWidget *circulationWidget)
    {
        if (circulationWidget->objectName().isEmpty())
            circulationWidget->setObjectName(QStringLiteral("circulationWidget"));
        circulationWidget->resize(1100, 600);

        retranslateUi(circulationWidget);

        QMetaObject::connectSlotsByName(circulationWidget);
    } // setupUi

    void retranslateUi(QWidget *circulationWidget)
    {
        circulationWidget->setWindowTitle(QApplication::translate("circulationWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class circulationWidget: public Ui_circulationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CIRCULATIONWIDGET_H
