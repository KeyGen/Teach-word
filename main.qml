// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle{
    id: mainAll

    width: 1200
    height: 300

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#404040"}
        GradientStop { position: 0.5; color: "#dcdcdc"}
        GradientStop { position: 1.0; color: "#404040"}
    }

    smooth: true

    state: "normal"

    states: [
        State {
            name: "normal"
            PropertyChanges {target: main; x:0;}
            PropertyChanges {target: setting; x:-600; }
        },
        State {
            name: "shift"
            PropertyChanges {target: main; x: -600; }
            PropertyChanges {target: setting; x: 0; }
        },
        State {
            name: "shiftSetting"
            PropertyChanges {target: inputSetting; x: 0}
            PropertyChanges {target: setting; x: -600}
            PropertyChanges {target: main; x: -600}
        }

    ]

    transitions: Transition {
        PropertyAnimation { properties: "x"; duration: 800; easing.type: Easing.InOutSine}
    }

    MouseArea {
        id: mainAllMouse
        anchors.fill: parent
        onClicked: Qt.LeftButton
        onPositionChanged: Qt_fun.move_window();
        onEntered: Qt_fun.cursor_up()
        onExited: Qt_fun.cursor_down()
    }


    Rectangle {
        id: main
        width: 600
        height: 0

        x: 600

        smooth: true

        Rectangle
        {
            id: show
            width: 0
            height: 0

            x: parent.width/2
            y: mainAll.height/2

            Show_words{
                id: show1
                objectName: "show1"

                z: -3

                y: show4.y - 30
                x: 60*1.7
                color: "white"

                width: show4.width/1.8
                height: show4.height/1.8
            }

            Show_words{
                id: show2
                objectName: "show2"

                z: -2

                y: show4.y - 20
                x: 40*1.5

                color: "magenta"

                width: show4.width/1.5
                height: show4.height/1.5
            }

            Show_words{
                id: show3
                objectName: "show3"

                z: -1
                y: show4.y - 10
                x: 20

                color: "blue"

                width: show4.width/1.3
                height: show4.height/1.3
            }

            Show_words{
                id: show4
                objectName: "show4"

                z: 0
            }

            Show_words{
                id: show5
                objectName: "show5"

                z: -1

                y: show4.y - 10
                x: -show5.width - 20

                color: "yellow"

                width: show4.width/1.3
                height: show4.height/1.3
            }

            Show_words{
                id: show6
                objectName: "show6"

                z: -2
                y: show4.y - 20
                x: -show5.width - 40/1.2

                color: "red"

                width: show4.width/1.5
                height: show4.height/1.5
            }

            Show_words{
                id: show7
                objectName: "show7"

                z: -3
                y: show4.y - 30
                x: -show5.width - 60 / 1.3

                width: show4.width/1.8
                height: show4.height/1.8
            }
        }

        TextInputQml{}

        Quit{}
        Down{}
        Setting{}
    }

    Rectangle{
        id: setting
        width: 600
        height: 0

        Image {
            id: backgruandButton
            source: ":/picture/backgruand"
            smooth: true
        }

        smooth: true

        Back{}

        Button_setting{}

        Button_setting{
            y:  139
        }

        Button_setting{
            y:  203
        }

    }

    Rectangle{
        id: inputSetting
        width: 600
        x: 600

        SaveSetting{}

        Back{
            x: parent.width - 100
            y: mainAll.height - 50
        }

        Setting{
            x: parent.width - 150
            y: mainAll.height - 50
        }
    }

}
