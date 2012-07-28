// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Image {
    id: quit
    source: ":/picture/back"

    width: 40
    height: 40

    x: parent.width/2 - 20
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
            if(quit.objectName == "setting")
                Qt_fun.helpButton("helpback=",276, 35);
            else if(quit.objectName == "Backrectagleinfo")
                Qt_fun.helpButton("helpback=",536, 208);
            else
                Qt_fun.helpButton("helpback=",486, 208);
        }
    }

    MouseArea {
        id: quitMouse
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {

            if(quit.objectName == "inputLearnWordsBack")
            {
                var temp = Qt_fun.controlSize()

                if(temp == 0)
                {
                    mainAll.state = "normal"
                    start.state = "normal"
                }
                else if(temp == 1)
                {
                    mainAll.state = "normal"
                    start.state = "shift"
                    Qt_fun.setShowOnDefault()
                }
                else if(temp == 2)
                {
                    Qt_fun.showMassage("infominimumsize=", "true")
                }
            }
            else
            {
                mainAll.state = "normal"
            }
        }
    }
}
