// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle{
    id: button
    width: 300
    height: 40

    x: parent.width/2 - button.width/2
    y: 75

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#4c0000"}
        GradientStop { position: 0.5; color: "#df8c73"}
        GradientStop { position: 1.0; color: "#4c0000"}
    }

    smooth: true
    radius: 10
    border.width: 4
    border.color: "#4c0000"

    Text {
        id: textButton
        text: "Общие настройки"
        font.pixelSize: 20

        anchors.verticalCenter: button.verticalCenter
        anchors.horizontalCenter: button.horizontalCenter
    }

    Image {
        id: iconButton
        source: ":/picture/setting"
        smooth: true

        y: -12
        x: parent.width - 32
    }

    scale: buttonMouse.pressed? 0.8 : 1.0

    MouseArea {
        id: buttonMouse
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: mainAll.state = "shiftSetting"
    }
}
