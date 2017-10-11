/*
 * This file is a part of Xpiks - cross platform application for
 * keywording and uploading images for microstocks
 * Copyright (C) 2014-2017 Taras Kushnir <kushnirTV@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

import QtQuick 2.2
import "qrc:/StyledControls"

Rectangle {
    id: helloWorldIconWrapper
    width: 24
    height: 20
    border.color: isHighlighted ? Colors.labelActiveForeground : Colors.inactiveControlColor
    border.width: 2
    color: "transparent"

    StyledText {
        text: "hw"
        color: helloWorldIconWrapper.border.color
        font.pixelSize: 10
        anchors.verticalCenterOffset: 1
        anchors.centerIn: parent
    }
}
