import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

Window {
    width: Screen.width / 1.5
    height: Screen.height / 1.5
    visible: true
    color: "#333333"
    title: qsTr("TaskManager")

    ScrollView {
        id: scrollView
        width: parent.width * 0.85
        height: parent.height
        clip: true

        ListView {
            width: parent.width
            height: parent.height
            model: 20 // c++에서 vector 갯수 몇개인지 받아와서 여기 써주면 됨. 너무 많으면 스크롤도 저절로 생김
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
                                            Text {
                                                height: 20
                                                text: "Hello World"
                                                Rectangle {
                                                                    anchors.centerIn: parent
                                                                       color: "orange"
                                                                   }
                                            }


                                        }
                                    }
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
