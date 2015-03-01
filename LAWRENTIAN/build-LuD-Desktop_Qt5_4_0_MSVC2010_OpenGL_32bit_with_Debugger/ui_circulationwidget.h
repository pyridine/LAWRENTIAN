/********************************************************************************
** Form generated from reading UI file 'circulationwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CIRCULATIONWIDGET_H
#define UI_CIRCULATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_circulationWidget
{
public:
    QLabel *label;
    QLabel *label_2;
    QListWidget *routeSelectorWidget;
    QListWidget *routeDisplayWidget;
    QPushButton *editRouteButton;
    QPushButton *addRouteButton;

    void setupUi(QWidget *circulationWidget)
    {
        if (circulationWidget->objectName().isEmpty())
            circulationWidget->setObjectName(QStringLiteral("circulationWidget"));
        circulationWidget->resize(645, 405);
        label = new QLabel(circulationWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 141, 16));
        label_2 = new QLabel(circulationWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(290, 20, 161, 16));
        routeSelectorWidget = new QListWidget(circulationWidget);
        routeSelectorWidget->setObjectName(QStringLiteral("routeSelectorWidget"));
        routeSelectorWidget->setGeometry(QRect(20, 50, 256, 261));
        routeDisplayWidget = new QListWidget(circulationWidget);
        routeDisplayWidget->setObjectName(QStringLiteral("routeDisplayWidget"));
        routeDisplayWidget->setGeometry(QRect(285, 50, 261, 261));
        editRouteButton = new QPushButton(circulationWidget);
        editRouteButton->setObjectName(QStringLiteral("editRouteButton"));
        editRouteButton->setGeometry(QRect(80, 10, 91, 31));
        addRouteButton = new QPushButton(circulationWidget);
        addRouteButton->setObjectName(QStringLiteral("addRouteButton"));
        addRouteButton->setGeometry(QRect(180, 10, 91, 31));

        retranslateUi(circulationWidget);

        QMetaObject::connectSlotsByName(circulationWidget);
    } // setupUi

    void retranslateUi(QWidget *circulationWidget)
    {
        circulationWidget->setWindowTitle(QApplication::translate("circulationWidget", "Form", 0));
        label->setText(QApplication::translate("circulationWidget", "Route", 0));
        label_2->setText(QApplication::translate("circulationWidget", "Route Definition (first to last)", 0));
        editRouteButton->setText(QApplication::translate("circulationWidget", "Edit Route", 0));
        addRouteButton->setText(QApplication::translate("circulationWidget", "Add Route", 0));
    } // retranslateUi

};

namespace Ui {
    class circulationWidget: public Ui_circulationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CIRCULATIONWIDGET_H
