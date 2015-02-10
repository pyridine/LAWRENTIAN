#-------------------------------------------------
#
# Project created by QtCreator 2015-02-09T20:33:52
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = LuDServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    FileSystem.cpp \
    FileSystemI.cpp \
    Receiver.cpp

DISTFILES += \
    FileSystem.ice \
    LuDServer.pro.user \
    Sections.txt

HEADERS += \
    FileSystem.h \
    FileSystemI.h \
    Receiver.h

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
