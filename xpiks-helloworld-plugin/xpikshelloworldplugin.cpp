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
#include <QLatin1String>
#include <QUrl>
#include <QtGlobal>

#include <Common/flags.h>
#include <Common/logging.h>
#include <Models/Editing/icurrenteditable.h>
#include <Plugins/ipluginaction.h>
#include <Plugins/iuiprovider.h>

#include "makeuserhappyaction.h"

XpiksHelloworldPlugin::XpiksHelloworldPlugin(QObject *parent):
    QObject(parent),
    m_InsertedTabID(-1),
    m_CommandManager(nullptr),
    m_UIProvider(nullptr),
    m_PresetsManager(nullptr)
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

bool XpiksHelloworldPlugin::initialize(Common::ISystemEnvironment &environment) {
    qDebug() << "#";
    Q_UNUSED(environment);

    Q_ASSERT(m_CommandManager != nullptr);
    Q_ASSERT(m_UIProvider != nullptr);
    Q_ASSERT(m_PresetsManager != nullptr);

    Q_INIT_RESOURCE(helloworldresources);

    // m_CommandManager->addWarningsService(&m_HelloWorldService);
    m_InsertedTabID = m_UIProvider->addTab("qrc:/HelloWorldTabIcon.qml", "qrc:/HelloWorldTab.qml", nullptr);

    m_HelloWorldService.startService();

    return true;
}

void XpiksHelloworldPlugin::finalize() {
    qDebug() << "#";
    m_HelloWorldService.stopService();
    if (m_InsertedTabID != -1) {
        m_UIProvider->removeTab(m_InsertedTabID);
    }
}

void XpiksHelloworldPlugin::enable() {
    qDebug() << "#";
    m_HelloWorldService.enableService();
}

void XpiksHelloworldPlugin::disable() {
    qDebug() << "#";
    m_HelloWorldService.disableService();
}

Common::PluginNotificationFlags XpiksHelloworldPlugin::getDesiredNotificationFlags() const {
    return Common::PluginNotificationFlags::CurrentEditableChanged;
}

void XpiksHelloworldPlugin::onPropertyChanged(Common::PluginNotificationFlags flag, const QVariant &data, void *pointer) {
    if (flag == Common::PluginNotificationFlags::CurrentEditableChanged) {
        const auto &currentEditable = m_CurrentEditableSource->getCurrentEditable();
        if (currentEditable) {
            LOG_INFO << "Current editable now:" << currentEditable->getItemID();
        } else {
            LOG_INFO << "Current editable has been dropped";
        }
    }
}

void XpiksHelloworldPlugin::injectCommandManager(Commands::ICommandManager *commandManager) {
    Q_ASSERT(commandManager != nullptr);
    m_CommandManager = commandManager;
}

void XpiksHelloworldPlugin::injectUIProvider(Plugins::IUIProvider *uiProvider) {
    Q_ASSERT(uiProvider != nullptr);
    m_UIProvider = uiProvider;
}

void XpiksHelloworldPlugin::injectPresetsManager(KeywordsPresets::IPresetsManager *presetsManager) {
    Q_ASSERT(presetsManager != nullptr);
    m_PresetsManager = presetsManager;
}

void XpiksHelloworldPlugin::injectCurrentEditable(Models::ICurrentEditableSource *currentEditableSource) {
    Q_ASSERT(currentEditableSource != nullptr);
    m_CurrentEditableSource = currentEditableSource;
}
