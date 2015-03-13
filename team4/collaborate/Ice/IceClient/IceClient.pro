#-------------------------------------------------
#
# Project created by QtCreator 2015-02-05T15:43:49
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = IceClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Printer.cpp

HEADERS += \
    Printer.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIceUtil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIceUtild
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIceUtil

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIce
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIced
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIce

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIce
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIced
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIce

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIceUtil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIceUtild
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIceUtil

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIce
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIced
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIce

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIceUtil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIceUtild
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIceUtil

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIce
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIced
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIce

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIceUtil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIceUtild
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIceUtil

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIce
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIced
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIce

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIceUtil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIceUtild
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/ -lIceUtil

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIce
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIced
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIce.35

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIceUtil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIceUtild
else:unix: LIBS += -L$$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11/ -lIceUtil.35

INCLUDEPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11
DEPENDPATH += $$PWD/../../../../../../Library/Developer/Ice-3.5.1/lib/c++11


