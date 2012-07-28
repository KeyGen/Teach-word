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
            Qt_fun.helpButton("helpsave=",522, 208);
        }
    }

    MouseArea {
        id: saveSettingMouse
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: mainAll.state = "normal"
    }
}
