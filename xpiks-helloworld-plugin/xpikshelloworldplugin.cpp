/*
 * This file is a part of HelloWorld plugin for Xpiks. Xpiks is
 * cross platform application for keywording and uploading images
 * for microstocks
 * Copyright (C) 2016-2017 Taras Kushnir <kushnirTV@gmail.com>
 *
 * Xpiks is distributed under the GNU General Public License, version 3.0
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

    MakeUserHappyAction *makeUserHappy = new MakeUserHappyAction();
    m_MyActions.push_back(makeUserHappy);
    m_ActionsHash.insert(makeUserHappy->getActionID(), makeUserHappy);
}

XpiksHelloworldPlugin::~XpiksHelloworldPlugin() {
    qDeleteAll(m_MyActions);
}

bool XpiksHelloworldPlugin::executeAction(int actionID) {
    if (m_ActionsHash.contains(actionID)) {
        // EXECUTE ACTION
        qInfo() << "Executing action:" << actionID;

        QHash<QString, QObject*> models;
        models.insert("helloWorldModel", &m_HelloWorldModel);
        m_UIProvider->openWindow(QUrl(QStringLiteral("qrc:/HelloPluginWindow.qml")),
                                 models);
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
    m_InsertedTabID = m_UIProvider->addTab("qrc:/HelloWorldTabIcon.qml", "qrc:/HelloWorldTab.qml");

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

Plugins::PluginNotificationFlags XpiksHelloworldPlugin::getDesiredNotificationFlags() const {
    return Plugins::PluginNotificationFlags::CurrentEditbleChanged;
}

void XpiksHelloworldPlugin::onPropertyChanged(Plugins::PluginNotificationFlags flag, const QVariant &data, void *pointer) {
    if (flag == Plugins::PluginNotificationFlags::CurrentEditbleChanged) {
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
