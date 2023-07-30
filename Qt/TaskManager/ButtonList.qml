import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

Column {
    id: right_column

    Button {
        id: task_manage
        x: 0
        y: 0
        width:  parent.width
        height: parent.height / 10
        text: qsTr("일정 관리")

        onClicked: {
            var path = "/Schedule";
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
            var path = "/Schedule/long_term_goal";
            folder_opener.openFolder(path);
        }
    }
}
