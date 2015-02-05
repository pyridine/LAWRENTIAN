/********************************************************************************
** Form generated from reading UI file 'registrationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATIONWINDOW_H
#define UI_REGISTRATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistrationWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QFrame *line;
    QLineEdit *emailTextField;
    QLineEdit *nameTextField;
    QLineEdit *luIdTextField;
    QLineEdit *phoneTextField;
    QLabel *label_5;
    QLineEdit *usernameTextField;
    QLabel *label_6;
    QLineEdit *passwordTextField;
    QLabel *label_7;
    QLineEdit *confirmPasswordTextField;
    QPushButton *submitButton;
    QGraphicsView *idPicture;
    QLabel *passwordErrorLabel;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RegistrationWindow)
    {
        if (RegistrationWindow->objectName().isEmpty())
            RegistrationWindow->setObjectName(QStringLiteral("RegistrationWindow"));
        RegistrationWindow->resize(569, 403);
        centralWidget = new QWidget(RegistrationWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 20, 41, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(90, 60, 41, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(90, 100, 41, 16));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(90, 140, 41, 16));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(120, 170, 331, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        emailTextField = new QLineEdit(centralWidget);
        emailTextField->setObjectName(QStringLiteral("emailTextField"));
        emailTextField->setGeometry(QRect(160, 100, 231, 21));
        nameTextField = new QLineEdit(centralWidget);
        nameTextField->setObjectName(QStringLiteral("nameTextField"));
        nameTextField->setGeometry(QRect(160, 20, 231, 21));
        luIdTextField = new QLineEdit(centralWidget);
        luIdTextField->setObjectName(QStringLiteral("luIdTextField"));
        luIdTextField->setGeometry(QRect(160, 60, 231, 21));
        phoneTextField = new QLineEdit(centralWidget);
        phoneTextField->setObjectName(QStringLiteral("phoneTextField"));
        phoneTextField->setGeometry(QRect(160, 140, 231, 21));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(70, 200, 71, 16));
        usernameTextField = new QLineEdit(centralWidget);
        usernameTextField->setObjectName(QStringLiteral("usernameTextField"));
        usernameTextField->setGeometry(QRect(160, 200, 231, 21));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(70, 240, 62, 16));
        passwordTextField = new QLineEdit(centralWidget);
        passwordTextField->setObjectName(QStringLiteral("passwordTextField"));
        passwordTextField->setGeometry(QRect(160, 240, 231, 21));
        passwordTextField->setEchoMode(QLineEdit::Password);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 280, 121, 16));
        confirmPasswordTextField = new QLineEdit(centralWidget);
        confirmPasswordTextField->setObjectName(QStringLiteral("confirmPasswordTextField"));
        confirmPasswordTextField->setGeometry(QRect(160, 280, 231, 21));
        confirmPasswordTextField->setEchoMode(QLineEdit::Password);
        submitButton = new QPushButton(centralWidget);
        submitButton->setObjectName(QStringLiteral("submitButton"));
        submitButton->setGeometry(QRect(440, 310, 114, 32));
        submitButton->setDefault(true);
        idPicture = new QGraphicsView(centralWidget);
        idPicture->setObjectName(QStringLiteral("idPicture"));
        idPicture->setGeometry(QRect(410, 20, 141, 141));
        passwordErrorLabel = new QLabel(centralWidget);
        passwordErrorLabel->setObjectName(QStringLiteral("passwordErrorLabel"));
        passwordErrorLabel->setGeometry(QRect(410, 240, 151, 16));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 310, 141, 32));
        RegistrationWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RegistrationWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 569, 22));
        RegistrationWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RegistrationWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        RegistrationWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RegistrationWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(true);
        RegistrationWindow->setStatusBar(statusBar);

        retranslateUi(RegistrationWindow);

        QMetaObject::connectSlotsByName(RegistrationWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RegistrationWindow)
    {
        RegistrationWindow->setWindowTitle(QApplication::translate("RegistrationWindow", "Registration", 0));
        label->setText(QApplication::translate("RegistrationWindow", "Name:", 0));
        label_2->setText(QApplication::translate("RegistrationWindow", "LU ID#:", 0));
        label_3->setText(QApplication::translate("RegistrationWindow", "Email:", 0));
        label_4->setText(QApplication::translate("RegistrationWindow", "Phone:", 0));
        emailTextField->setPlaceholderText(QApplication::translate("RegistrationWindow", "Enter Email...", 0));
#ifndef QT_NO_ACCESSIBILITY
        nameTextField->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        nameTextField->setPlaceholderText(QApplication::translate("RegistrationWindow", "Enter Name...", 0));
        luIdTextField->setPlaceholderText(QApplication::translate("RegistrationWindow", "Enter LU ID#...", 0));
        phoneTextField->setPlaceholderText(QApplication::translate("RegistrationWindow", "Enter Phone#...", 0));
        label_5->setText(QApplication::translate("RegistrationWindow", "Username:", 0));
        usernameTextField->setPlaceholderText(QApplication::translate("RegistrationWindow", "Enter Username...", 0));
        label_6->setText(QApplication::translate("RegistrationWindow", "Password:", 0));
        passwordTextField->setInputMask(QString());
        passwordTextField->setPlaceholderText(QApplication::translate("RegistrationWindow", "Enter Password...", 0));
        label_7->setText(QApplication::translate("RegistrationWindow", "Confirm Password:", 0));
        confirmPasswordTextField->setPlaceholderText(QApplication::translate("RegistrationWindow", "Confirm Password...", 0));
        submitButton->setText(QApplication::translate("RegistrationWindow", "Submit", 0));
        passwordErrorLabel->setText(QApplication::translate("RegistrationWindow", "Password Error", 0));
        pushButton->setText(QApplication::translate("RegistrationWindow", "Check Employees", 0));
    } // retranslateUi

};

namespace Ui {
    class RegistrationWindow: public Ui_RegistrationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATIONWINDOW_H
