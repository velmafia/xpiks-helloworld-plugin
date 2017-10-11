/*
 * This file is a part of Xpiks - cross platform application for
 * keywording and uploading images for microstocks
 * Copyright (C) 2014-2017 Taras Kushnir <kushnirTV@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef HELLOWORKERCOMMAND_H
#define HELLOWORKERCOMMAND_H

#include <Common/ibasicartwork.h>
#include <Common/flags.h>

class HelloWorkerCommand {
public:
    HelloWorkerCommand(Common::IBasicArtwork *basicArtwork, Common::WarningsCheckFlags flags = Common::WarningsCheckFlags::All) :
        m_BasicArtwork(basicArtwork),
        m_CommandFlags(flags)
    {
    }

public:
    Common::IBasicArtwork *getInnerItem() const { return m_BasicArtwork; }
    int getFlags() const { return (int)m_CommandFlags; }

private:
    Common::IBasicArtwork *m_BasicArtwork;
    Common::WarningsCheckFlags m_CommandFlags;
};

#endif // HELLOWORKERCOMMAND_H
