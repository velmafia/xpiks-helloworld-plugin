import QtQuick 2.2
import QtQuick.Dialogs 1.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

//import "../Constants"
import "qrc:/../Constants/Colors.js" as Colors;
//import "../Components"
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
        color: Colors.selectedArtworkColor
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

            StyledText {
                anchors.horizontalCenter: parent.horizontalCenter
                text: filteredArtItemsModel.getItemsCount()
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
