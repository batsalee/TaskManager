import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

Column {
    id: right_column

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
