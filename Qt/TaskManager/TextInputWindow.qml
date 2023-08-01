import QtQuick
import QtQuick.Controls 6.3

Window {
    id: textinputwindow
    width: 300
    height: 100
    color: "#FFFFFF"
    title: "할일 추가"

    TextInput {
        id: textinput
        anchors.fill: parent
        anchors.margins: 5
        cursorVisible: true
        font.pointSize: 12
        color: "#000000"

        Keys.onEnterPressed: {
            scheduler.addTask(textinput.text);
            textinputwindow.close();
        }

        Keys.onReturnPressed: {
            scheduler.addTask(textinput.text);
            textinputwindow.close();
        }

        Keys.onEscapePressed: {
            textinputwindow.close();
        }
    }

    Component.onCompleted: {
        textinput.forceActiveFocus(); // 윈도우가 생성되면서 포커스를 설정하여 보여줌
    }
}
