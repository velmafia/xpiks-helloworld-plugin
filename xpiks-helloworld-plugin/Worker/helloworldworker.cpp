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

#include <QStringList>

#include <Artworks/iartworkmetadata.h>

#include "Worker/helloworkercommand.h"

HelloWorldWorker::HelloWorldWorker(QObject *parent) : QObject(parent)
{
}

bool HelloWorldWorker::initWorker() {
    return true;
}

void HelloWorldWorker::processOneItem(const std::shared_ptr<HelloWorkerCommand> &item) {
    auto &checkable = item->getInnerItem();

    int warningsFlags = 0;

    if (checkable->hasKeywords(QStringList() << "test")) {
        // heavy calculation here ...
        warningsFlags = 1 << 30;
        m_ResultsHash.insert(0, warningsFlags);
    } else {
        // return result from hash
        warningsFlags = m_ResultsHash[0];
    }
}
