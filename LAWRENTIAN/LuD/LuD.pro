#-------------------------------------------------
#
# Project created by QtCreator 2015-02-01T20:41:48
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LuD
TEMPLATE = app


SOURCES += main.cpp\
        registrationwindow.cpp \
    employee.cpp \
    checkemployeeswindow.cpp \
    permissions.cpp \
    circulation.cpp \
    remotedbconnection.cpp \
    registrationwindowdbcontroller.cpp \
    client.cpp \
    loginwindow.cpp \
    loginwindowdbcontroller.cpp \
    logincredentials.cpp \
    alert.cpp \
    ad.cpp \
    archive.cpp \
    article.cpp \
    editortimesheet.cpp \
    idea.cpp \
    registrationdialog.cpp \
    subscription.cpp \
    writertimesheet.cpp \
    adwidget.cpp \
    articleworkspace.cpp \
    circulationwidget.cpp \
    editortimesheetwidget.cpp \
    employeeswidget.cpp \
    mainwindow.cpp \
    newarticleworkspacewindow.cpp \
    profilewidget.cpp \
    subscriptionswidget.cpp \
    writertimesheetwidget.cpp

HEADERS  += registrationwindow.h \
    employee.h \
    checkemployeeswindow.h \
    PermissionDefinitions.h \
    permissions.h \
    circulation.h \
    remotedbconnection.h \
    registrationwindowdbcontroller.h \
    client.h \
    loginwindow.h \
    loginwindowdbcontroller.h \
    logincredentials.h \
    alert.h \
    ad.h \
    archive.h \
    article.h \
    editortimesheet.h \
    idea.h \
    registrationdialog.h \
    subscription.h \
    writertimesheet.h \
    titledefinitions.h \
    adwidget.h \
    articleworkspace.h \
    circulationwidget.h \
    editortimesheetwidget.h \
    employeeswidget.h \
    mainwindow.h \
    newarticleworkspacewindow.h \
    profilewidget.h \
    subscriptionswidget.h \
    writertimesheetwidget.h


FORMS    += registrationwindow.ui \
    checkemployeeswindow.ui \
    loginwindow.ui \
    registrationdialog.ui \
    adwidget.ui \
    articleworkspace.ui \
    circulationwidget.ui \
    editortimesheetwidget.ui \
    employeeswidget.ui \
    mainwindow.ui \
    newarticleworkspacewindow.ui \
    profilewidget.ui \
    subscriptionswidget.ui \
    writertimesheetwidget.ui
CONFIG   += console
CONFIG   += C++11

DISTFILES += \
    libmysql.dll \
    LuD.pro.user
