#ifndef XPIKSHELLOWORLDPLUGIN_H
#define XPIKSHELLOWORLDPLUGIN_H

#include <QObject>
#include <QString>
#include <QtPlugin>
#include <Plugins/xpiksplugininterface.h>
#include <Plugins/ipluginaction.h>

class XpiksHelloworldPlugin :
        public QObject,
        public Plugins::XpiksPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Xpiks.Plugins.XpiksPluginInterface.v0.1" FILE "helloworld.json")
    Q_INTERFACES(Plugins::XpiksPluginInterface)

public:
    XpiksHelloworldPlugin(QObject *parent=0);

    // XpiksPluginInterface interface
public:
    virtual const QString &getPrettyName() const { return m_PrettyName; }
    virtual const QString &getVersionString() const { return m_Version; }
    virtual const QString &getAuthor() const { return m_Author; }

public:
    virtual const QVector<Plugins::IPluginAction*> &getExportedActions() const { return m_MyActions; }
    virtual bool executeAction(int actionID);

public:
    virtual void injectCommandManager(Commands::ICommandManager *commandManager);
    virtual void injectUndoRedoManager(UndoRedo::IUndoRedoManager *undoRedoManager);

private:
    QString m_PrettyName;
    QString m_Version;
    QString m_Author;
    QVector<Plugins::IPluginAction*> m_MyActions;
    QHash<int, Plugins::IPluginAction*> m_ActionsHash;
    Commands::ICommandManager *m_CommandManager;
    UndoRedo::IUndoRedoManager *m_UndoRedoManager;
};

#endif // XPIKSHELLOWORLDPLUGIN_H
