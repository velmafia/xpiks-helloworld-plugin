/*
 * This file is a part of Xpiks - cross platform application for
 * keywording and uploading images for microstocks
 * Copyright (C) 2014-2017 Taras Kushnir <kushnirTV@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef HELLOWORLDMODEL_H
#define HELLOWORLDMODEL_H

#include <QObject>
#include <QString>

class HelloWorldModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString greetingText READ getGreetingText WRITE setGreetingText NOTIFY greetingTextChanged)
public:
    explicit HelloWorldModel(QObject *parent = 0);

public:
    const QString &getGreetingText() const { return m_GreetingText; }
    void setGreetingText(const QString &value) {
        if (m_GreetingText != value) {
            m_GreetingText = value;
            emit greetingTextChanged();
        }
    }

signals:
    void greetingTextChanged();

private:
    QString m_GreetingText;
};

#endif // HELLOWORLDMODEL_H
