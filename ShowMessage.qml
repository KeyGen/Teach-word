// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: message
    width: 600
    height: 300

    x: 300
    y: 300

    color: "red"

    Rectangle{
        id:  massegeBackground
        objectName: "massegeBackground"
        width: 600
        height: 300

        x: - 300
        y: - 300

        opacity: 0.0
        color: "grey"

        Behavior on opacity { PropertyAnimation {duration: 305; easing.type: Easing.InOutSine} }

        MouseArea {
            id: massegeBackgroundMouse
            anchors.fill: parent
            onClicked: Qt.LeftButton
            onPositionChanged: Qt_fun.move_window();
            onEntered: Qt_fun.cursor_up()
            onExited: Qt_fun.cursor_down()
        }
    }

    Rectangle{
        id:  crossV
        objectName: "crossV"
        width: 20
        height: 200

        x: -10
        y: -250
        opacity: 0.0

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4c0000"}
            GradientStop { position: 0.5; color: "#df8c73"}
            GradientStop { position: 1.0; color: "#4c0000"}
        }

        smooth: true

        Behavior on opacity { PropertyAnimation {duration: 50; easing.type: Easing.InOutSine} }
    }

    Rectangle{
        id:  crossH
        objectName: "crossH"
        width: 400
        height: 20

        x: -crossH.width/2
        y: message.height/2 - crossH.height/2 - 300

        opacity: 0.0

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#d28069"}
            GradientStop { position: 0.5; color: "#df8c73"}
            GradientStop { position: 1.0; color: "#d28069"}
        }

        smooth: true

        Behavior on opacity { PropertyAnimation {duration: 50; easing.type: Easing.InOutSine} }
    }

    Rectangle{
        id: recOne
        objectName: "recOne"
        width: 200
        height: 100

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4c0000"}
            GradientStop { position: 1.0; color: "#df8c73"}
        }

        smooth: true
        radius: 10

        state: "shift"

        states: [
            State {
                name: "normal"
                PropertyChanges {target: recOne; x: -recOne.width; y: -250; opacity: 1.0; }
            },
            State {
                name: "shift"
                PropertyChanges {target: recOne; x: - message.x - recOne.width; y: -40 - recOne.height -250; opacity: 0.0; }
            }
        ]

        Behavior on x { PropertyAnimation {duration: 305; easing.type: Easing.InCurve} }
        Behavior on y { PropertyAnimation {duration: 305; easing.type: Easing.InCurve} }
        Behavior on opacity { PropertyAnimation {duration: 305; easing.type: Easing.InCurve} }

    }

    Rectangle{
        id: recTwo
        objectName: "recTwo"
        width: recOne.width
        height: recOne.height

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4c0000"}
            GradientStop { position: 1.0; color: "#df8c73"}
        }

        smooth: true
        radius: 10

        state: "shift"

        states: [
            State {
                name: "normal"
                PropertyChanges {target: recTwo; x: 0; y: -250; opacity: 1.0; }
            },
            State {
                name: "shift"
                PropertyChanges {target: recTwo; x: 300; y: -40 - recOne.height -250; opacity: 0.0; }
            }
        ]

        Behavior on x { PropertyAnimation {duration: 305; easing.type: Easing.InCurve} }
        Behavior on y { PropertyAnimation {duration: 305; easing.type: Easing.InCurve} }
        Behavior on opacity { PropertyAnimation {duration: 305; easing.type: Easing.InCurve} }
    }

    Rectangle{
        id: recThree
        objectName: "recThree"
        width: recOne.width
        height: recOne.height

        gradient: Gradient {
            GradientStop { position: 1.0; color: "#4c0000"}
            GradientStop { position: 0.0; color: "#df8c73"}
        }

        smooth: true
        radius: 10

        state: "shift"

        states: [
            State {
                name: "normal"
                PropertyChanges {target: recThree; x: -recOne.width; y: recOne.height -250; opacity: 1.0; }
            },
            State {
                name: "shift"
                PropertyChanges {target: recThree; x: -message.x - recOne.width; y: 240 - 250; opacity: 0.0; }
            }
        ]

        Behavior on x { PropertyAnimation {duration: 305; easing.type: Easing.InCurve} }
        Behavior on y { PropertyAnimation {duration: 305; easing.type: Easing.InCurve} }
        Behavior on opacity { PropertyAnimation {duration: 305; easing.type: Easing.InCurve} }

    }

    Rectangle{
        id: recFour
        objectName: "recFour"
        width: recOne.width
        height: recOne.height

        gradient: Gradient {
            GradientStop { position: 1.0; color: "#4c0000"}
            GradientStop { position: 0.0; color: "#df8c73"}
        }

        smooth: true
        radius: 10

        state: "shift"

        states: [
            State {
                name: "normal"
                PropertyChanges {target: recFour; x: 0; y: recOne.height -250; opacity: 1.0; }
            },
            State {
                name: "shift"
                PropertyChanges {target: recFour; x: 300; y: 240 -250; opacity: 0.0; }
            }
        ]

        Behavior on x { PropertyAnimation {duration: 305; easing.type: Easing.InCurve} }
        Behavior on y { PropertyAnimation {duration: 305; easing.type: Easing.InCurve} }
        Behavior on opacity { PropertyAnimation {duration: 305; easing.type: Easing.InCurve} }

        Image {
            id: ok
            objectName: "yes"
            source: "/picture/yes"

            width: 40
            height: 40

            smooth: true

            y: recFour.height - ok.height - 5
            x: recFour.width - ok.width - 5

            scale: okMouse.pressed? 0.8 : 1.0

            MouseArea {
                id: okMouse
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                onClicked:
                {
                    recOne.state = "shift"

                    recTwo.state = "shift"

                    recThree.state = "shift"

                    recFour.state = "shift"

                    imageInfo.state = "shift"

                    messageText.state = "shift"

                    crossV.opacity = 0.0
                    crossH.opacity = 0.0
                    massegeBackground.opacity = 0.0

                    timerMessageTwo.running = true

                    if(message.objectName == "help")
                        Qt_fun.setVisibleQRadioButton(false);
                }
            }
        }

        Image {
            id: no
            objectName: "no"
            source: "/picture/quit"

            width: 40
            height: 40

            smooth: true

            y: recFour.height - ok.height - 5
            x: ok.x - ok.width - 5

            scale: noMouse.pressed? 0.8 : 1.0

            MouseArea {
                id: noMouse
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                onClicked:
                {
                    recOne.state = "shift"

                    recTwo.state = "shift"

                    recThree.state = "shift"

                    recFour.state = "shift"

                    imageInfo.state = "shift"

                    messageText.state = "shift"

                    crossV.opacity = 0.0
                    crossH.opacity = 0.0
                    massegeBackground.opacity = 0.0

                    timerMessageTwo.running = true

                    if(message.objectName == "help")
                        Qt_fun.setVisibleQRadioButton(false);
                }
            }
        }
    }

    property alias iconImageInfo: imageInfo.source
    Image {
        id: imageInfo
        objectName: "imageInfo"
        source: ":/picture/info128"

        width: 100
        height: 100

        x: -50
        y: -47 -250

        state: "shift"

        states: [
            State {
                name: "normal"
                PropertyChanges {target: imageInfo; opacity: 1.0; }
            },
            State {
                name: "shift"
                PropertyChanges {target: imageInfo; opacity: 0.0; }
            }
        ]

        Behavior on opacity { PropertyAnimation {duration: 50; easing.type: Easing.InOutSine} }
    }


    Text {
        id: messageText
        objectName: "messageText"

        color: "black"
        font.pixelSize: 16
        smooth: true

        x: -190
        y: 55 -250

        width: 380
        height: 140

        state: "shift"

        states: [
            State {
                name: "normal"
                PropertyChanges {target: messageText; opacity: 1.0; }
            },
            State {
                name: "shift"
                PropertyChanges {target: messageText; opacity: 0.0; }
            }
        ]

        Behavior on opacity { PropertyAnimation {duration: 50; easing.type: Easing.InOutSine} }
    }

    Timer {
        id: timerMessage
        objectName: "timerMessage"
        interval: 260
        onTriggered:
        {
            imageInfo.state = "normal"

            messageText.state = "normal"

            crossV.opacity = 1.0
            crossH.opacity = 1.0
        }
    }

    Timer {
        id: timerMessageTwo
        interval: 305
        onTriggered:
        {
            if(message.objectName != "help")
            Qt_fun.quit()
        }
    }
}
