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
import QtQuick.Dialogs 1.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

import "qrc:/../Constants"
import "qrc:/../StyledControls"
import "qrc:/../Common.js" as Common

Item {
    id: helloWorldComponent
    anchors.fill: parent

    signal dialogDestruction();
    Component.onDestruction: dialogDestruction();

    Keys.onEscapePressed: closePopup()

    function closePopup() {
        helloWorldComponent.destroy()
    }

    function onAfterCreated() {
        dialogWindow.anchors.centerIn = undefined
    }

    PropertyAnimation { target: helloWorldComponent; property: "opacity";
        duration: 400; from: 0; to: 1;
        easing.type: Easing.InOutQuad ; running: true }

    // This rectange is the a overlay to partially show the parent through it
    // and clicking outside of the 'dialog' popup will do 'nothing'
    Rectangle {
        anchors.fill: parent
        id: overlay
        color: "#000000"
        opacity: 0.6
        // add a mouse area so that clicks outside
        // the dialog window will not do anything
        MouseArea {
            anchors.fill: parent
        }
    }

    FocusScope {
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent
            onWheel: wheel.accepted = true
            onClicked: mouse.accepted = true
            onDoubleClicked: mouse.accepted = true

            property real old_x : 0
            property real old_y : 0

            /* THIS IS OPTIONAL */
            onPressed:{
                var tmp = mapToItem(helloWorldComponent, mouse.x, mouse.y);
                old_x = tmp.x;
                old_y = tmp.y;

                var dialogPoint = mapToItem(dialogWindow, mouse.x, mouse.y);
                if (!Common.isInComponent(dialogPoint, dialogWindow)) {
                    closePopup()
                }
            }

            /* THIS IS OPTIONAL TOO */
            onPositionChanged: {
                var old_xy = Common.movePopupInsideComponent(helloWorldComponent, dialogWindow, mouse, old_x, old_y);
                old_x = old_xy[0]; old_y = old_xy[1];
            }
        }

        // This rectangle is the actual popup
        Rectangle {
            id: dialogWindow
            width: 400
            height: 300
            color: uiColors.selectedArtworkBackground
            anchors.centerIn: parent
            //Component.onCompleted: anchors.centerIn = undefined

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
}
