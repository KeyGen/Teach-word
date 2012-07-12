// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle{
    id: button
    width: 190
    height: 30

    x: parent.width/2 - button.width/2
    y: 65

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#4c0000"}
        GradientStop { position: 0.5; color: "#df8c73"}
        GradientStop { position: 1.0; color: "#4c0000"}
    }

    smooth: true
    radius: 10
    border.width: 3
    border.color: "#4c0000"

    // Разрешаем доступ textButton
    property alias textButton: textButton.text
    Text {
        id: textButton
        text: "Общие настройки"
        font.pixelSize: 16

        anchors.verticalCenter: button.verticalCenter
        anchors.horizontalCenter: button.horizontalCenter
    }

    // Разрешаем доступ iconButton
    property alias iconButton: iconButton.source
    Image {
        id: iconButton
        source: ":/picture/setting"
        smooth: true

        width: 40
        height: 40

        y: -5
        x: -20
    }

    scale: buttonMouse.pressed? 0.8 : 1.0

    MouseArea {
        id: buttonMouse
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked:
        {
            console.log(textButton.text)

            if(textButton.text == "Общие натройки")
            mainAll.state = "shiftSetting"

            if(textButton.text == "О программе")
            mainAll.state = "shiftInfo"

            if(textButton.text == "Установка уроков")
            mainAll.state = "shiftinputLearnWords"
        }
    }
}
