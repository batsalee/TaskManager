import QtQuick 6.5
import QtQuick.Controls 6.5

Window {
    id: textInputWindow
    width: 400
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
            text: qsTr("https://github.com/batsalee/TaskManager")
        }
    }
}
