/********************************************************************************
** Form generated from reading UI file 'employeeswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYEESWIDGET_H
#define UI_EMPLOYEESWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_employeesWidget
{
public:
    QTableWidget *employeeTable;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *approveRegButton;

    void setupUi(QWidget *employeesWidget)
    {
        if (employeesWidget->objectName().isEmpty())
            employeesWidget->setObjectName(QStringLiteral("employeesWidget"));
        employeesWidget->resize(800, 600);
        employeeTable = new QTableWidget(employeesWidget);
        employeeTable->setObjectName(QStringLiteral("employeeTable"));
        employeeTable->setGeometry(QRect(20, 80, 1000, 550));
        label = new QLabel(employeesWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 40, 111, 16));
        lineEdit = new QLineEdit(employeesWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(140, 40, 261, 21));
        approveRegButton = new QPushButton(employeesWidget);
        approveRegButton->setObjectName(QStringLiteral("approveRegButton"));
        approveRegButton->setGeometry(QRect(650, 40, 141, 21));

        retranslateUi(employeesWidget);

        QMetaObject::connectSlotsByName(employeesWidget);
    } // setupUi

    void retranslateUi(QWidget *employeesWidget)
    {
        employeesWidget->setWindowTitle(QApplication::translate("employeesWidget", "Form", 0));
        label->setText(QApplication::translate("employeesWidget", "Search Employee:", 0));
        approveRegButton->setText(QApplication::translate("employeesWidget", "Approve Registration", 0));
    } // retranslateUi

};

namespace Ui {
    class employeesWidget: public Ui_employeesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYEESWIDGET_H
