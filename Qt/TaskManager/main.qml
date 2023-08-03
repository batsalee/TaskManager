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
    flags: Qt.FramelessWindowHint

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

    MouseArea {
        /* MouseArea의 목적
            FramelessWindow를 만들되 창의 크기 조정은 가능해야 하므로
            오른쪽구석에서 오른쪽으로 끌면 오른쪽으로 커지게, 아래에서 아래로 끌면 아래로 커지게
            오른쪽아래 구석에서 끌면 오른쪽아래로 커지게 만들기 위한 용도
        */
        width: 7
        height: 7
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        cursorShape: Qt.SizeFDiagCursor
        onPressed: {
            mainWindow.startSystemResize(Qt.BottomEdge | Qt.RightEdge);
        }
    }
}
