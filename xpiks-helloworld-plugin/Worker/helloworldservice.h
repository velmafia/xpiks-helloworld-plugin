/*
 * This file is a part of HelloWorld plugin for Xpiks. Xpiks is
 * cross platform application for keywording and uploading images
 * for microstocks
 * Copyright (C) 2016-2017 Taras Kushnir <kushnirTV@gmail.com>
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

#ifndef HELLOWORLDSERVICE_H
#define HELLOWORLDSERVICE_H

#include <QObject>
#include <QVector>
#include <Common/iservicebase.h>
#include <Common/ibasicartwork.h>
#include <Common/flags.h>

class HelloWorldWorker;

class HelloWorldService :
        public QObject,
        public Common::IServiceBase<Common::IBasicArtwork, Common::WarningsCheckFlags>
{
    Q_OBJECT
public:
    explicit HelloWorldService(QObject *parent = 0);

public:
    virtual void startService(const std::shared_ptr<Common::ServiceStartParams> &params);
    virtual void stopService();

    virtual bool isAvailable() const { return m_IsAvailable; }
    virtual bool isBusy() const { return false; }

    virtual void submitItem(Common::IBasicArtwork *item);
    virtual void submitItem(Common::IBasicArtwork *item, Common::WarningsCheckFlags flags);
    virtual void submitItems(const QVector<Common::IBasicArtwork*> &items);

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
