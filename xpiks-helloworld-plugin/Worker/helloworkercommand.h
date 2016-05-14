/*
 * This file is a part of HelloWorld plugin for Xpiks. Xpiks is
 * cross platform application for keywording and uploading images
 * for microstocks
 * Copyright (C) 2016 Taras Kushnir <kushnirTV@gmail.com>
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

#ifndef HELLOWORKERCOMMAND_H
#define HELLOWORKERCOMMAND_H

#include <Common/ibasicartwork.h>

class HelloWorkerCommand {
public:
    HelloWorkerCommand(Common::IBasicArtwork *basicArtwork, int flags = 0) :
        m_BasicArtwork(basicArtwork),
        m_CommandFlags(flags)
    {
    }

public:
    Common::IBasicArtwork *getInnerItem() const { return m_BasicArtwork; }
    int getFlags() const { return m_CommandFlags; }

private:
    Common::IBasicArtwork *m_BasicArtwork;
    int m_CommandFlags;
};

#endif // HELLOWORKERCOMMAND_H
