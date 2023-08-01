import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

Window {
    width: Screen.width / 2
    height: Screen.height / 2
    visible: true
    color: "#333333"
    title: qsTr("TaskManager")

    Clock {
        id: clock
        x: 0
        y: 0
        width: parent.width * 0.85
        height: 30
    }

    TaskList {
        x: 0
        y: 30
        width: parent.width * 0.85
        height: parent.height - clock.height
    }

    ButtonList {
        x: parent.width * 0.85
        y: 0
        width: parent.width * 0.15
        height: parent.height
    }
}
