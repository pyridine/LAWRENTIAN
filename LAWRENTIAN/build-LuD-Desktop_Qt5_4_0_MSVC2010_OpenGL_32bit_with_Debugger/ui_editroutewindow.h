/********************************************************************************
** Form generated from reading UI file 'editroutewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITROUTEWINDOW_H
#define UI_EDITROUTEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditRouteWindow
{
public:
    QPushButton *cancelButton;
    QPushButton *applyButton;
    QLabel *routeLabel;
    QLabel *label_2;
    QPushButton *upButton;
    QPushButton *downButton;
    QLabel *label_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *addPointButton;
    QPushButton *removePointButton;
    QListWidget *locationList;
    QListWidget *routePointList;
    QPushButton *dropRouteWindow;

    void setupUi(QDialog *EditRouteWindow)
    {
        if (EditRouteWindow->objectName().isEmpty())
            EditRouteWindow->setObjectName(QStringLiteral("EditRouteWindow"));
        EditRouteWindow->resize(441, 422);
        cancelButton = new QPushButton(EditRouteWindow);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(220, 390, 80, 21));
        applyButton = new QPushButton(EditRouteWindow);
        applyButton->setObjectName(QStringLiteral("applyButton"));
        applyButton->setGeometry(QRect(130, 390, 80, 21));
        routeLabel = new QLabel(EditRouteWindow);
        routeLabel->setObjectName(QStringLiteral("routeLabel"));
        routeLabel->setGeometry(QRect(20, 12, 121, 21));
        label_2 = new QLabel(EditRouteWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(240, 13, 47, 20));
        upButton = new QPushButton(EditRouteWindow);
        upButton->setObjectName(QStringLiteral("upButton"));
        upButton->setGeometry(QRect(200, 150, 31, 21));
        downButton = new QPushButton(EditRouteWindow);
        downButton->setObjectName(QStringLiteral("downButton"));
        downButton->setGeometry(QRect(200, 180, 31, 21));
        label_3 = new QLabel(EditRouteWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(200, 120, 47, 13));
        pushButton_5 = new QPushButton(EditRouteWindow);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(240, 350, 80, 21));
        pushButton_6 = new QPushButton(EditRouteWindow);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(330, 350, 91, 21));
        addPointButton = new QPushButton(EditRouteWindow);
        addPointButton->setObjectName(QStringLiteral("addPointButton"));
        addPointButton->setGeometry(QRect(20, 350, 80, 21));
        removePointButton = new QPushButton(EditRouteWindow);
        removePointButton->setObjectName(QStringLiteral("removePointButton"));
        removePointButton->setGeometry(QRect(110, 350, 80, 21));
        locationList = new QListWidget(EditRouteWindow);
        locationList->setObjectName(QStringLiteral("locationList"));
        locationList->setGeometry(QRect(240, 40, 181, 301));
        routePointList = new QListWidget(EditRouteWindow);
        routePointList->setObjectName(QStringLiteral("routePointList"));
        routePointList->setGeometry(QRect(10, 40, 181, 301));
        dropRouteWindow = new QPushButton(EditRouteWindow);
        dropRouteWindow->setObjectName(QStringLiteral("dropRouteWindow"));
        dropRouteWindow->setGeometry(QRect(340, 390, 80, 21));

        retranslateUi(EditRouteWindow);

        QMetaObject::connectSlotsByName(EditRouteWindow);
    } // setupUi

    void retranslateUi(QDialog *EditRouteWindow)
    {
        EditRouteWindow->setWindowTitle(QApplication::translate("EditRouteWindow", "Dialog", 0));
        cancelButton->setText(QApplication::translate("EditRouteWindow", "Cancel", 0));
        applyButton->setText(QApplication::translate("EditRouteWindow", "Apply", 0));
        routeLabel->setText(QApplication::translate("EditRouteWindow", "Route # ", 0));
        label_2->setText(QApplication::translate("EditRouteWindow", "Locations", 0));
        upButton->setText(QApplication::translate("EditRouteWindow", "\342\206\221", 0));
        downButton->setText(QApplication::translate("EditRouteWindow", "\342\206\223", 0));
        label_3->setText(QApplication::translate("EditRouteWindow", "Order", 0));
        pushButton_5->setText(QApplication::translate("EditRouteWindow", "?Add Location?", 0));
        pushButton_6->setText(QApplication::translate("EditRouteWindow", "?Edit Location?", 0));
        addPointButton->setText(QApplication::translate("EditRouteWindow", "Add Point", 0));
        removePointButton->setText(QApplication::translate("EditRouteWindow", "Remove Point", 0));
        dropRouteWindow->setText(QApplication::translate("EditRouteWindow", "Drop Route", 0));
    } // retranslateUi

};

namespace Ui {
    class EditRouteWindow: public Ui_EditRouteWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITROUTEWINDOW_H
