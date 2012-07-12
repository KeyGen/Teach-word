// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle
{
    id: textRecInput
    width: 250
    height: 30
    radius: 10

    smooth: true
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#a3a3a3"}
        GradientStop { position: 0.5; color: "#d6d6d6"}
        GradientStop { position: 1.0; color: "#a3a3a3"}
    }

    border.width: 3
    border.color: "#494949"

    anchors.horizontalCenter: parent.horizontalCenter
    y: mainAll.height - 50

    TextInput {
        id: textInput

        width: 200
        x: 10

        text: "Hello world!"
        color: "black"
        font.pixelSize : 17
        cursorVisible: true
        activeFocusOnPress: true
        font.bold: true
        anchors.verticalCenter: textRecInput.verticalCenter
        selectByMouse: true
    }

    Help_word{}
}
