#ifndef MAKEUSERHAPPYACTION
#define MAKEUSERHAPPYACTION

#include <Plugins/ipluginaction.h>
#include <QString>

class MakeUserHappyAction : public Plugins::IPluginAction {

public:
    MakeUserHappyAction():
        m_ActionName("Make user happy")
    { }

    // IPluginAction interface
public:
    const QString &getActionName() const { return m_ActionName; }
    int getActionID() const { return 123; }

private:
    QString m_ActionName;
};

#endif // MAKEUSERHAPPYACTION

