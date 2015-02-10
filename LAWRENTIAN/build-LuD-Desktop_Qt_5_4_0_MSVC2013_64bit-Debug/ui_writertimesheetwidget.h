/********************************************************************************
** Form generated from reading UI file 'writertimesheetwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WRITERTIMESHEETWIDGET_H
#define UI_WRITERTIMESHEETWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_writerTimesheetWidget
{
public:

    void setupUi(QWidget *writerTimesheetWidget)
    {
        if (writerTimesheetWidget->objectName().isEmpty())
            writerTimesheetWidget->setObjectName(QStringLiteral("writerTimesheetWidget"));
        writerTimesheetWidget->resize(1100, 600);

        retranslateUi(writerTimesheetWidget);

        QMetaObject::connectSlotsByName(writerTimesheetWidget);
    } // setupUi

    void retranslateUi(QWidget *writerTimesheetWidget)
    {
        writerTimesheetWidget->setWindowTitle(QApplication::translate("writerTimesheetWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class writerTimesheetWidget: public Ui_writerTimesheetWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WRITERTIMESHEETWIDGET_H
