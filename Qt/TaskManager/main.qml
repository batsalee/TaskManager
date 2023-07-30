import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

Window {
    width: Screen.width / 1.5
    height: Screen.height / 1.5
    visible: true
    color: "#333333"
    title: qsTr("TaskManager")

    TaskList {
        x: 0
        y: 0
        width: parent.width * 0.85
        height: parent.height
    }

    ButtonList {
        x: parent.width * 0.85
        y: 0
        width: parent.width * 0.15
        height: parent.height
    }
}
