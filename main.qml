import QtQuick 6.5
import QtQuick.Controls 6.5
import QtQuick.Layouts 6.5
import "./qml"

Window {
    id: mainWindow
    width: Screen.width / 2
    height: Screen.height / 2
    visible: true
    color: "#333333"
    title: qsTr("TaskManager")
    flags: Qt.FramelessWindowHint | Qt.Window

    Resizer {
        z: 2
    }

    TitleBar {
        id: titlebar
        x: 0
        y: 0
        width: mainWindow.width
        height: 37
    }

    TaskList { // 왼쪽에 표시될 할일들의 리스트 영역
        id: taskList
        x: 0
        y: 37
        width: parent.width * 0.85
        height: parent.height - titlebar.height
    }

    ButtonList { // 오른쪽에 표시될 버튼들 영역
        id: buttonList
        x: parent.width * 0.85
        y: 37
        width: parent.width * 0.15
        height: parent.height - titlebar.height
    }
}
