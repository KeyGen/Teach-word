// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Image {
    id: help_word
    source: ":/picture/help_word"

    width: 40
    height: 40

    x: parent.width - 35
    y: -5

    smooth: true

    scale: help_wordMouse.pressed? 0.9 : 1.0

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
            Qt_fun.helpButton("Подсказать",434, 237);
        }
    }

    MouseArea {
        id: help_wordMouse
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked:
        {
            //Qt_fun.showMassage("<br>Скоро будет готава подсказка!<br><br>Цетр отредактирован :)")
            Qt_fun.helpWord()
        }
    }
}
