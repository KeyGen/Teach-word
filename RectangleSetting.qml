// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle{
    id: recinfomain
    width: 560
    height: 0

    Rectangle {
        id: recinfoBackground
        width: 560
        height: 180

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
    }

    Image {
        id: iconPrBack
        source: ":/picture/globe128back"
        smooth: true

        width: 90
        height: 90

        y: 15
        x: 35
        z: 1
        scale: 0.86
    }

    Image {
        id: iconPrTwoBack
        source: ":/picture/music128back"
        smooth: true

        width: 90
        height: 90

        y: 15
        x: iconPr.x + iconPr.width + 20
        z: 1
        scale: 0.86
    }

    Image {
        id: iconPrThreeBack
        source: ":/picture/clock128back"
        smooth: true

        width: 90
        height: 90

        y: 15
        x: iconPrTwo.x + iconPrTwo.width + 20
        z: 1
        scale: 0.86
    }

    Image {
        id: iconPrFourBack
        source: ":/picture/ok128back"
        smooth: true

        width: 90
        height: 90

        y: 15
        x: iconPrThree.x + iconPrThree.width + 20
        z: 1
        scale: 0.86
    }

    Image {
        id: iconPrFiveBack
        source: ":/picture/refresh128back"
        smooth: true

        width: 90
        height: 90

        y: 15
        x: iconPrFour.x + iconPrFour.width + 20
        z: 1

        scale: 0.86
    }

    Image {
        id: iconPr
        //source: ":/picture/globe128"
        smooth: true

        width: 90
        height: 90

        y: 15
        x: 35
        z: 2

        state: "normaliconPr"

        states: [
            State {
                name: "normaliconPr"
                PropertyChanges {target: iconPr; source: ":/picture/globe128" }
            },
            State {
                name: "shifticonPr"
                PropertyChanges {target: iconPr; source: ":/picture/globe128false" }
            }
        ]

        transitions: Transition {
            PropertyAnimation { properties: "source"; duration: 400}
        }

        Behavior on opacity { PropertyAnimation {duration: 400} }

        Timer {
            id: timer
            interval: 400;
            onTriggered: iconPr.opacity = 1.0
        }

        scale: iconPrMouseArea.pressed? 0.87 : 1.0

        MouseArea {
            id: iconPrMouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked:
            {
                iconPr.opacity = 0.5
                timer.running = true

                iconPr.state = "normaliconPr"

                if(iconPrTwo.state == "normaliconPrTwo")
                {
                    timerTwo.running = true
                    iconPrTwo.opacity = 0.5
                    iconPrTwo.state = "shifticonPrTwo"
                }

                if(iconPrThree.state == "normaliconPrThree")
                {
                    timerThree.running = true
                    iconPrThree.opacity = 0.5
                    iconPrThree.state = "shifticonPrThree"
                }

                if(iconPrFour.state == "normaliconPrFour")
                {
                    timerFour.running = true
                    iconPrFour.opacity = 0.5
                    iconPrFour.state = "shifticonPrFour"
                }

                if(iconPrFive.state == "normaliconPrFive")
                {
                    timerFive.running = true
                    iconPrFive.opacity = 0.5
                    iconPrFive.state = "shifticonPrFive"
                }

                recinfoLanguage.state = "normalrecinfoLanguage"
                recinfoSound.state = "normalrecinforecinfoSound"
                recinfoTimer.state = "normalrecinforecinfoTimer"
                recinfoLearn.state = "normalrecinforecinfoLearn"
                recinfoRefresh.state = "normalrecinfoRefresh"
            }
        }
    }

    Image {
        id: iconPrTwo
        smooth: true

        width: 90
        height: 90

        y: 15
        x: iconPr.x + iconPr.width + 20
        z: 2

        state: "shifticonPrTwo"

        states: [
            State {
                name: "normaliconPrTwo"
                PropertyChanges {target: iconPrTwo; source: ":/picture/music128" }
            },
            State {
                name: "shifticonPrTwo"
                PropertyChanges {target: iconPrTwo; source: ":/picture/music128false" }
            }
        ]

        transitions: Transition {
            PropertyAnimation { properties: "source"; duration: 400}
        }

        Behavior on opacity { PropertyAnimation {duration: 400} }

        Timer {
            id: timerTwo
            interval: 400;
            onTriggered: iconPrTwo.opacity = 1.0
        }

        scale: iconPrTwoMouseArea.pressed? 0.87 : 1.0

        MouseArea {
            id: iconPrTwoMouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked:
            {
                iconPrTwo.opacity = 0.5
                timerTwo.running = true

                iconPrTwo.state = "normaliconPrTwo"

                if(iconPr.state == "normaliconPr")
                {
                    timer.running = true
                    iconPr.opacity = 0.5
                    iconPr.state = "shifticonPr"
                }

                if(iconPrThree.state == "normaliconPrThree")
                {
                    timerThree.running = true
                    iconPrThree.opacity = 0.5
                    iconPrThree.state = "shifticonPrThree"
                }

                if(iconPrFour.state == "normaliconPrFour")
                {
                    timerFour.running = true
                    iconPrFour.opacity = 0.5
                    iconPrFour.state = "shifticonPrFour"
                }

                if(iconPrFive.state == "normaliconPrFive")
                {
                    timerFive.running = true
                    iconPrFive.opacity = 0.5
                    iconPrFive.state = "shifticonPrFive"
                }

                recinfoLanguage.state = "shiftrecinfoLanguage"
                recinfoSound.state = "shiftrecinforecinfoSound"
                recinfoTimer.state = "normalrecinforecinfoTimer"
                recinfoLearn.state = "normalrecinforecinfoLearn"
                recinfoRefresh.state = "normalrecinfoRefresh"
            }
        }
    }

    Image {
        id: iconPrThree
        //source: ":/picture/clock128false"
        smooth: true

        width: 90
        height: 90

        y: 15
        x: iconPrTwo.x + iconPrTwo.width + 20
        z: 2

        state: "shifticonPrThree"

        states: [
            State {
                name: "normaliconPrThree"
                PropertyChanges {target: iconPrThree; source: ":/picture/clock128" }
            },
            State {
                name: "shifticonPrThree"
                PropertyChanges {target: iconPrThree; source: ":/picture/clock128false" }
            }
        ]

        transitions: Transition {
            PropertyAnimation { properties: "source"; duration: 400}
        }

        Behavior on opacity { PropertyAnimation {duration: 400} }

        Timer {
            id: timerThree
            interval: 400;
            onTriggered: iconPrThree.opacity = 1.0
        }

        scale: iconPrThreeMouseArea.pressed? 0.87 : 1.0

        MouseArea {
            id: iconPrThreeMouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onClicked:
            {
                iconPrThree.opacity = 0.5
                timerThree.running = true

                iconPrThree.state = "normaliconPrThree"

                if(iconPr.state == "normaliconPr")
                {
                    timer.running = true
                    iconPr.opacity = 0.5
                    iconPr.state = "shifticonPr"
                }

                if(iconPrTwo.state == "normaliconPrTwo")
                {
                    timerTwo.running = true
                    iconPrTwo.opacity = 0.5
                    iconPrTwo.state = "shifticonPrTwo"
                }

                if(iconPrFour.state == "normaliconPrFour")
                {
                    timerFour.running = true
                    iconPrFour.opacity = 0.5
                    iconPrFour.state = "shifticonPrFour"
                }

                if(iconPrFive.state == "normaliconPrFive")
                {
                    timerFive.running = true
                    iconPrFive.opacity = 0.5
                    iconPrFive.state = "shifticonPrFive"
                }

                recinfoLanguage.state = "shiftrecinfoLanguage"
                recinfoSound.state = "normalrecinforecinfoSound"
                recinfoTimer.state = "shiftrecinforecinfoTimer"
                recinfoLearn.state = "normalrecinforecinfoLearn"
                recinfoRefresh.state = "normalrecinfoRefresh"
            }
        }
    }

    Image {
        id: iconPrFour
        //source: ":/picture/ok128false"
        smooth: true

        width: 90
        height: 90

        y: 15
        x: iconPrThree.x + iconPrThree.width + 20
        z: 2

        state: "shifticonPrFour"

        states: [
            State {
                name: "normaliconPrFour"
                PropertyChanges {target: iconPrFour; source: ":/picture/ok128" }
            },
            State {
                name: "shifticonPrFour"
                PropertyChanges {target: iconPrFour; source: ":/picture/ok128false" }
            }
        ]

        transitions: Transition {
            PropertyAnimation { properties: "source"; duration: 400}
        }

        Behavior on opacity { PropertyAnimation {duration: 400} }

        Timer {
            id: timerFour
            interval: 400;
            onTriggered: iconPrFour.opacity = 1.0
        }

        scale: iconPrFourMouseArea.pressed? 0.87 : 1.0

        MouseArea {
            id: iconPrFourMouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked:
            {
                iconPrFour.opacity = 0.5
                timerFour.running = true

                iconPrFour.state = "normaliconPrFour"

                if(iconPr.state == "normaliconPr")
                {
                    timer.running = true
                    iconPr.opacity = 0.5
                    iconPr.state = "shifticonPr"
                }

                if(iconPrTwo.state == "normaliconPrTwo")
                {
                    timerTwo.running = true
                    iconPrTwo.opacity = 0.5
                    iconPrTwo.state = "shifticonPrTwo"
                }

                if(iconPrThree.state == "normaliconPrThree")
                {
                    timerThree.running = true
                    iconPrThree.opacity = 0.5
                    iconPrThree.state = "shifticonPrThree"
                }

                if(iconPrFive.state == "normaliconPrFive")
                {
                    timerFive.running = true
                    iconPrFive.opacity = 0.5
                    iconPrFive.state = "shifticonPrFive"
                }

                recinfoLanguage.state = "shiftrecinfoLanguage"
                recinfoSound.state = "normalrecinforecinfoSound"
                recinfoTimer.state = "normalrecinforecinfoTimer"
                recinfoLearn.state = "shiftrecinforecinfoLearn"
                recinfoRefresh.state = "normalrecinfoRefresh"

            }
        }
    }

    Image {
        id: iconPrFive
        smooth: true

        width: 90
        height: 90

        y: 15
        x: iconPrFour.x + iconPrFour.width + 20
        z: 2

        state: "shifticonPrFive"

        states: [
            State {
                name: "normaliconPrFive"
                PropertyChanges {target: iconPrFive; source: ":/picture/refresh128" }
            },
            State {
                name: "shifticonPrFive"
                PropertyChanges {target: iconPrFive; source: ":/picture/refresh128false" }
            }
        ]

        transitions: Transition {
            PropertyAnimation { properties: "source"; duration: 400}
        }

        Behavior on opacity { PropertyAnimation {duration: 400} }

        Timer {
            id: timerFive
            interval: 400;
            onTriggered: iconPrFive.opacity = 1.0
        }

        scale: iconPrFiveMouseArea.pressed? 0.87 : 1.0

        MouseArea {
            id: iconPrFiveMouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked:
            {
                iconPrFive.opacity = 0.5
                timerFive.running = true

                iconPrFive.state = "normaliconPrFive"

                if(iconPr.state == "normaliconPr")
                {
                    timer.running = true
                    iconPr.opacity = 0.5
                    iconPr.state = "shifticonPr"
                }

                if(iconPrTwo.state == "normaliconPrTwo")
                {
                    timerTwo.running = true
                    iconPrTwo.opacity = 0.5
                    iconPrTwo.state = "shifticonPrTwo"
                }

                if(iconPrThree.state == "normaliconPrThree")
                {
                    timerThree.running = true
                    iconPrThree.opacity = 0.5
                    iconPrThree.state = "shifticonPrThree"
                }

                if(iconPrFour.state == "normaliconPrFour")
                {
                    timerFour.running = true
                    iconPrFour.opacity = 0.5
                    iconPrFour.state = "shifticonPrFour"
                }

                recinfoLanguage.state = "shiftrecinfoLanguage"
                recinfoSound.state = "normalrecinforecinfoSound"
                recinfoTimer.state = "normalrecinforecinfoTimer"
                recinfoLearn.state = "normalrecinforecinfoLearn"
                recinfoRefresh.state = "shiftrecinfoRefresh"
            }
        }
    }

    Rectangle {
        id: recinfoLanguage
        width: 560
        height: 180

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

        state: "normalrecinfoLanguage"

        states: [
            State {
                name: "normalrecinfoLanguage"
                PropertyChanges {target: recinfoLanguage; opacity: 1.0 }
            },
            State {
                name: "shiftrecinfoLanguage"
                PropertyChanges {target: recinfoLanguage; opacity: 0.0 }
            }
        ]

        transitions: Transition {
            PropertyAnimation { properties: "opacity"; duration: 700}
        }

        Text {
            id: textInfoLanguage
            text:
    "<span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:14pt;\"><b>Установки языка</b></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:11pt;\">Выберите язык приложения, выбрав</span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:11pt;\"> пункт из выпадающего меню</span>"

            x: 230
            y: 30
        }
    }

    Rectangle {
        id: recinfoSound
        width: 560
        height: 180

        radius: 10
        smooth: true

        opacity: 0.0

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4c0000"}
            GradientStop { position: 0.5; color: "#df8c73"}
            GradientStop { position: 1.0; color: "#4c0000"}
        }

        y: 60
        x: 20

        border.width: 3
        border.color: "#080808"

        state: "normalrecinforecinfoSound"

        states: [
            State {
                name: "normalrecinforecinfoSound"
                PropertyChanges {target: recinfoSound; opacity: 0.0 }
            },
            State {
                name: "shiftrecinforecinfoSound"
                PropertyChanges {target: recinfoSound; opacity: 1.0 }
            }
        ]

        transitions: Transition {
            PropertyAnimation { properties: "opacity"; duration: 700}
        }

        Text {
            id: textInfoSound
            text:
    "<span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:14pt;\"><b>Установки звука</b></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:11pt;\">Здесь можно включить, выключить, звук</span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:11pt;\">приложения или отрегулировать громкость</span>"

            x: 230
            y: 30
        }
    }

    Rectangle {
        id: recinfoTimer
        width: 560
        height: 180

        radius: 10
        smooth: true

        opacity: 0.0

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4c0000"}
            GradientStop { position: 0.5; color: "#df8c73"}
            GradientStop { position: 1.0; color: "#4c0000"}
        }

        y: 60
        x: 20

        border.width: 3
        border.color: "#080808"

        state: "normalrecinforecinfoTimer"

        states: [
            State {
                name: "normalrecinforecinfoTimer"
                PropertyChanges {target: recinfoTimer; opacity: 0.0 }
            },
            State {
                name: "shiftrecinforecinfoTimer"
                PropertyChanges {target: recinfoTimer; opacity: 1.0 }
            }
        ]

        transitions: Transition {
            PropertyAnimation { properties: "opacity"; duration: 700}
        }

        Text {
            id: textInfoTimer
            text:
    "<span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:14pt;\"><b>Установки таймера</b></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:11pt;\">Таймер предназначен для отображение</span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:11pt;\">программы через заданное время</span>"

            x: 230
            y: 30
        }
    }

    Rectangle {
        id: recinfoLearn
        width: 560
        height: 180

        radius: 10
        smooth: true

        opacity: 0.0

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4c0000"}
            GradientStop { position: 0.5; color: "#df8c73"}
            GradientStop { position: 1.0; color: "#4c0000"}
        }

        y: 60
        x: 20

        border.width: 3
        border.color: "#080808"

        state: "normalrecinforecinfoLearn"

        states: [
            State {
                name: "normalrecinforecinfoLearn"
                PropertyChanges {target: recinfoLearn; opacity: 0.0 }
            },
            State {
                name: "shiftrecinforecinfoLearn"
                PropertyChanges {target: recinfoLearn; opacity: 1.0 }
            }
        ]

        transitions: Transition {
            PropertyAnimation { properties: "opacity"; duration: 700}
        }

        Text {
            id: textInfoLearn
            text:
    "<span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:14pt;\"><b>Установки статистики</b></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:11pt;\">Статистика правильных ответов. Установите</span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:11pt;\">позицию в статистике при которой слово</span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:11pt;\">будет считаться выучинным</span>"

            x: 230
            y: 30
        }
    }

    Rectangle {
        id: recinfoRefresh
        width: 560
        height: 180

        radius: 10
        smooth: true

        opacity: 0.0

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#4c0000"}
            GradientStop { position: 0.5; color: "#df8c73"}
            GradientStop { position: 1.0; color: "#4c0000"}
        }

        y: 60
        x: 20

        border.width: 3
        border.color: "#080808"

        state: "normalrecinfoRefresh"

        states: [
            State {
                name: "normalrecinfoRefresh"
                PropertyChanges {target: recinfoRefresh; opacity: 0.0 }
            },
            State {
                name: "shiftrecinfoRefresh"
                PropertyChanges {target: recinfoRefresh; opacity: 1.0 }
            }
        ]

        transitions: Transition {
            PropertyAnimation { properties: "opacity"; duration: 700}
        }

        Text {
            id: textInfoRecresh
            text:
    "<span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:14pt;\"><b>Проверка обновлений</b></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:11pt;\">Здесь вы можете проверить и установить</span>
    <span style=\" font-size:6pt;\">&#32;<br></span>
    <span style=\" font-size:11pt;\">обновления</span>"

            x: 230
            y: 30
        }
    }
}
