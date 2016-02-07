#include "xpikshelloworldplugin.h"

XpiksHelloworldPlugin::XpiksHelloworldPlugin(QObject *parent):
    QObject(parent)
{
    m_PrettyName = QLatin1String("HelloWorldPlugin");
    m_Version = QLatin1String("v0.0.1");
    m_Author = QLatin1String("John Doe");
}

void XpiksHelloworldPlugin::injectCommandManager(Commands::ICommandManager *commandManager) const {
    Q_UNUSED(commandManager);
}

void XpiksHelloworldPlugin::injectUndoRedoManager(UndoRedo::IUndoRedoManager *undoRedoManager) const {
    Q_UNUSED(undoRedoManager);
}
