import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

Window {
    width: Screen.width / 1.5
    height: Screen.height / 1.5
    visible: true
    color: "#333333"
    title: qsTr("TaskManager")

    Column {
        id: column
        x: 0
        y: 0
        width: parent.width / 100 * 85
        height: parent.height

        Repeater {
            model: 50 // 나중에 vector 갯수 파악해서 여기로 가져와서 써주면 될듯? 아니면 디자인을 위해 걍 놔두거나
            Rectangle {
                id: rectangle
                x: 0
                y: 0
                width: parent.width
                height: 30
                color: Positioner.index % 2 ? "#555555" : "#444444"

            }
        }
    }


    Column {
        id: right_column
        x: parent.width / 100 * 85
        y: 0
        width: parent.width / 100 * 15
        height: parent.height

        Button {
            id: refresh
            x: 0
            y: 0
            width: parent.width
            height: parent.height / 10
            text: qsTr("새로 고침")
        }

        Button {
            id: task_manage
            x: 0
            y: 0
            width:  parent.width
            height: parent.height / 10
            text: qsTr("일정 관리")
        }

        Button {
            id: long_term_goal
            x: 0
            y: 0
            width:  parent.width
            height: parent.height / 10
            text: qsTr("장기 계획")
        }
    }
}
