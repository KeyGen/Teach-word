// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Image {
    id: quit
    source: ":/picture/quit"

    width: 40
    height: 40

    x: parent.width/2 - 70
    y: 10

    smooth: true

    scale: quitMouse.pressed? 0.8 : 1.0

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
            Qt_fun.helpButton("Выйти",176, 2);
        }
    }

    MouseArea {
        id: quitMouse
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: Qt_fun.quit()
    }
}
