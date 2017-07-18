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
    Q_PLUGIN_METADATA(IID "Xpiks.Plugins.XpiksPluginInterface.v0.1" FILE "helloworld.json")
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
    virtual const std::vector<std::shared_ptr<Plugins::IPluginAction> > &getExportedActions() const override { return m_MyActions; }
    virtual bool executeAction(int actionID) override;

public:
    virtual void initializePlugin() override;
    virtual void finalizePlugin() override;
    virtual void enablePlugin() override;
    virtual void disablePlugin() override;

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
