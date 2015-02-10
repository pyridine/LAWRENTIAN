/********************************************************************************
** Form generated from reading UI file 'editortimesheetwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORTIMESHEETWIDGET_H
#define UI_EDITORTIMESHEETWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editorTimesheetWidget
{
public:

    void setupUi(QWidget *editorTimesheetWidget)
    {
        if (editorTimesheetWidget->objectName().isEmpty())
            editorTimesheetWidget->setObjectName(QStringLiteral("editorTimesheetWidget"));
        editorTimesheetWidget->resize(1100, 600);

        retranslateUi(editorTimesheetWidget);

        QMetaObject::connectSlotsByName(editorTimesheetWidget);
    } // setupUi

    void retranslateUi(QWidget *editorTimesheetWidget)
    {
        editorTimesheetWidget->setWindowTitle(QApplication::translate("editorTimesheetWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class editorTimesheetWidget: public Ui_editorTimesheetWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORTIMESHEETWIDGET_H
