#-------------------------------------------------
#
# Project created by QtCreator 2016-02-07T20:53:32
#
#-------------------------------------------------

QT       -= gui

TARGET = xpiks-helloworld-plugin
TEMPLATE = lib
CONFIG += plugin
CONFIG += c++11

VERSION = 0.0.1.0
QMAKE_TARGET_PRODUCT = xpiks-helloworld-plugin
QMAKE_TARGET_DESCRIPTION = "Sample implementation of a plugin for Xpiks"
QMAKE_TARGET_COPYRIGHT = "Copyright (C) 2016-2018 Taras Kushnir"

#DEFINES += XPIKSHELLOWORLDPLUGIN_LIBRARY
INCLUDEPATH += "../../xpiks/src/xpiks-qt/"

travis-ci | appveyor {
    INCLUDEPATH += "../../../../xpiks-qt/"
}

SOURCES += xpikshelloworldplugin.cpp \
    Worker/helloworldworker.cpp \
    Worker/helloworldservice.cpp \
    Model/helloworldmodel.cpp \
    ../../xpiks/src/xpiks-qt/Helpers/threadhelpers.cpp

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

BRANCH_NAME=$$system(git rev-parse --abbrev-ref HEAD)
#BRANCH_NAME=ui_upgrade_15

CONFIG(debug, debug|release)  {
    message("Building debug")
} else {
    message("Building release")
}

macx {
    CONFIG(debug, debug|release)  {
        # copy to Xpiks Plugins directory after build
        DESTDIR = $$shell_path("~/Library/Application Support/Xpiks/Xpiks_debug/$${BRANCH_NAME}/plugins/")
    }
}

!appveyor {
    win32 {
        CONFIG(debug, debug|release)  {
            APP_DATA = $$(APPDATA)
            message(Deploying to $${APP_DATA})
            # copy to Xpiks Plugins directory after build
            DESTDIR = $$shell_path("$${APP_DATA}/Xpiks/Xpiks_debug/$${BRANCH_NAME}/plugins/")
        }
    }
}
