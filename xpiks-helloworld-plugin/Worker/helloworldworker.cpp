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

#include "helloworldworker.h"
#include "helloworkercommand.h"
#include <Warnings/iwarningscheckable.h>
#include <Common/flags.h>

HelloWorldWorker::HelloWorldWorker(QObject *parent) : QObject(parent)
{
}

bool HelloWorldWorker::initWorker() {
    return true;
}

bool HelloWorldWorker::processOneItem(HelloWorkerCommand *item) {
    Warnings::IWarningsCheckable *checkable = item->getInnerItem();

    int warningsFlags = 0;
    int allCustomFlags = 1 << 30 | 1 << 29;

    qint64 id = checkable->getItemID();
    if (!m_ResultsHash.contains(id)) {
        // heavy calculation here ...
        warningsFlags = 1 << 30;
        m_ResultsHash.insert(id, warningsFlags);
    } else {
        // return result from hash
        warningsFlags = m_ResultsHash[id];
    }

    if (!checkable->getFilepath().isEmpty()) {
        checkable->dropWarningsFlags(allCustomFlags);
        checkable->addWarningsFlags(warningsFlags);
    }

    checkable->release();

    return true;
}
