/********************************************************************************
** Form generated from reading UI file 'newarticleworkspacewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWARTICLEWORKSPACEWINDOW_H
#define UI_NEWARTICLEWORKSPACEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_newArticleWorkspaceWindow
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *articleTitleTextField;
    QLabel *label_4;
    QTextEdit *descriptionTextField;
    QLabel *label_5;
    QComboBox *sectionComboBox;
    QComboBox *writerComboBox;
    QComboBox *photographerComboBox;
    QLabel *label_6;
    QPushButton *pushButton;
    QLineEdit *articleFileTextField;
    QPushButton *pushButton_2;
    QLabel *label_7;
    QDateEdit *issueDateEdit;

    void setupUi(QDialog *newArticleWorkspaceWindow)
    {
        if (newArticleWorkspaceWindow->objectName().isEmpty())
            newArticleWorkspaceWindow->setObjectName(QStringLiteral("newArticleWorkspaceWindow"));
        newArticleWorkspaceWindow->resize(616, 435);
        label = new QLabel(newArticleWorkspaceWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 91, 16));
        label_2 = new QLabel(newArticleWorkspaceWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 60, 81, 16));
        label_3 = new QLabel(newArticleWorkspaceWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 270, 51, 16));
        articleTitleTextField = new QLineEdit(newArticleWorkspaceWindow);
        articleTitleTextField->setObjectName(QStringLiteral("articleTitleTextField"));
        articleTitleTextField->setGeometry(QRect(120, 20, 471, 21));
        label_4 = new QLabel(newArticleWorkspaceWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(60, 230, 51, 16));
        descriptionTextField = new QTextEdit(newArticleWorkspaceWindow);
        descriptionTextField->setObjectName(QStringLiteral("descriptionTextField"));
        descriptionTextField->setGeometry(QRect(120, 60, 471, 151));
        label_5 = new QLabel(newArticleWorkspaceWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 310, 91, 16));
        sectionComboBox = new QComboBox(newArticleWorkspaceWindow);
        sectionComboBox->setObjectName(QStringLiteral("sectionComboBox"));
        sectionComboBox->setGeometry(QRect(120, 230, 201, 26));
        writerComboBox = new QComboBox(newArticleWorkspaceWindow);
        writerComboBox->setObjectName(QStringLiteral("writerComboBox"));
        writerComboBox->setGeometry(QRect(120, 270, 201, 26));
        photographerComboBox = new QComboBox(newArticleWorkspaceWindow);
        photographerComboBox->setObjectName(QStringLiteral("photographerComboBox"));
        photographerComboBox->setGeometry(QRect(120, 310, 201, 26));
        label_6 = new QLabel(newArticleWorkspaceWindow);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 350, 71, 16));
        pushButton = new QPushButton(newArticleWorkspaceWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(490, 350, 121, 32));
        pushButton->setAutoDefault(false);
        articleFileTextField = new QLineEdit(newArticleWorkspaceWindow);
        articleFileTextField->setObjectName(QStringLiteral("articleFileTextField"));
        articleFileTextField->setGeometry(QRect(120, 350, 361, 21));
        pushButton_2 = new QPushButton(newArticleWorkspaceWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(500, 400, 111, 32));
        label_7 = new QLabel(newArticleWorkspaceWindow);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 390, 71, 16));
        issueDateEdit = new QDateEdit(newArticleWorkspaceWindow);
        issueDateEdit->setObjectName(QStringLiteral("issueDateEdit"));
        issueDateEdit->setGeometry(QRect(120, 390, 110, 24));

        retranslateUi(newArticleWorkspaceWindow);

        QMetaObject::connectSlotsByName(newArticleWorkspaceWindow);
    } // setupUi

    void retranslateUi(QDialog *newArticleWorkspaceWindow)
    {
        newArticleWorkspaceWindow->setWindowTitle(QApplication::translate("newArticleWorkspaceWindow", "Edit Article Workspace", 0));
        label->setText(QApplication::translate("newArticleWorkspaceWindow", "Article Title:", 0));
        label_2->setText(QApplication::translate("newArticleWorkspaceWindow", "Description:", 0));
        label_3->setText(QApplication::translate("newArticleWorkspaceWindow", "Writer:", 0));
        articleTitleTextField->setPlaceholderText(QApplication::translate("newArticleWorkspaceWindow", "Add Article Title...", 0));
        label_4->setText(QApplication::translate("newArticleWorkspaceWindow", "Section:", 0));
        label_5->setText(QApplication::translate("newArticleWorkspaceWindow", "Photographer:", 0));
        label_6->setText(QApplication::translate("newArticleWorkspaceWindow", "Article File:", 0));
        pushButton->setText(QApplication::translate("newArticleWorkspaceWindow", "Choose File...", 0));
        pushButton_2->setText(QApplication::translate("newArticleWorkspaceWindow", "Submit", 0));
        label_7->setText(QApplication::translate("newArticleWorkspaceWindow", "Issue Date:", 0));
    } // retranslateUi

};

namespace Ui {
    class newArticleWorkspaceWindow: public Ui_newArticleWorkspaceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWARTICLEWORKSPACEWINDOW_H
