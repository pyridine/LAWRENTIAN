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
    Sections.txt \
    LuDServer.pro.user.47f9476 \
    LuDServer.pro.user.83fecab

HEADERS += \
    FileSystem.h \
    FileSystemI.h \
    Receiver.h

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
