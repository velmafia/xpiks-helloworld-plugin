/*
 * This file is a part of Xpiks - cross platform application for
 * keywording and uploading images for microstocks
 * Copyright (C) 2014-2017 Taras Kushnir <kushnirTV@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "helloworldservice.h"
#include <QThread>
#include "helloworldworker.h"
#include "helloworkercommand.h"

HelloWorldService::HelloWorldService(QObject *parent) :
    QObject(parent),
    m_Worker(NULL)
{
}

void HelloWorldService::startService() {
    if (m_Worker != NULL) { return; }

    m_Worker = new HelloWorldWorker();

    QThread *thread = new QThread();
    m_Worker->moveToThread(thread);

    QObject::connect(thread, SIGNAL(started()), m_Worker, SLOT(process()));
    QObject::connect(m_Worker, SIGNAL(stopped()), thread, SLOT(quit()));

    QObject::connect(m_Worker, SIGNAL(stopped()), m_Worker, SLOT(deleteLater()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    QObject::connect(m_Worker, SIGNAL(destroyed(QObject*)),
                     this, SLOT(workerDestroyed(QObject*)));

    qInfo() << "Starting worker";

    thread->start();
}

void HelloWorldService::stopService() {
    if (m_Worker != NULL) {
        qInfo() << "Stopping worker";
        m_Worker->stopWorking();
    }
}

void HelloWorldService::submitItem(std::shared_ptr<Artworks::IArtworkMetadata> const &item) {
    Common::WarningsCheckFlags defaultFlags = Common::WarningsCheckFlags::All;
    this->submitItem(item, defaultFlags);
}

void HelloWorldService::submitItem(std::shared_ptr<Artworks::IArtworkMetadata> const &item,
                                   Common::WarningsCheckFlags flags) {
    if (m_Worker == NULL) { return; }

    std::shared_ptr<HelloWorkerCommand> command(new HelloWorkerCommand(item, flags));
    m_Worker->submitItem(command);
}

void HelloWorldService::workerDestroyed(QObject *object) {
    Q_UNUSED(object);
    m_Worker = NULL;
}
