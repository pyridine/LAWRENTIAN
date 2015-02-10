/********************************************************************************
** Form generated from reading UI file 'profilewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILEWIDGET_H
#define UI_PROFILEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_profileWidget
{
public:
    QLabel *welcomeLabel;
    QPushButton *logOutButton;
    QLabel *titleLabel;

    void setupUi(QWidget *profileWidget)
    {
        if (profileWidget->objectName().isEmpty())
            profileWidget->setObjectName(QStringLiteral("profileWidget"));
        profileWidget->resize(1100, 600);
        welcomeLabel = new QLabel(profileWidget);
        welcomeLabel->setObjectName(QStringLiteral("welcomeLabel"));
        welcomeLabel->setGeometry(QRect(20, 20, 621, 31));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        welcomeLabel->setFont(font);
        logOutButton = new QPushButton(profileWidget);
        logOutButton->setObjectName(QStringLiteral("logOutButton"));
        logOutButton->setGeometry(QRect(20, 130, 231, 31));
        titleLabel = new QLabel(profileWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        titleLabel->setGeometry(QRect(20, 70, 621, 31));
        titleLabel->setFont(font);

        retranslateUi(profileWidget);

        QMetaObject::connectSlotsByName(profileWidget);
    } // setupUi

    void retranslateUi(QWidget *profileWidget)
    {
        profileWidget->setWindowTitle(QApplication::translate("profileWidget", "Form", 0));
        welcomeLabel->setText(QApplication::translate("profileWidget", "Welcome, ERROR! WHAT THE FUCK WENT WRONG", 0));
        logOutButton->setText(QApplication::translate("profileWidget", "Log out :(", 0));
        titleLabel->setText(QApplication::translate("profileWidget", "You are a ERROR! WHAT THE FUCK WENT WRONG!?!??!", 0));
    } // retranslateUi

};

namespace Ui {
    class profileWidget: public Ui_profileWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILEWIDGET_H
