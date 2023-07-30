import QtQuick

Rectangle {
        id: clock
        color: "#555555"

        Text {
            id: dateTimeText
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
}

