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

DISTFILES += \
    libmysql.dll \
    FileSystem.ice \
    LuD.pro.user \
    LuD.pro.user.47f9476 \
    LuD.pro.user.ee9f765 \
    LuD.pro.user.IX7944 \
    LuD.pro.user.0f8f2c1 \
    LuD.pro.user.bn5604

FORMS += \
    addlocationdialogue.ui \
    adwidget.ui \
    articleworkspace.ui \
    checkemployeeswindow.ui \
    circulationwidget.ui \
    copyhistorywindow.ui \
    editemployeeinfo.ui \
    editortimesheetwidget.ui \
    editprofilewidget.ui \
    editroutewindow.ui \
    employeeswidget.ui \
    loginwindow.ui \
    mainwindow.ui \
    managetitles.ui \
    newarticleworkspacewindow.ui \
    permissionswidget.ui \
    photopoolwindow.ui \
    profilewidget.ui \
    registrationdialog.ui \
    registrationwindow.ui \
    subscriptionswidget.ui \
    writertimesheetwidget.ui \
    articleworkspaceaandewidget.ui \
    articleworkspacefeatureswidget.ui \
    articleworkspacenewswidget.ui \
    articleworkspaceopedwidget.ui \
    articleworkspacesportswidget.ui \
    articleworkspacevarietywidget.ui

HEADERS += \
    ad.h \
    addlocationdialogue.h \
    addlocationwindowdbc.h \
    adwidget.h \
    alert.h \
    archive.h \
    article.h \
    articleworkspace.h \
    articleworkspacedbc.h \
    checkemployeeswindow.h \
    circulationwidget.h \
    circulationwindowdbc.h \
    client.h \
    constants.h \
    copyhistorywindow.h \
    databasecontroller.h \
    editemployeeinfo.h \
    editemployeeinfodbc.h \
    editortimesheet.h \
    editortimesheetdbc.h \
    editortimesheetwidget.h \
    editprofiledbc.h \
    editprofilewidget.h \
    editroutewindow.h \
    editroutewindowdbc.h \
    employee.h \
    employeeswidget.h \
    employeetabledbc.h \
    FileSystem.h \
    idea.h \
    logincredentials.h \
    loginwindow.h \
    loginwindowdbc.h \
    mainwindow.h \
    mainwindowdbc.h \
    managetitles.h \
    newarticleworkspacewindow.h \
    newarticleworkspacewindowdbc.h \
    permissiondef.h \
    permissions.h \
    permissionswidget.h \
    permissionswidgetdbc.h \
    photopoolwindow.h \
    photopoolwindowdbc.h \
    profilewidget.h \
    profilewidgetdbc.h \
    registrationdialog.h \
    registrationwindow.h \
    registrationwindowdbc.h \
    remotedbconnection.h \
    route.h \
    sectiondef.h \
    Sender.h \
    subscription.h \
    subscriptionswidget.h \
    titledef.h \
    writertimesheet.h \
    writertimesheetdbc.h \
    writertimesheetwidget.h \
    diff.h \
    diff_match_patch.h \
    articleworkspaceaandewidget.h \
    articleworkspacefeatureswidget.h \
    articleworkspacenewswidget.h \
    articleworkspaceopedwidget.h \
    articleworkspacesportswidget.h \
    articleworkspacevarietywidget.h \
    DocxmlToString.h

SOURCES += \
    ad.cpp \
    addlocationdialogue.cpp \
    addlocationwindowdbc.cpp \
    adwidget.cpp \
    alert.cpp \
    archive.cpp \
    article.cpp \
    articleworkspace.cpp \
    articleworkspacedbc.cpp \
    checkemployeeswindow.cpp \
    circulationwidget.cpp \
    circulationwindowdbc.cpp \
    client.cpp \
    copyhistorywindow.cpp \
    databasecontroller.cpp \
    editemployeeinfo.cpp \
    editemployeeinfodbc.cpp \
    editortimesheet.cpp \
    editortimesheetdbc.cpp \
    editortimesheetwidget.cpp \
    editprofiledbc.cpp \
    editprofilewidget.cpp \
    editroutewindow.cpp \
    editroutewindowdbc.cpp \
    employee.cpp \
    employeeswidget.cpp \
    employeetabledbc.cpp \
    FileSystem.cpp \
    idea.cpp \
    logincredentials.cpp \
    loginwindow.cpp \
    loginwindowdbc.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowdbc.cpp \
    managetitles.cpp \
    newarticleworkspacewindow.cpp \
    newarticleworkspacewindowdbc.cpp \
    permissiondef.cpp \
    permissions.cpp \
    permissionswidget.cpp \
    permissionswidgetdbc.cpp \
    photopoolwindow.cpp \
    photopoolwindowdbc.cpp \
    profilewidget.cpp \
    profilewidgetdbc.cpp \
    registrationdialog.cpp \
    registrationwindow.cpp \
    registrationwindowdbc.cpp \
    remotedbconnection.cpp \
    route.cpp \
    sectiondef.cpp \
    Sender.cpp \
    subscription.cpp \
    subscriptionswidget.cpp \
    titledef.cpp \
    writertimesheet.cpp \
    writertimesheetdbc.cpp \
    writertimesheetwidget.cpp \
    diff.cpp \
    articleworkspaceaandewidget.cpp \
    articleworkspacefeatureswidget.cpp \
    articleworkspacenewswidget.cpp \
    articleworkspaceopedwidget.cpp \
    articleworkspacesportswidget.cpp \
    articleworkspacevarietywidget.cpp \
    DocxmlToString.cpp



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
