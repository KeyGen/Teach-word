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
        id: helpMouse
        anchors.fill: parent

        hoverEnabled: true
        onEntered:
        {
            timerhelpshow.running = true
        }
        onExited:
        {
            timerhelpshow.running = false
        }
    }

    Timer {
        id: timerhelpshow
        interval: 1000
        onTriggered:
        {
            Qt_fun.helpButton("helpmask=",373, 2);
        }
    }

    MouseArea {
        id: downMouse
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: Qt_fun.maskProgramm()
    }
}
