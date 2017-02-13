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

import QtQuick 2.2
import QtQuick.Dialogs 1.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

import "qrc:/../Constants"
import "qrc:/../StyledControls"

ApplicationWindow {
    id: aboutWindow
    objectName: "HelloWorldPlugin_0.1_Window"
    modality: "ApplicationModal"
    width: 250
    visible: true
    height: Qt.platform.os === "linux" ? 180 : 150
    /*minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height
    flags: Qt.Dialog
    title: qsTr("About")*/

    onClosing: {
        // NOTE: this will not work
        close.accepted = false
    }

    function closeAbout() {
        aboutWindow.close();
    }

    Rectangle {
        color: Colors.selectedArtworkBackground
        anchors.fill: parent

        Component.onCompleted: focus = true
        Keys.onEscapePressed: closeAbout()

        MouseArea {
            anchors.fill: parent
            onClicked: closeAbout()
        }

        ColumnLayout {
            anchors.centerIn: parent

            StyledText {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Hello World plugin")
            }

            StyledText {
                anchors.horizontalCenter: parent.horizontalCenter
                text: helloWorldModel.greetingText
            }

            Item {
                height: 10
            }

            StyledButton {
                width: 100
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Change Model")
                onClicked: {
                    helloWorldModel.greetingText = "Changed greeting"
                }
            }
        }
    }
}
