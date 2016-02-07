#ifndef XPIKSHELLOWORLDPLUGIN_H
#define XPIKSHELLOWORLDPLUGIN_H

#include <QObject>
#include <QString>
#include <QtPlugin>
#include <Plugins/xpiksplugininterface.h>

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
    virtual void injectCommandManager(Commands::ICommandManager *commandManager) const;
    virtual void injectUndoRedoManager(UndoRedo::IUndoRedoManager *undoRedoManager) const;

private:
    QString m_PrettyName;
    QString m_Version;
    QString m_Author;
};

#endif // XPIKSHELLOWORLDPLUGIN_H
