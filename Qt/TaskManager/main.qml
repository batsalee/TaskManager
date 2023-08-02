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
    flags: Qt.FramelessWindowHint | Qt.Window // Qt.Window 지워도 되는지 확인하기

    Clock {
        id: clock
        x: 0
        y: 0
        width: parent.width * 0.85
        height: 30

        MouseArea { // FramelessWindow를 만들되 창은 움직일 수 있어야 하므로
            anchors.fill: parent
            onPressed: {
                mainWindow.startSystemMove();
            }
        }
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

    // FramelessWindow를 만들되 창의 크기 조정은 가능해야 하므로


}
