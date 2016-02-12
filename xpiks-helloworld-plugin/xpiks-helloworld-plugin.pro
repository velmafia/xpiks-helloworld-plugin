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
    Worker/helloworldworker.cpp \
    Worker/helloworldservice.cpp \
    Model/helloworldmodel.cpp

HEADERS += xpikshelloworldplugin.h \
    makeuserhappyaction.h \
    Worker/helloworldworker.h \
    Worker/helloworkercommand.h \
    Worker/helloworldservice.h \
    Model/helloworldmodel.h

DISTFILES += \
    helloworld.json

RESOURCES += \
    helloworldresources.qrc
