import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

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
        height: 30
    }

    TaskList { // 왼쪽에 표시될 할일들의 리스트 영역
        x: 0
        y: 30
        width: parent.width * 0.85
        height: parent.height - titlebar.height
    }

    ButtonList { // 오른쪽에 표시될 버튼들 영역
        x: parent.width * 0.85
        y: 30
        width: parent.width * 0.15
        height: parent.height - titlebar.height
    }
}
