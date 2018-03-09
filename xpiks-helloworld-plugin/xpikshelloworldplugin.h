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

#include <QObject>
#include <QString>
#include <QtPlugin>
#include <Plugins/xpiksplugininterface.h>
#include <Plugins/ipluginaction.h>
#include <Plugins/iuiprovider.h>
#include "Worker/helloworldservice.h"
#include "Model/helloworldmodel.h"

class XpiksHelloworldPlugin :
        public QObject,
        public Plugins::XpiksPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Xpiks.Plugins.XpiksPluginInterface.v0.0.1" FILE "helloworld.json")
    Q_INTERFACES(Plugins::XpiksPluginInterface)

public:
    XpiksHelloworldPlugin(QObject *parent=0);
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
    virtual bool initialize() override;
    virtual void finalize() override;
    virtual void enable() override;
    virtual void disable() override;

public:
    virtual Common::flag_t getDesiredNotificationFlags() const override;
    virtual void onPropertyChanged(Plugins::PluginNotificationFlags flag, const QVariant &data, void *pointer) override;

public:
    virtual void injectCommandManager(Commands::ICommandManager *commandManager) override;
    virtual void injectUndoRedoManager(UndoRedo::IUndoRedoManager *undoRedoManager) override;
    virtual void injectArtworksSource(Common::IArtworksSource *artworksSource) override;
    virtual void injectUIProvider(Plugins::IUIProvider *uiProvider) override;
    virtual void injectPresetsManager(KeywordsPresets::IPresetsManager *presetsManager) override;

private:
    QString m_PrettyName;
    QString m_Version;
    QString m_Author;

    int m_InsertedTabID;

    std::vector<std::shared_ptr<Plugins::IPluginAction> > m_MyActions;
    QHash<int, std::shared_ptr<Plugins::IPluginAction> > m_ActionsHash;

    Commands::ICommandManager *m_CommandManager;
    UndoRedo::IUndoRedoManager *m_UndoRedoManager;
    Plugins::IUIProvider *m_UIProvider;
    Common::IArtworksSource *m_ArtworksSource;
    KeywordsPresets::IPresetsManager *m_PresetsManager;

    HelloWorldService m_HelloWorldService;
    HelloWorldModel m_HelloWorldModel;
};

#endif // XPIKSHELLOWORLDPLUGIN_H
