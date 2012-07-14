// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Image {
    id: saveSetting
    source: ":/picture/saveSetting"

    width: 40
    height: 40

    x: parent.width - 60
    y: mainAll.height - 50

    smooth: true

    scale: saveSettingMouse.pressed? 0.8 : 1.0

    MouseArea {
        id: saveSettingMouse
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: mainAll.state = "normal"
    }
}
