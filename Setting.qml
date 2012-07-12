// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Image {
    id: setting
    source: ":/picture/setting"

    width: 40
    height: 40

    x: parent.width/2 - 20
    y: 10

    smooth: true

    scale: settingMouse.pressed? 0.8 : 1.0

    MouseArea {
        id: settingMouse
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: mainAll.state = "shift"
    }
}
