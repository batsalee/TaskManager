import QtQuick
import QtQuick.Layouts 6.3

ListView {
    id: listView
    clip: true
    model: scheduler.getTaskList()
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
            leftPadding: 5
            spacing: 10
            anchors.fill: parent
            Repeater {
                id: repeater
                model: modelData
                Rectangle {
                    id: rectangle
                    width: scheduleText.width + 10
                    height: scheduleText.height
                    color: "#33AABB"
                    border.color: "#33AABB"
                    border.width: 1.5
                    radius: 10
                    anchors.verticalCenter: parent.verticalCenter
                    Text {
                        id: scheduleText
                        x: 5
                        anchors.centerIn: parent
                        font.pointSize: 12
                        font.bold: true
                        color:"#FFFFFF"
                        text: {
                            if(modelData.startsWith("★")) {
                                rectangle.color = "#333333"
                                rectangle.border.color = "#DDBB88"
                                scheduleText.text = modelData.substr(1);
                            }
                            else if(modelData.startsWith("@")) {
                                rectangle.color = "#BB3377"
                                rectangle.border.color = "#BB3377"
                                scheduleText.text = modelData.substr(1);
                            }
                            else {
                                rectangle.color = "#33AABB"
                                rectangle.border.color = "#33AABB"
                                scheduleText.text = modelData;
                            }
                        }
                    }
                    MouseArea {
                        width: parent.width
                        height: parent.height
                        onDoubleClicked: {
                            // 클릭한 사각형의 인덱스를 얻어서 list에서 remove 해주기
                            backgroundRect.getxIndex();
                            xIndex = index;
                            scheduler.removeTask(yIndex, xIndex); // 더블클릭된 사각형 삭제하고
                        }
                    }
                }
            }
        }
    }

    Connections {
        target: scheduler
        function onTasksChanged() {
            listView.model = scheduler.getTaskList(); // 화면에 보이는 리스트 갱신
        }
    }
}
