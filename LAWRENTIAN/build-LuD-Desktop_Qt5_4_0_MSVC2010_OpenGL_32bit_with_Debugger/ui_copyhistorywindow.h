/********************************************************************************
** Form generated from reading UI file 'copyhistorywindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYHISTORYWINDOW_H
#define UI_COPYHISTORYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_CopyHistoryWindow
{
public:
    QPushButton *cancel_pushButton;
    QPushButton *download_pushButton;
    QTableWidget *copyHistory_tableWidget;

    void setupUi(QDialog *CopyHistoryWindow)
    {
        if (CopyHistoryWindow->objectName().isEmpty())
            CopyHistoryWindow->setObjectName(QStringLiteral("CopyHistoryWindow"));
        CopyHistoryWindow->resize(404, 297);
        cancel_pushButton = new QPushButton(CopyHistoryWindow);
        cancel_pushButton->setObjectName(QStringLiteral("cancel_pushButton"));
        cancel_pushButton->setGeometry(QRect(274, 270, 121, 23));
        download_pushButton = new QPushButton(CopyHistoryWindow);
        download_pushButton->setObjectName(QStringLiteral("download_pushButton"));
        download_pushButton->setGeometry(QRect(10, 270, 111, 23));
        copyHistory_tableWidget = new QTableWidget(CopyHistoryWindow);
        copyHistory_tableWidget->setObjectName(QStringLiteral("copyHistory_tableWidget"));
        copyHistory_tableWidget->setGeometry(QRect(10, 10, 381, 241));

        retranslateUi(CopyHistoryWindow);

        QMetaObject::connectSlotsByName(CopyHistoryWindow);
    } // setupUi

    void retranslateUi(QDialog *CopyHistoryWindow)
    {
        CopyHistoryWindow->setWindowTitle(QApplication::translate("CopyHistoryWindow", "Dialog", 0));
        cancel_pushButton->setText(QApplication::translate("CopyHistoryWindow", "Cancel", 0));
        download_pushButton->setText(QApplication::translate("CopyHistoryWindow", "Download", 0));
    } // retranslateUi

};

namespace Ui {
    class CopyHistoryWindow: public Ui_CopyHistoryWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYHISTORYWINDOW_H
