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
        id: listView
        width: parent.width * 0.85
        height: parent.height
        model: lineCount
        delegate: Rectangle {
            id: backgroundRect
            x: 0
            y: 0
            width: parent.width
            height: 30
            color: index % 2 ? "#555555" : "#444444"

            property int yIndex;
            property int xIndex;
            function getxIndex() { yIndex = index; }

            Row {
                spacing: 10
                anchors.fill: parent
                Repeater {
                    id: repeater
                    model: taskList[index]
                    Rectangle {
                        id: rectangle
                        width: scheduleText.width + 10
                        height: scheduleText.height
                        color: "#33AABB"
                        radius: 10
                        anchors.verticalCenter: parent.verticalCenter
                        Text {
                            id: scheduleText
                            x: 5
                            anchors.centerIn: parent
                            color: "#FFFFFF"
                            font.pointSize: 12
                            text: modelData
                            font.bold: true
                        }
                        MouseArea {
                            width: parent.width
                            height: parent.height
                            onDoubleClicked: {
                                repeater.model = taskList[yIndex];

                                // 클릭한 사각형의 인덱스를 얻어서 list에서 remove 해주기
                                backgroundRect.getxIndex();
                                xIndex = index;
                                scheduler.removeTask(yIndex, xIndex);
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
