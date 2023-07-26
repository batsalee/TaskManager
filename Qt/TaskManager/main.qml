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
                                // 클릭한 사각형의 인덱스를 얻어서 list에서 remove 해주기
                                backgroundRect.getxIndex();
                                xIndex = index;
                                scheduler.removeTask(yIndex, xIndex);

                                //listView.model = scheduler.getTasks();
                                rectangle.visible = false;
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

            // 현재 수정중인 인덱스 문제와 같이 해결될듯함
        }

        Button {
            id: task_manage
            x: 0
            y: 0
            width:  parent.width
            height: parent.height / 10
            text: qsTr("일정 관리")

            onClicked: {
                var path = "file:///C:/workspace/Qt/build-TaskManager-Replacement_for_Desktop_x86_windows_msvc2022_pe_64bit-Debug/Schedule";
                folder_opener.openFolder(path);
            }
        }

        Button {
            id: long_term_goal
            x: 0
            y: 0
            width:  parent.width
            height: parent.height / 10
            text: qsTr("장기 계획")

            onClicked: {
                var path = "file:///C:/workspace/Qt/build-TaskManager-Replacement_for_Desktop_x86_windows_msvc2022_pe_64bit-Debug/Schedule/long_term_goal";
                folder_opener.openFolder(path);
            }
        }
    }
}
