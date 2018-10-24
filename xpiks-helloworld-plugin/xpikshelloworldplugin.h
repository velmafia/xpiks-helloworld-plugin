/*
 * This file is a part of Xpiks - cross platform application for
 * keywording and uploading images for microstocks
 * Copyright (C) 2014-2017 Taras Kushnir <kushnirTV@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef XPIKSHELLOWORLDPLUGIN_H
#define XPIKSHELLOWORLDPLUGIN_H

#include <memory>
#include <vector>

#include <QHash>
#include <QObject>
#include <QString>
#include <QVariant>

#include <Common/flags.h>
#include <Plugins/xpiksplugininterface.h>

#include "Model/helloworldmodel.h"
#include "Worker/helloworldservice.h"

namespace Commands {
    class ICommandManager;
}

namespace Common {
    class ISystemEnvironment;
}

namespace KeywordsPresets {
    class IPresetsManager;
}

namespace Models {
    class ICurrentEditableSource;
}

namespace Plugins {
    class IPluginAction;
    class IUIProvider;
}

class XpiksHelloworldPlugin :
        public QObject,
        public Plugins::XpiksPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Xpiks.Plugins.XpiksPluginInterface.v0.0.1" FILE "helloworld.json")
    Q_INTERFACES(Plugins::XpiksPluginInterface)

public:
    XpiksHelloworldPlugin(QObject *parent=nullptr);
    virtual ~XpiksHelloworldPlugin();

    // XpiksPluginInterface interface
public:
    virtual const QString &getPrettyName() const override { return m_PrettyName; }
    virtual const QString &getVersionString() const override { return m_Version; }
    virtual const QString &getAuthor() const override { return m_Author; }

public:
    virtual std::vector<std::shared_ptr<Plugins::IPluginAction> > getExportedActions() const override { return m_MyActions; }
    virtual bool executeAction(int actionID) override;

public:
    virtual bool initialize(Common::ISystemEnvironment &environment) override;
    virtual void finalize() override;
    virtual void enable() override;
    virtual void disable() override;

public:
    virtual Common::PluginNotificationFlags getDesiredNotificationFlags() const override;
    virtual void onPropertyChanged(Common::PluginNotificationFlags flag, const QVariant &data, void *pointer) override;

public:
    virtual void injectCommandManager(Commands::ICommandManager *commandManager) override;
    virtual void injectUIProvider(Plugins::IUIProvider *uiProvider) override;
    virtual void injectPresetsManager(KeywordsPresets::IPresetsManager *presetsManager) override;
    virtual void injectCurrentEditable(Models::ICurrentEditableSource *currentEditableSource) override;

private:
    QString m_PrettyName;
    QString m_Version;
    QString m_Author;

    int m_InsertedTabID;

    std::vector<std::shared_ptr<Plugins::IPluginAction> > m_MyActions;
    QHash<int, std::shared_ptr<Plugins::IPluginAction> > m_ActionsHash;

    Commands::ICommandManager *m_CommandManager;
    Plugins::IUIProvider *m_UIProvider;
    KeywordsPresets::IPresetsManager *m_PresetsManager;
    Models::ICurrentEditableSource *m_CurrentEditableSource;

    HelloWorldService m_HelloWorldService;
    HelloWorldModel m_HelloWorldModel;
};

#endif // XPIKSHELLOWORLDPLUGIN_H
