// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Image {
    id: down
    source: ":/picture/down"

    width: 40
    height: 40

    x: parent.width/2 + 30
    y: 10

    smooth: true

    scale: downMouse.pressed? 0.8 : 1.0

    MouseArea {
        id: downMouse
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: Qt_fun.maskProgramm()
    }
}
