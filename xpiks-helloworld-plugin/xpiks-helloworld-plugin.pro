#-------------------------------------------------
#
# Project created by QtCreator 2016-02-07T20:53:32
#
#-------------------------------------------------

QT       -= gui

TARGET = xpiks-helloworld-plugin
TEMPLATE = lib
CONFIG += plugin

#DEFINES += XPIKSHELLOWORLDPLUGIN_LIBRARY
INCLUDEPATH += "../../xpiks/src/xpiks-qt/"

SOURCES += xpikshelloworldplugin.cpp \
    helloworldworker.cpp \
    helloworldservice.cpp

HEADERS += xpikshelloworldplugin.h \
    makeuserhappyaction.h \
    helloworldworker.h \
    helloworkercommand.h \
    helloworldservice.h

DISTFILES += \
    helloworld.json

RESOURCES += \
    helloworldresources.qrc
