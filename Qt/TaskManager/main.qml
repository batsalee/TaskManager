import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

Window {
    width: Screen.width / 1.5
    height: Screen.height / 1.5
    visible: true
    color: "#333333"
    title: qsTr("TaskManager")

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: parent.width / 100 * 85
        height: parent.height
        color: "#1e1e1e"

        Column {
            id: left_column
            width: parent.width
            height: parent.height

            Row {
                id: row1
                width: parent.width
                height: 30

                Rectangle {
                    id: rectangle1
                    width: parent.width
                    height: 30
                    color: "#333333"

                    Text {
                        id: text1
                        color: "#FFFFFF"
                        text: qsTr("글씨 써지는거 확인")
                        font.pixelSize: 18
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
            id: button1
            x: 0
            y: 0
            width: parent.width
            height: parent.height / 10
            text: qsTr("새로 고침")
        }

        Button {
            id: button2
            x: 0
            y: 0
            width:  parent.width
            height: parent.height / 10
            text: qsTr("일정 관리")
        }
    }
}
