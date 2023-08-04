import QtQuick
import QtQuick.Controls 6.3

Window {
    id: textInputWindow
    width: 300
    height: 100
    title: qsTr("Information")

    Rectangle {
        anchors.fill: parent
        color: "#333333"

        Text {
            anchors.fill: parent
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            font.pointSize: 10
            color: "#FFFFFF"
            text: qsTr("")
        }
    }
}
