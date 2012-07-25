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
            if(setting.objectName == "show")
            Qt_fun.helpButton("Настойки",266, 35);
            else if(setting.objectName == "Settingrectagleinfo")
                Qt_fun.helpButton("Настойки",476, 208);
            else if(setting.objectName == "settingstartLearnWords")
                Qt_fun.helpButton("Перейти в настрйки",237, 231);
            else
            Qt_fun.helpButton("Настойки",426, 208);
        }
    }

    MouseArea {
        id: settingMouse
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: mainAll.state = "shift"
    }
}
