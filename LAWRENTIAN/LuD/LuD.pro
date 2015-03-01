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
    remotedbconnection.cpp \
    client.cpp \
    loginwindow.cpp \
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
    FileSystem.cpp \
    Sender.cpp \
    registrationwindowdbc.cpp \
    loginwindowdbc.cpp \
    employeetabledbc.cpp \
    databasecontroller.cpp \
    permissiondef.cpp \
    mainwindowdbc.cpp \
    titledef.cpp \
    locationdef.cpp \
    copyhistorywindow.cpp \
    editroutewindow.cpp \
    circulationwindowdbc.cpp \
    route.cpp \
    newarticleworkspacewindowdbc.cpp \
    articleworkspacedbc.cpp \
    sectiondef.cpp \
    editemployeeinfo.cpp \
    editemployeeinfodbc.cpp \
    editprofilewidget.cpp \
    editprofiledbc.cpp \
    profilewidgetdbc.cpp \
    photopoolwindow.cpp \
    addlocationdialogue.cpp \
    editroutewindowdbc.cpp

HEADERS  += registrationwindow.h \
    employee.h \
    checkemployeeswindow.h \
    permissions.h \
    remotedbconnection.h \
    client.h \
    loginwindow.h \
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
    FileSystem.h \
    Sender.h \
    constants.h \
    registrationwindowdbc.h \
    loginwindowdbc.h \
    employeetabledbc.h \
    databasecontroller.h \
    permissiondef.h \
    mainwindowdbc.h \
    titledef.h \
    locationdef.h \
    copyhistorywindow.h \
    editroutewindow.h \
    circulationwindowdbc.h \
    route.h \
    newarticleworkspacewindowdbc.h \
    articleworkspacedbc.h \
    sectiondef.h \
    editemployeeinfo.h \
    editemployeeinfodbc.h \
    editprofilewidget.h \
    editprofiledbc.h \
    profilewidgetdbc.h \
    photopoolwindow.h \
    addlocationdialogue.h \
    editroutewindowdbc.h


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
    writertimesheetwidget.ui \
    copyhistorywindow.ui \
    editroutewindow.ui \
    editemployeeinfo.ui \
    editprofilewidget.ui \
    photopoolwindow.ui \
    addlocationdialogue.ui

DISTFILES += \
    libmysql.dll \
    LuD.pro.user \
    FileSystem.ice \
    LuD.pro.user.0f8f2c1 \
    LuD.pro.user.ee9f765 \
    LuD.pro.user.47f9476 \
    LuD.pro.user.83fecab \
    LuD.pro.user.IX7944

win32{

CONFIG   += console
CONFIG   += C++11

# Ice libraries. Simply set the environment variable $(ICE_DIR) to Ice parent node and add the bin directory to Ice bin node.
# Example: $(ICE_DIR) = C:/Programs/ZeroC/Ice-3.5.1 and $(PATH) = C:\Programs\ZeroC\Ice-3.5.1\bin;
win32:CONFIG(release, debug|release): LIBS += -L$(ICE_DIR)/lib/ -lice
else:win32:CONFIG(debug, debug|release): LIBS += -L$(ICE_DIR)/lib/ -liced
else:unix: LIBS += -L$(ICE_DIR)/lib/ -lice

INCLUDEPATH += $(ICE_DIR)/include
DEPENDPATH += $(ICE_DIR)/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $(ICE_DIR)/lib/libice.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $(ICE_DIR)/lib/libiced.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $(ICE_DIR)/lib/ice.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $(ICE_DIR)/lib/iced.lib
else:unix: PRE_TARGETDEPS += $(ICE_DIR)/lib/libice.a

win32:CONFIG(release, debug|release): LIBS += -L$(ICE_DIR)/lib/ -liceutil
else:win32:CONFIG(debug, debug|release): LIBS += -L$(ICE_DIR)/lib/ -liceutild
else:unix: LIBS += -L$(ICE_DIR)/lib/ -liceutil

INCLUDEPATH += $(ICE_DIR)/include
DEPENDPATH += $(ICE_DIR)/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $(ICE_DIR)/lib/libiceutil.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $(ICE_DIR)/lib/libiceutild.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $(ICE_DIR)/lib/iceutil.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $(ICE_DIR)/lib/iceutild.lib
else:unix: PRE_TARGETDEPS += $(ICE_DIR)/lib/libiceutil.a
}

macx{
CONFIG   += console
#CONFIG   += C++11
CONFIG += x86
CONFIG += -arch x86_64

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -stdlib=libstdc++

LIBS += -framework IOKit
LIBS += -framework CoreFoundation

LIBS += -stdlib=libc++ #don't need -std=c++11

QMAKE_CXXFLAGS += -stdlib=libc++
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -mmacosx-version-min=10.7
QMAKE_LFLAGS += -mmacosx-version-min=10.7

INCLUDEPATH += -Wl,-rpath,/Library/Developer/Ice-3.5.1/lib -L/Library/Developer/Ice-3.5.1/lib -lIce -lIceUtil

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/release/ -lIce
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/debug/ -lIce
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIce

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/release/ -lIceUtil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/debug/ -lIceUtil
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIceUtil

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/release/ -lIce
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/debug/ -lIce
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIce

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/release/ -lIceUtil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/debug/ -lIceUtil
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIceUtil

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/release/ -lIce
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/debug/ -lIce
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIce

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/release/ -lIceUtil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/debug/ -lIceUtil
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIceUtil

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include

}
