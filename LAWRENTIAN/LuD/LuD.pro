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
    writertimesheetwidget.cpp \
    employeetabdbcontroller.cpp \
    FileSystem.cpp \
    Sender.cpp

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
    writertimesheetwidget.h \
    employeetabdbcontroller.h \
    FileSystem.h \
    Sender.h


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
    LuD.pro.user \
    FileSystem.ice \
    LuD.pro.user.0f8f2c1 \
    LuD.pro.user.ee9f765

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../$(ICE_SUB_DIR)/lib/ -lice
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../$(ICE_SUB_DIR)/lib/ -liced
else:unix: LIBS += -L$$PWD/../../../$(ICE_SUB_DIR)/lib/ -lice

INCLUDEPATH += $$PWD/../../../$(ICE_SUB_DIR)/include
DEPENDPATH += $$PWD/../../../$(ICE_SUB_DIR)/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../$(ICE_SUB_DIR)/lib/libice.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../$(ICE_SUB_DIR)/lib/libiced.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../$(ICE_SUB_DIR)/lib/ice.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../$(ICE_SUB_DIR)/lib/iced.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../$(ICE_SUB_DIR)/lib/libice.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../$(ICE_SUB_DIR)/lib/ -liceutil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../$(ICE_SUB_DIR)/lib/ -liceutild
else:unix: LIBS += -L$$PWD/../../../$(ICE_SUB_DIR)/lib/ -liceutil

INCLUDEPATH += $$PWD/../../../$(ICE_SUB_DIR)/include
DEPENDPATH += $$PWD/../../../$(ICE_SUB_DIR)/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../$(ICE_SUB_DIR)/lib/libiceutil.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../$(ICE_SUB_DIR)/lib/libiceutild.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../$(ICE_SUB_DIR)/lib/iceutil.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../$(ICE_SUB_DIR)/lib/iceutild.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../$(ICE_SUB_DIR)/lib/libiceutil.a
