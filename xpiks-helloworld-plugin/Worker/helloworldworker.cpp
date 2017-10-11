/*
 * This file is a part of Xpiks - cross platform application for
 * keywording and uploading images for microstocks
 * Copyright (C) 2014-2017 Taras Kushnir <kushnirTV@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "helloworldworker.h"
#include "helloworkercommand.h"
#include <Common/ibasicartwork.h>
#include <Common/flags.h>

HelloWorldWorker::HelloWorldWorker(QObject *parent) : QObject(parent)
{
}

bool HelloWorldWorker::initWorker() {
    return true;
}

void HelloWorldWorker::processOneItem(std::shared_ptr<HelloWorkerCommand> &item) {
    Common::IBasicArtwork *checkable = item->getInnerItem();

    int warningsFlags = 0;
    //int allCustomFlags = 1 << 30 | 1 << 29;

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
        //checkable->dropWarningsFlags(allCustomFlags);
        //checkable->addWarningsFlags(warningsFlags);
    }

    //checkable->release();
}
