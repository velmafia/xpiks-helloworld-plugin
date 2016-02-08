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

    //onClosing: dialogDestruction();

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
                focus: true
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("<u>Home webpage of Xpiks</u>")
                color: aboutMA.pressed ? Colors.defaultLightColor : Colors.artworkActiveColor

                MouseArea {
                    id: aboutMA
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true
                    onClicked: {
                        Qt.openUrlExternally("http://ribtoks.github.io/xpiks/")
                    }
                }
            }

            Item {
                height: 10
            }

            StyledButton {
                text: qsTr("Close")
                onClicked: {
                    closeAbout()
                }
            }
        }
    }
}
