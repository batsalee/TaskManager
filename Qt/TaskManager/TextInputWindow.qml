import QtQuick
import QtQuick.Controls 6.3

Window {
    id: textInputWindow
    width: 300
    height: 100
    color: "#FFFFFF"
    title: "할일 추가"

    TextInput {
        id: textInput
        anchors.fill: parent
        anchors.margins: 5
        cursorVisible: true
        font.pointSize: 12
        color: "#000000"

        Keys.onEnterPressed: addTask()
        Keys.onReturnPressed: addTask()
        Keys.onEscapePressed: textInputWindow.close();
    }

    Component.onCompleted: {
        textInput.forceActiveFocus(); // 윈도우가 생성되면서 포커스를 설정하여 보여줌
    }

    function addTask() { 
        scheduler.addTask(textInput.text);
        textInputWindow.close();
        /*
            사용자입장에서의 제약
            1) 문장의 시작이 @ 혹은 #이면 @/#이 아닌 문자가 나올때까지 다 지워짐
            2) task중요도를 @와 #을 이용해 구현했기때문에 파싱이 꼬일것을 감안해서 제약을 둠
        */
    }
}
