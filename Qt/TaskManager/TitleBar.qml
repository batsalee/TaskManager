import QtQuick
import QtQuick.Controls 6.3

Rectangle {
    id: clock
    x: 0
    y: 0
    color: "#555555"

    MouseArea {
        /* FramelessWindow를 만들되 창은 움직일 수 있어야 하므로
           타이틀바 쪽을 잡고 드래그하면 창을 옮길 수 있음
        */
        width: parent.width * 0.85
        height: 30
        onPressed: {
            mainWindow.startSystemMove();
        }
        onDoubleClicked:  {
            if (mainWindow.visibility === Window.Windowed) mainWindow.visibility = Window.Maximized;
            else mainWindow.visibility = Window.Windowed;
        }
    }

    Text {
        id: dateTimeText
        x: 0
        y: 0
        width: parent.width * 0.85
        height: 30
        text: getCurrentDateTime()
        padding: 5
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: 12
        color: "#888888"
        font.bold: true

        Timer {
            interval: 1000 // 1 second
            repeat: true
            running: true
            onTriggered: {
                dateTimeText.text = getCurrentDateTime();
            }
        }
    }

    function getCurrentDateTime() {
        var currentDate = new Date();
        var year = currentDate.getFullYear();
        var month = ("0" + (currentDate.getMonth() + 1)).slice(-2);
        var day = ("0" + currentDate.getDate()).slice(-2);
        var hours = ("0" + currentDate.getHours()).slice(-2);
        var minutes = ("0" + currentDate.getMinutes()).slice(-2);
        var seconds = ("0" + currentDate.getSeconds()).slice(-2);
        var days = ["일요일", "월요일", "화요일", "수요일", "목요일", "금요일", "토요일"];
        var dayOfWeek = days[currentDate.getDay()];

        return year + "-" + month + "-" + day + " " + dayOfWeek + " " + hours + ":" + minutes + ":" + seconds;
    }

    Row {
        x: parent.width * 0.85
        y: 0
        width: parent.width * 0.15
        height: 30

        Rectangle {
            id: minimize
            width: parent.width / 3
            height: parent.height
            color: "transparent"

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 10
                color: "#FFFFFF"
                text: qsTr("__")
            }

            MouseArea {                
                hoverEnabled: true
                anchors.fill: parent

                onClicked: {
                    mainWindow.visibility = Window.Minimized;
                }
                onEntered: {
                    minimize.color = "#777777"
                }
                onExited: {
                    minimize.color = "transparent"
                }
            }
        }

        Rectangle {
            id: maximize
            width: parent.width / 3
            height: parent.height
            color: "transparent"

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 10
                color: "#FFFFFF"
                text: qsTr("□")
            }

            MouseArea {                
                hoverEnabled: true
                anchors.fill: parent

                onClicked: {
                    if (mainWindow.visibility === Window.Windowed) mainWindow.visibility = Window.Maximized;
                    else mainWindow.visibility = Window.Windowed;
                }
                onEntered: {
                    maximize.color = "#777777"
                }
                onExited: {
                    maximize.color = "transparent"
                }
            }
        }

        Rectangle {
            id: quit
            width: parent.width / 3
            height: parent.height
            color: "transparent"

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 11
                color: "#FFFFFF"
                text: qsTr("⨉")
            }

            MouseArea {
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    mainWindow.close();
                }

                onEntered: {
                    quit.color = "#777777"
                }

                onExited: {
                    quit.color = "transparent"
                }
            }
        }
    }
}
