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
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

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
    QPushButton *chooseFile_pushButton;
    QLineEdit *articleFileTextField;
    QPushButton *submit_pushButton;
    QLabel *label_7;
    QDateEdit *issueDateEdit;
    QPushButton *addImage_pushButton;
    QLabel *label_8;
    QScrollArea *img_scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *delete_pushButton;
    QPushButton *deleteAWS_pushButton;
    QPushButton *copyHistory_pushButton;

    void setupUi(QDialog *newArticleWorkspaceWindow)
    {
        if (newArticleWorkspaceWindow->objectName().isEmpty())
            newArticleWorkspaceWindow->setObjectName(QStringLiteral("newArticleWorkspaceWindow"));
        newArticleWorkspaceWindow->resize(616, 526);
        label = new QLabel(newArticleWorkspaceWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 20, 61, 16));
        label_2 = new QLabel(newArticleWorkspaceWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 60, 61, 16));
        label_3 = new QLabel(newArticleWorkspaceWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 270, 41, 16));
        articleTitleTextField = new QLineEdit(newArticleWorkspaceWindow);
        articleTitleTextField->setObjectName(QStringLiteral("articleTitleTextField"));
        articleTitleTextField->setGeometry(QRect(120, 20, 471, 21));
        label_4 = new QLabel(newArticleWorkspaceWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(70, 230, 41, 16));
        descriptionTextField = new QTextEdit(newArticleWorkspaceWindow);
        descriptionTextField->setObjectName(QStringLiteral("descriptionTextField"));
        descriptionTextField->setGeometry(QRect(120, 60, 471, 151));
        label_5 = new QLabel(newArticleWorkspaceWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(40, 310, 71, 16));
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
        label_6->setGeometry(QRect(60, 350, 51, 16));
        chooseFile_pushButton = new QPushButton(newArticleWorkspaceWindow);
        chooseFile_pushButton->setObjectName(QStringLiteral("chooseFile_pushButton"));
        chooseFile_pushButton->setGeometry(QRect(490, 351, 121, 21));
        chooseFile_pushButton->setAutoDefault(false);
        articleFileTextField = new QLineEdit(newArticleWorkspaceWindow);
        articleFileTextField->setObjectName(QStringLiteral("articleFileTextField"));
        articleFileTextField->setGeometry(QRect(120, 350, 361, 21));
        submit_pushButton = new QPushButton(newArticleWorkspaceWindow);
        submit_pushButton->setObjectName(QStringLiteral("submit_pushButton"));
        submit_pushButton->setGeometry(QRect(490, 490, 121, 32));
        label_7 = new QLabel(newArticleWorkspaceWindow);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(50, 500, 61, 16));
        issueDateEdit = new QDateEdit(newArticleWorkspaceWindow);
        issueDateEdit->setObjectName(QStringLiteral("issueDateEdit"));
        issueDateEdit->setGeometry(QRect(120, 500, 110, 24));
        addImage_pushButton = new QPushButton(newArticleWorkspaceWindow);
        addImage_pushButton->setObjectName(QStringLiteral("addImage_pushButton"));
        addImage_pushButton->setGeometry(QRect(520, 400, 71, 51));
        label_8 = new QLabel(newArticleWorkspaceWindow);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(70, 420, 41, 16));
        img_scrollArea = new QScrollArea(newArticleWorkspaceWindow);
        img_scrollArea->setObjectName(QStringLiteral("img_scrollArea"));
        img_scrollArea->setGeometry(QRect(120, 380, 361, 101));
        img_scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 359, 99));
        img_scrollArea->setWidget(scrollAreaWidgetContents);
        delete_pushButton = new QPushButton(newArticleWorkspaceWindow);
        delete_pushButton->setObjectName(QStringLiteral("delete_pushButton"));
        delete_pushButton->setGeometry(QRect(300, 490, 131, 31));
        deleteAWS_pushButton = new QPushButton(newArticleWorkspaceWindow);
        deleteAWS_pushButton->setObjectName(QStringLiteral("deleteAWS_pushButton"));
        deleteAWS_pushButton->setGeometry(QRect(490, 220, 121, 31));
        copyHistory_pushButton = new QPushButton(newArticleWorkspaceWindow);
        copyHistory_pushButton->setObjectName(QStringLiteral("copyHistory_pushButton"));
        copyHistory_pushButton->setGeometry(QRect(490, 280, 121, 31));

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
        chooseFile_pushButton->setText(QApplication::translate("newArticleWorkspaceWindow", "Choose File...", 0));
        submit_pushButton->setText(QApplication::translate("newArticleWorkspaceWindow", "Submit", 0));
        label_7->setText(QApplication::translate("newArticleWorkspaceWindow", "Issue Date:", 0));
        addImage_pushButton->setText(QApplication::translate("newArticleWorkspaceWindow", "Add Image", 0));
        label_8->setText(QApplication::translate("newArticleWorkspaceWindow", "Images:", 0));
        delete_pushButton->setText(QApplication::translate("newArticleWorkspaceWindow", "Delete Image", 0));
        deleteAWS_pushButton->setText(QApplication::translate("newArticleWorkspaceWindow", "Delete Workspace", 0));
        copyHistory_pushButton->setText(QApplication::translate("newArticleWorkspaceWindow", "Copy History", 0));
    } // retranslateUi

};

namespace Ui {
    class newArticleWorkspaceWindow: public Ui_newArticleWorkspaceWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWARTICLEWORKSPACEWINDOW_H
