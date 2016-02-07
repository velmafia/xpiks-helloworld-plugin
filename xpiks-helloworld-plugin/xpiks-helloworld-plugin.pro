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

SOURCES += xpikshelloworldplugin.cpp

HEADERS += xpikshelloworldplugin.h

DISTFILES += \
    helloworld.json
