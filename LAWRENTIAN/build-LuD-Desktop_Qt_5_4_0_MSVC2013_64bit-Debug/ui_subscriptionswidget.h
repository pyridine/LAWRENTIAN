/********************************************************************************
** Form generated from reading UI file 'subscriptionswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBSCRIPTIONSWIDGET_H
#define UI_SUBSCRIPTIONSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_subscriptionsWidget
{
public:

    void setupUi(QWidget *subscriptionsWidget)
    {
        if (subscriptionsWidget->objectName().isEmpty())
            subscriptionsWidget->setObjectName(QStringLiteral("subscriptionsWidget"));
        subscriptionsWidget->resize(1100, 600);

        retranslateUi(subscriptionsWidget);

        QMetaObject::connectSlotsByName(subscriptionsWidget);
    } // setupUi

    void retranslateUi(QWidget *subscriptionsWidget)
    {
        subscriptionsWidget->setWindowTitle(QApplication::translate("subscriptionsWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class subscriptionsWidget: public Ui_subscriptionsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBSCRIPTIONSWIDGET_H
