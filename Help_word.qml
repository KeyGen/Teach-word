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
            Qt_fun.helpButton("helphelp=",434, 237);
        }
    }

    MouseArea {
        id: help_wordMouse
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked:
        {
            if(showleftopacity.objectName == "show_1")
            {
                Qt_fun.wordHelpTest(showleftopacity.textShow)
            }

            else if(show1.objectName == "show_1")
            {
                Qt_fun.wordHelpTest(show1.textShow)
            }

            else if(show2.objectName == "show_1")
            {
                Qt_fun.wordHelpTest(show2.textShow)
            }

            else if(show3.objectName == "show_1")
            {
                Qt_fun.wordHelpTest(show3.textShow)
            }

            else if(showrightopacity.objectName == "show_1")
            {
                Qt_fun.wordHelpTest(showrightopacity.textShow)
            }

            else if(show5.objectName == "show_1")
            {
                Qt_fun.wordHelpTest(show5.textShow)
            }

            else if(show4.objectName == "show_1")
            {
                Qt_fun.wordHelpTest(show4.textShow)
            }

            else if(show6.objectName == "show_1")
            {
                Qt_fun.wordHelpTest(show6.textShow)
            }

            else if(show7.objectName == "show_1")
            {
                Qt_fun.wordHelpTest(show7.textShow)
            }

            Qt_fun.helpWord()
        }
    }
}
