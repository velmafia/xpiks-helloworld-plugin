/*
 * This file is a part of Xpiks - cross platform application for
 * keywording and uploading images for microstocks
 * Copyright (C) 2014-2017 Taras Kushnir <kushnirTV@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef HELLOWORLDSERVICE_H
#define HELLOWORLDSERVICE_H

#include <QObject>
#include <QVector>
#include <Common/flags.h>
#include <Artworks/iartworkmetadata.h>

class HelloWorldWorker;

class HelloWorldService: public QObject
{
    Q_OBJECT
public:
    explicit HelloWorldService(QObject *parent = 0);

public:
    void startService();
    void stopService();

    bool isAvailable() const { return m_IsAvailable; }
    bool isBusy() const { return false; }

    void submitItem(std::shared_ptr<Artworks::IArtworkMetadata> const &item);
    void submitItem(std::shared_ptr<Artworks::IArtworkMetadata> const &item, Common::WarningsCheckFlags flags);

public:
    void disableService() { m_IsAvailable = false; }
    void enableService() { m_IsAvailable = true; }

public slots:
    void disableRequested() { disableService(); }

private slots:
    void workerDestroyed(QObject *object);

private:
    HelloWorldWorker *m_Worker;
    bool m_IsAvailable;
};

#endif // HELLOWORLDSERVICE_H
