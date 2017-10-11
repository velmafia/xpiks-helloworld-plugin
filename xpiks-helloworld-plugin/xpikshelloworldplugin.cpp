/*
 * This file is a part of Xpiks - cross platform application for
 * keywording and uploading images for microstocks
 * Copyright (C) 2014-2017 Taras Kushnir <kushnirTV@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "xpikshelloworldplugin.h"
#include <QDebug>
#include <QThread>
#include "makeuserhappyaction.h"
#include "Worker/helloworldworker.h"
#include "Worker/helloworkercommand.h"

XpiksHelloworldPlugin::XpiksHelloworldPlugin(QObject *parent):
    QObject(parent),
    m_InsertedTabID(-1),
    m_CommandManager(NULL),
    m_UndoRedoManager(NULL),
    m_UIProvider(NULL),
    m_ArtworksSource(NULL),
    m_PresetsManager(NULL)
{
    qDebug() << "Construction...";

    m_PrettyName = QLatin1String("HelloWorldPlugin");
    m_Version = QLatin1String("v0.0.1");
    m_Author = QLatin1String("John Doe");

    std::shared_ptr<Plugins::IPluginAction> makeUserHappy(new MakeUserHappyAction());
    m_MyActions.push_back(makeUserHappy);
    m_ActionsHash.insert(makeUserHappy->getActionID(), makeUserHappy);
}

XpiksHelloworldPlugin::~XpiksHelloworldPlugin() {
    qDebug() << "Destruction...";
}

bool XpiksHelloworldPlugin::executeAction(int actionID) {
    if (m_ActionsHash.contains(actionID)) {
        // EXECUTE ACTION
        qInfo() << "Executing action:" << actionID;

        QHash<QString, QObject*> models;
        models.insert("helloWorldModel", &m_HelloWorldModel);

        m_UIProvider->openDialog(QUrl(QStringLiteral("qrc:/HelloWorldDialog.qml")), models);
    }

    return true;
}

void XpiksHelloworldPlugin::initializePlugin() {
    qDebug() << "#";

    Q_ASSERT(m_CommandManager != NULL);
    Q_ASSERT(m_UndoRedoManager != NULL);
    Q_ASSERT(m_UIProvider != NULL);
    Q_ASSERT(m_ArtworksSource != NULL);
    Q_ASSERT(m_PresetsManager != NULL);

    Q_INIT_RESOURCE(helloworldresources);

    m_CommandManager->addWarningsService(&m_HelloWorldService);
    m_InsertedTabID = m_UIProvider->addTab("qrc:/HelloWorldTabIcon.qml", "qrc:/HelloWorldTab.qml", nullptr);

    m_HelloWorldService.startService();
}

void XpiksHelloworldPlugin::finalizePlugin() {
    qDebug() << "#";
    m_HelloWorldService.stopService();
    if (m_InsertedTabID != -1) {
        m_UIProvider->removeTab(m_InsertedTabID);
    }
}

void XpiksHelloworldPlugin::enablePlugin() {
    qDebug() << "#";
    m_HelloWorldService.enableService();
}

void XpiksHelloworldPlugin::disablePlugin() {
    qDebug() << "#";
    m_HelloWorldService.disableService();
}

Common::flag_t XpiksHelloworldPlugin::getDesiredNotificationFlags() const {
    return Common::flag_t(Plugins::PluginNotificationFlags::CurrentEditableChanged);
}

void XpiksHelloworldPlugin::onPropertyChanged(Plugins::PluginNotificationFlags flag, const QVariant &data, void *pointer) {
    if (flag == Plugins::PluginNotificationFlags::CurrentEditableChanged) {
        const auto &currentEditable = m_UIProvider->getCurrentEditable();
        if (currentEditable) {
            LOG_INFO << "Current editable now:" << currentEditable->getItemID();
        } else {
            LOG_INFO << "Current editable has been dropped";
        }
    }
}

void XpiksHelloworldPlugin::injectCommandManager(Commands::ICommandManager *commandManager) {
    Q_ASSERT(commandManager != NULL);
    m_CommandManager = commandManager;
}

void XpiksHelloworldPlugin::injectUndoRedoManager(UndoRedo::IUndoRedoManager *undoRedoManager) {
    Q_ASSERT(undoRedoManager != NULL);
    m_UndoRedoManager = undoRedoManager;
}

void XpiksHelloworldPlugin::injectArtworksSource(Common::IArtworksSource *artworksSource) {
    Q_ASSERT(artworksSource != NULL);
    m_ArtworksSource = artworksSource;
}

void XpiksHelloworldPlugin::injectUIProvider(Plugins::IUIProvider *uiProvider) {
    Q_ASSERT(uiProvider != NULL);
    m_UIProvider = uiProvider;
}

void XpiksHelloworldPlugin::injectPresetsManager(KeywordsPresets::IPresetsManager *presetsManager) {
    Q_ASSERT(presetsManager != nullptr);
    m_PresetsManager = presetsManager;
}
