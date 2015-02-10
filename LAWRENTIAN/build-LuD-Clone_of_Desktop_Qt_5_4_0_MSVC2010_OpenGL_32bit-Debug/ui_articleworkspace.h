/********************************************************************************
** Form generated from reading UI file 'articleworkspace.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARTICLEWORKSPACE_H
#define UI_ARTICLEWORKSPACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_articleWorkspace
{
public:
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *articleWorkspace)
    {
        if (articleWorkspace->objectName().isEmpty())
            articleWorkspace->setObjectName(QStringLiteral("articleWorkspace"));
        articleWorkspace->resize(1100, 600);
        label = new QLabel(articleWorkspace);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 201, 41));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        pushButton = new QPushButton(articleWorkspace);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(950, 510, 141, 32));

        retranslateUi(articleWorkspace);

        QMetaObject::connectSlotsByName(articleWorkspace);
    } // setupUi

    void retranslateUi(QWidget *articleWorkspace)
    {
        articleWorkspace->setWindowTitle(QApplication::translate("articleWorkspace", "Form", 0));
        label->setText(QApplication::translate("articleWorkspace", "Article Workspaces:", 0));
        pushButton->setText(QApplication::translate("articleWorkspace", "Add Workspace", 0));
    } // retranslateUi

};

namespace Ui {
    class articleWorkspace: public Ui_articleWorkspace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARTICLEWORKSPACE_H
