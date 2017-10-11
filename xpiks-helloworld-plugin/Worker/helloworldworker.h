/*
 * This file is a part of Xpiks - cross platform application for
 * keywording and uploading images for microstocks
 * Copyright (C) 2014-2017 Taras Kushnir <kushnirTV@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef HELLOWORLDWORKER_H
#define HELLOWORLDWORKER_H

#include <QObject>
#include <QHash>
#include <memory>
#include <Common/itemprocessingworker.h>
#include "helloworkercommand.h"

class HelloWorldWorker : public QObject, public Common::ItemProcessingWorker<HelloWorkerCommand>
{
    Q_OBJECT
public:
    explicit HelloWorldWorker(QObject *parent = 0);

protected:
    virtual bool initWorker() override;
    virtual void processOneItem(std::shared_ptr<HelloWorkerCommand> &item) override;
    virtual void workerStopped() override {}

protected:
    virtual void notifyQueueIsEmpty() override { emit queueIsEmpty(); }

public slots:
    void process() { doWork(); }
    void cancel() { stopWorking(); }

signals:
    void stopped();
    void queueIsEmpty();

private:
    QHash<qint64, int> m_ResultsHash;
};

#endif // HELLOWORLDWORKER_H
