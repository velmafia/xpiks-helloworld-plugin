/*
 * This file is a part of Xpiks - cross platform application for
 * keywording and uploading images for microstocks
 * Copyright (C) 2014-2017 Taras Kushnir <kushnirTV@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef MAKEUSERHAPPYACTION
#define MAKEUSERHAPPYACTION

#include <QString>

#include <Plugins/ipluginaction.h>

class MakeUserHappyAction : public Plugins::IPluginAction {

public:
    MakeUserHappyAction():
        m_ActionName("Make user happy"),
        m_ID(123)
    { }

    // IPluginAction interface
public:
    virtual const QString &getActionName() const override { return m_ActionName; }
    virtual int getActionID() const override { return m_ID; }

private:
    QString m_ActionName;
    int m_ID;
};

#endif // MAKEUSERHAPPYACTION

