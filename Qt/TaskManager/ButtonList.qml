import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

Column {
    Button {
        width:  parent.width
        height: parent.height / 10
        text: qsTr("할일 추가")

        onClicked: {
            // textinput 불러와서 작성한 내용 파일에 추가되게
            var component = Qt.createComponent("TextInputWindow.qml");
            if(component.status === Component.Ready) {
                var textInputWindow = component.createObject();
                textInputWindow.show();
            }
        }
    }

    Button {
        width: parent.width
        height: parent.height / 10
        text: qsTr("일정 관리")

        onClicked: folder_opener.openFolder("/Schedule")

    }

    Button {
        width: parent.width
        height: parent.height / 10
        text: qsTr("장기 계획")

        onClicked: folder_opener.openFolder("/Schedule/long_term_goal")
    }
}
