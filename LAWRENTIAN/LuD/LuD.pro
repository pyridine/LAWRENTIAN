#-------------------------------------------------
#
# Project created by QtCreator 2015-02-01T20:41:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LuD
TEMPLATE = app


SOURCES += main.cpp\
        registrationwindow.cpp \
    employee.cpp \
    checkemployeeswindow.cpp \
    permissions.cpp \
    circulation.cpp

HEADERS  += registrationwindow.h \
    employee.h \
    checkemployeeswindow.h \
    PermissionDefinitions.h \
    permissions.h \
    circulation.h

FORMS    += registrationwindow.ui \
    checkemployeeswindow.ui
CONFIG   += console
