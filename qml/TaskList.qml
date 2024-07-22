import QtQuick
import QtQuick.Layouts 6.3

ListView {
    id: listView
    clip: true
    model: scheduler.schedule_list
    boundsBehavior: Flickable.StopAtBounds

    property int scroll_height // 스크롤된 상태에서 더블클릭으로 지울때 contentY가 유지되도록 하기 위해

    delegate: Rectangle {
        id: backgroundRect
        x: 0
        y: 0
        width: listView.width
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
                    border.width: 1.5
                    radius: 10
                    anchors.verticalCenter: parent.verticalCenter
                    Text {
                        id: scheduleText
                        x: 5
                        anchors.centerIn: parent
                        font.pointSize: 12
                        font.bold: true
                        text: {
                            if(modelData.startsWith("★")) {
                                rectangle.color = "#333333"
                                rectangle.border.color = "#DDBB88"
                                scheduleText.text = modelData
                                scheduleText.color = "#DDBB88"
                            }
                            else if(modelData.startsWith("@")) {
                                rectangle.color = "#BB3377"
                                rectangle.border.color = "#BB3377"
                                scheduleText.text = modelData.substr(1);
                                scheduleText.color = "#AAAAAA"
                            }
                            else {
                                rectangle.color = "#33AABB"
                                rectangle.border.color = "#33AABB"
                                scheduleText.text = modelData;
                                scheduleText.color = "#FFFFFF"
                            }
                        }
                    }
                    MouseArea {
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        width: parent.width
                        height: parent.height
                        onDoubleClicked: {
                            listView.scroll_height = contentY; // 스크롤된 상태에서 더블클릭으로 지울때 contentY가 유지되도록 하기 위해

                            // 클릭한 사각형의 인덱스를 얻어서 list에서 remove 해주기
                            backgroundRect.getxIndex();
                            xIndex = index;
                            scheduler.deleteTask(yIndex, xIndex); // 더블클릭된 사각형 삭제하고
                        }

                        onClicked: {
                            listView.scroll_height = contentY; // 스크롤된 상태에서 변경시 contentY가 유지되도록 하기 위해

                            if (mouse.button === Qt.RightButton) {
                                var component = Qt.createComponent("TextInputWindow.qml");
                                if(component.status === Component.Ready) {
                                    var taskUpdateWindow = component.createObject();

                                    backgroundRect.getxIndex();
                                    taskUpdateWindow.y = yIndex;
                                    taskUpdateWindow.x = index;
                                    taskUpdateWindow.state = 1; // 0은 insert, 1은 update
                                    taskUpdateWindow.show();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Connections {
        target: scheduler

        function onTasksChanged() { // 할일 삭제 및 변경시 현재 스크롤 상태 유지하면서 값 갱신
            listView.model = scheduler.getTaskList(); // 화면에 보이는 리스트 갱신

            if(listView.model.length * 30 >= mainWindow.height - 30)
                listView.contentY = listView.scroll_height;
            else
                listView.contentY = 0;
        }

        function onTasksInserted() { // 할일 추가시 스크롤 가장 아래로 내리면서 값 추가
            listView.model = scheduler.getTaskList(); // 화면에 보이는 리스트 갱신

            listView.contentY = (listView.model.length * 30) - (mainWindow.height - 30);
        }
    }
}
