// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

//////////////////////////////////////
//////////////////// Кнопка редактирования словоря

Image {
    id: edit //Имя кнопки
    objectName: "edit_push"
    source: ":/icon/help"

    width: 50
    height: 50

    smooth: true
    rotation: -90

    scale: quitMouse.pressed ? 0.8 : 1.0
    //smooth: true

    MouseArea {
        id: quitMouse
        anchors.fill: parent
        anchors.margins: -10
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: Qt_fun.helpProgramm()
    }
}
