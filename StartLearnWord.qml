// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id:startLearnWords
    width: 600
    height: 300

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#404040"}
        GradientStop { position: 0.5; color: "#dcdcdc"}
        GradientStop { position: 1.0; color: "#404040"}
    }

    state: "normal"

    states: [
        State {
            name: "normal"
            PropertyChanges {target: startLearnWords; y:0; }
        },
        State {
            name: "shift"
            PropertyChanges {target: startLearnWords; y: -320}
        }
    ]

    Rectangle {
        id: startLearnWordsBackground
        width: 560
        height: 200

        radius: 10
        smooth: true
        opacity: 1.0

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4c0000"}
            GradientStop { position: 0.5; color: "#df8c73"}
            GradientStop { position: 1.0; color: "#4c0000"}
        }

        y: 60
        x: 20

        border.width: 3
        border.color: "#080808"


        Text {
            id: text
            text:
    "<center>
    <span style=\" font-size:16pt;\">&#32;<br></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:16pt;\"><b>Добро пожаловать в программу Learn words!</b></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:11pt;\">Выберите слова для обучения в настойках.</span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:11pt;\">И можно приступать к изучению.</span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    </center>"

            //anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    //<img src=\":/picture/setting\"> </img>

    Setting{
        objectName: "settingstartLearnWords"
        width: 60
        height: 60
        x: parent.width/2 - 30
        y: parent.width/2 - 115
    }
}
