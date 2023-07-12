import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

Window {
    width: Screen.width / 1.5
    height: Screen.height / 1.5
    visible: true
    color: "#333333"
    title: qsTr("TaskManager")

    ListView {
        width: parent.width * 0.85
        height: parent.height
        model: 30 // c++에서 vector 갯수 몇개인지 받아와서 여기 써주면 됨
        delegate: Rectangle {
            x: 0
            y: 0
            width: parent.width
            height: 30
            color: index % 2 ? "#555555" : "#444444"

            Row {
                spacing: 10
                anchors.fill: parent
                Repeater {
                    model: 5 // vector size로 변경
                    Rectangle {
                        id: rectangle
                        width: scheduleText.width + 10
                        height: scheduleText.height
                        color: "#33AABB"
                        radius: 10
                        anchors.verticalCenter: parent.verticalCenter
                        Text {
                            id: scheduleText
                            x: parent + 5
                            anchors.centerIn: parent
                            color: "#FFFFFF"
                            font.pointSize: 12 // 여기를 vector 내의 내용으로 변경
                            text: "1일 1커밋"
                            font.bold: true
                        }
                        MouseArea {
                            width: parent.width
                            height: parent.height
                            onClicked: {
                                scheduleText.text = "clicked"
                            }
                        }
                    }
                }
            }
        }
    }

    Column {
        id: right_column
        x: parent.width * 0.85
        y: 0
        width: parent.width * 0.15
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
