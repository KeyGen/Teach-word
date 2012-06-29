import QtQuick 1.1

//////////////////////////////////////
//////////////////// Кнопка редактирования словоря

Image {
    id: edit //Имя кнопки
    objectName: "edit_push"
    source: ":/icon/edit"

    width: 41
    height: 41

    x: 4.5

    scale: quitMouse.pressed ? 0.8 : 1.0
    smooth: true
    rotation: -90

    MouseArea {
        id: quitMouse
        anchors.fill: parent
        anchors.margins: -10
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: Qt_fun.exec_dialog_input()
    }
}
