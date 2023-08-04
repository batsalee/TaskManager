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

    ////////////////////////////////////////////////////
    /* 아래 MouseArea들의 목적
        FramelessWindow를 만들되 창의 크기 조정은 가능해야 하므로
        오른쪽구석에서 오른쪽으로 끌면 오른쪽으로 커지게, 아래에서 아래로 끌면 아래로 커지게
        오른쪽아래 구석에서 끌면 오른쪽아래로 커지게 만들기 위한 용도
    */
    MouseArea { // 우하단
        width: 7
        height: 7
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        cursorShape: Qt.SizeFDiagCursor
        onPressed: {
            mainWindow.startSystemResize(Qt.BottomEdge | Qt.RightEdge);
        }
    }

    MouseArea { // 좌상단
        width: 7
        height: 7
        anchors.left: parent.left
        anchors.top: parent.top
        cursorShape: Qt.SizeFDiagCursor
        onPressed: {
            mainWindow.startSystemResize(Qt.TopEdge | Qt.LeftEdge);
        }
    }

    MouseArea { // 상
        x: 7
        width: (parent.width * 0.85) - 7
        height: 7
        anchors.top: parent.top
        cursorShape: Qt.SizeVerCursor
        onPressed: {
            mainWindow.startSystemResize(Qt.TopEdge);
        }
    }

    MouseArea { // 하
        x: 7
        width: parent.width - 14
        height: 7
        anchors.bottom: parent.bottom
        cursorShape: Qt.SizeVerCursor
        onPressed: {
            mainWindow.startSystemResize(Qt.BottomEdge);
        }
    }

    MouseArea { // 좌
        y: 7
        width: 7
        height: parent.height - 14
        anchors.left: parent.left
        cursorShape: Qt.SizeHorCursor
        onPressed: {
            mainWindow.startSystemResize(Qt.LeftEdge);
        }
    }

    MouseArea { // 우
        y: 30
        width: 7
        height: parent.height - 37
        anchors.right: parent.right
        cursorShape: Qt.SizeHorCursor
        onPressed: {
            mainWindow.startSystemResize(Qt.RightEdge);
        }
    }

    MouseArea { // 좌하단
        width: 7
        height: 7
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        cursorShape: Qt.SizeBDiagCursor
        onPressed: {
            mainWindow.startSystemResize(Qt.BottomEdge | Qt.LeftEdge);
        }
    }
    // 우상단은 X키랑 겹쳐서 그냥 안만들기로
}
