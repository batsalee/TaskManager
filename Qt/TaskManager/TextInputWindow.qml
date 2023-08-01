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
        while(textInput.text[0] === '#' || textInput.text[0] === '@') {
            textInput.text = textInput.text.substr(1);
        } // 우선순위를 위해 #과 @를 사용했는데 이걸 추가하면 파싱이 꼬이므로 막아줌

        scheduler.addTask(textInput.text);
        textInputWindow.close();
    }
}
