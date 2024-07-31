import QtQuick
import QtQuick.Controls 6.3
import QtQuick.Layouts 6.3

Column {       
    signal showInsertRect()
    Button {
        width: parent.width
        height: parent.height / 10
        text: qsTr("할일 추가")

        onClicked: {

            /*기능추가시 해당 함수만 남기고 나머지 지우면 됌*/
            // showInsertRect(); // 이 버튼을 누르면 showInsertRect 이벤트 발생



            // textinput 불러와서 작성한 내용 파일에 추가되게
            var component = Qt.createComponent("TextInputWindow.qml");
            if(component.status === Component.Ready) {
                var textInsertWindow = component.createObject();
                textInsertWindow.state = 0; // 0은 insert, 1은 update
                textInsertWindow.show();
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

    Button {
        width: parent.width
        height: parent.height / 10
        text: qsTr("제작자 정보")

        onClicked: {
            var component = Qt.createComponent("InformationWindow.qml");
            if(component.status === Component.Ready) {
                var textInputWindow = component.createObject();
                textInputWindow.show();
            }
        }
    }
}
