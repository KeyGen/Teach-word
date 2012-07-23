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
        },
        State {
            name: "shiftInfo"
            PropertyChanges {target: rectagleinfo; x: 0}
            PropertyChanges {target: setting; x: -600}
            PropertyChanges {target: main; x: -600}
        },
        State {
            name: "shiftinputLearnWords"
            PropertyChanges {target: inputLearnWords; x: 0}
            PropertyChanges {target: setting; x: -600}
            PropertyChanges {target: main; x: -600}
        }

    ]

    transitions: Transition {
        PropertyAnimation { properties: "x"; duration: 500; easing.type: Easing.InOutSine }
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

//        Image {
//            id: mainbackground
//            source: ":/picture/mainbackground"

//            y: -24
//        }

        Rectangle
        {
            id: show
            width: 0
            height: 0

            x: parent.width/2
            y: mainAll.height/2

            Show_words{
                id: showleftopacity
                objectName: "show_5"

                z: -4
                x: 97
                y: -170

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#00358c"}
                    GradientStop { position: 0.5; color: "#00c7e6"}
                    GradientStop { position: 1.0; color: "#00358c"}
                }

                scale: 0.3

                textShow: "show_5"

                opacity: 0.0

            }

            Show_words{
                id: show1
                objectName: "show_4"

                z: -3

                y: -153
                x: 72

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#5f005e"}
                    GradientStop { position: 0.5; color: "#ff00fc"}
                    GradientStop { position: 1.0; color: "#5f005e"}
                }

                scale: 0.4

                textShow: "show_4"

            }

            Show_words{
                id: show2
                objectName: "show_3"

                z: -2

                y: -128
                x: 30

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#0e6600"}
                    GradientStop { position: 0.5; color: "#24ff00"}
                    GradientStop { position: 1.0; color: "#0e6600"}
                }

                scale: 0.6

                textShow: "show_3"
            }

            Show_words{
                id: show3
                objectName: "show_2"

                z: -1
                x: -280 + 20 + show3.width*0.8
                y: -100

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#005c71"}
                    GradientStop { position: 0.5; color: "#00cfff"}
                    GradientStop { position: 1.0; color: "#005c71"}
                }

                scale: 0.8

                textShow: "show_2"
            }

            Show_words{
                id: show4
                objectName: "show_1"

                textShow: "show_1"

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#00562c"}
                    GradientStop { position: 0.5; color: "#00dc71"}
                    GradientStop { position: 1.0; color: "#00562c"}
                }

                scale: 1.0

                z: 0
            }

            Show_words{
                id: show5
                objectName: "show_9"

                z: -1
                x: -40 + ((show5.width)*-1)*0.8
                y: -100

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#007a25"}
                    GradientStop { position: 0.5; color: "#00ff4e"}
                    GradientStop { position: 1.0; color: "#007a25"}
                }

                scale: 0.8

                textShow: "show_9"

                opacity: 0.01
            }

            Show_words{
                id: show6
                objectName: "show_8"

                z: -2
                x: -332
                y: -128

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#625800"}
                    GradientStop { position: 0.5; color: "#ffe500"}
                    GradientStop { position: 1.0; color: "#625800"}
                }

                scale: 0.6

                textShow: "show_8"

                opacity: 0.01
            }

            Show_words{
                id: show7
                objectName: "show_7"

                z: -3
                x: -374
                y: -153

                scale: 0.4

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#2e5a00"}
                    GradientStop { position: 0.5; color: "#84ff00"}
                    GradientStop { position: 1.0; color: "#2e5a00"}
                }

                textShow: "show_7"

                opacity: 0.01
            }

            Show_words{
                id: showrightopacity
                objectName: "show_6"

                z: -4
                x: -400
                y: -170

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#833e00"}
                    GradientStop { position: 0.5; color: "#ffa555"}
                    GradientStop { position: 1.0; color: "#833e00"}
                }

                scale: 0.3

                textShow: "show6"

                opacity: 0.0

            }

        }

        TextInputQml{}

        Quit{}
        Down{}
        Setting{
            objectName: "show"
        }
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

        Image {
            id: backgruandButtonTwo
            source: ":/picture/backgruandTwo"
            smooth: true

            x: setting.width - 190
            y: 20
        }

        smooth: true

        Back{
            objectName: "setting"
        }

        Button_setting{
            id: settingButton
            textButton: "Общие натройки"
        }

        Button_setting{
            id: learnButton
            textButton: "Установка уроков"
            iconButton: ":/picture/learn"
            y:  settingButton.y + 55
        }

        Button_setting{
            id: helpButton
            textButton: "Справка"
            iconButton: ":/picture/help"
            y:  learnButton.y + 55
        }

        Button_setting{
            id: infoButton
            textButton: "О программе"
            iconButton: ":/picture/info"
            y:  helpButton.y + 55
        }

    }

    Rectangle{
        id: inputSetting
        width: 600
        x: 600

        SaveSetting{}

        Back{
            objectName: "inputSetting"
            x: parent.width - 110
            y: mainAll.height - 50
        }

        Setting{
            objectName: "inputSetting"
            x: parent.width - 160
            y: mainAll.height - 50
        }

        RectangleSetting{}

        onXChanged: Qt_fun.moveSetup(inputSetting.x)
    }

    Rectangle{
        id: rectagleinfo
        width: 600
        x: 600

        RectagleInfo{}

        Back{
            objectName: "Backrectagleinfo"
            x: parent.width - 60
            y: mainAll.height - 50
        }

        Setting{
            objectName: "Settingrectagleinfo"
            x: parent.width - 110
            y: mainAll.height - 50
        }
    }

    Rectangle{
        id: inputLearnWords
        width: 600
        x: 600

        SaveSetting{
            x: parent.width - 60
        }

        Back{
            x: parent.width - 110
            y: mainAll.height - 50
        }

        Setting{
            x: parent.width - 160
            y: mainAll.height - 50
        }

       Rectangle{
            width: 560
            height: 215

            radius: 10
            smooth: true
            opacity: 1.0

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#4c0000"}
                GradientStop { position: 0.5; color: "#df8c73"}
                GradientStop { position: 1.0; color: "#4c0000"}
            }

            y: 30
            x: 20

            border.width: 3
            border.color: "#080808"

            Image {
                id: helpAmount
                source: ":/picture/help30"

                width: 40
                height: 40

                x: 11
                y: -20

                smooth: true

                scale: helpAmountMouse.pressed? 0.8 : 1.0

                MouseArea {
                    id: helpAmountMouse
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onPressed:
                    {
                        Qt_fun.showMassage("<br>Это отображение статистики.<br><br>Фиксирует правильные ответы.", "true")
                    }
                }
            }

            Image {
                id: helpLearnWord
                source: ":/picture/help30"

                width: 40
                height: 40

                x: 124
                y: -20

                smooth: true

                scale: helpLearnWordMouse.pressed? 0.8 : 1.0

                MouseArea {
                    id: helpLearnWordMouse
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onPressed:
                    {
                        Qt_fun.showMassage("<br>Отображение слов которые будем учить<br><br>Добавте слова и можно начинать урок", "true")
                    }
                }
            }

            Image {
                id: trash_fullLearnWord
                source: ":/picture/trash_full"

                width: 40
                height: 40

                x: helpLearnWord.x + helpLearnWord.width + 10
                y: helpLearnWord.y

                smooth: true

                scale: trash_fullLearnWordMouse.pressed? 0.8 : 1.0

                MouseArea {
                    id: trash_fullLearnWordhelpMouse
                    anchors.fill: parent

                    hoverEnabled: true
                    onEntered:
                    {
                        trash_fullLearnWordtimerhelpshow.running = true
                    }
                    onExited:
                    {
                        trash_fullLearnWordtimerhelpshow.running = false
                    }
                }

                Timer {
                    id: trash_fullLearnWordtimerhelpshow
                    interval: 1000
                    onTriggered:
                    {
                        Qt_fun.helpButton("Очистить базу слов для обучения",206, 35);
                    }
                }

                MouseArea {
                    id: trash_fullLearnWordMouse
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                    onClicked: Qt_fun.clearLearnWords()
                }
            }

            Image {
                id: helpBase
                source: ":/picture/help30"

                width: 40
                height: 40

                x: 366
                y: -20

                smooth: true

                scale: helpBaseWordMouse.pressed? 0.8 : 1.0

                MouseArea {
                    id: helpBaseWordMouse
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onPressed:
                    {
                        Qt_fun.showMassage("<br><b>Базовый словарь</b><br><br>Cловари из которых будем учить слова", "true")
                    }
                }
            }

            Image {
                id: helpBase_transfer
                source: ":/picture/rotate"

                width: 40
                height: 40

                x: helpBase.x + helpBase_transfer.width + 10
                y: -20

                smooth: true

                scale: helpBase_transferMouse.pressed? 0.8 : 1.0

                MouseArea {
                    id: helpBase_transferhelpMouse
                    anchors.fill: parent

                    hoverEnabled: true
                    onEntered:
                    {
                        helpBase_transfertimerhelpshow.running = true
                    }
                    onExited:
                    {
                        helpBase_transfertimerhelpshow.running = false
                    }
                }

                Timer {
                    id: helpBase_transfertimerhelpshow
                    interval: 1000
                    onTriggered:
                    {
                        Qt_fun.helpButton("Отобразить/скрыть перевод",450, 35);
                    }
                }

                MouseArea {
                    id: helpBase_transferMouse
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                    onClicked: Qt_fun.setVisibleObjectLernWord()
                }
            }

            Image {
                id: languageBase
                source: ":/picture/globe"

                width: 40
                height: 40

                x: helpBase_transfer.x + languageBase.width + 10
                y: helpBase.y

                smooth: true

                scale: languageBaseMouse.pressed? 0.8 : 1.0

                MouseArea {
                    id: languageBasehelpMouse
                    anchors.fill: parent

                    hoverEnabled: true
                    onEntered:
                    {
                        languageBasetimerhelpshow.running = true
                    }
                    onExited:
                    {
                        languageBasetimerhelpshow.running = false
                    }
                }

                Timer {
                    id: languageBasetimerhelpshow
                    interval: 1000
                    onTriggered:
                    {
                        Qt_fun.helpButton("Выбор словаря",500, 35);
                    }
                }

                MouseArea {
                    id: languageBaseMouse
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: {
                        Qt_fun.showObjectdicInputanddicInfo()
                    }
                }
            }

            Image {
                id: right
                source: ":/picture/right"

                width: 40
                height: 40

                x: 283
                y: 117

                smooth: true

                scale: rightMouse.pressed? 0.8 : 1.0

                MouseArea {
                    id: righthelpMouse
                    anchors.fill: parent

                    hoverEnabled: true
                    onEntered:
                    {
                        righttimerhelpshow.running = true
                    }
                    onExited:
                    {
                        righttimerhelpshow.running = false
                    }
                }

                Timer {
                    id: righttimerhelpshow
                    interval: 1000
                    onTriggered:
                    {
                        Qt_fun.helpButton("Убрать слово",277, 175);
                    }
                }

                MouseArea {
                    id: rightMouse
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onPressed: Qt_fun.deleteWord()
                }
            }

            Image {
                id: left
                source: ":/picture/left"

                width: 40
                height: 40

                x: right.x
                y: right.y - 50

                smooth: true

                scale: leftMouse.pressed? 0.8 : 1.0

                MouseArea {
                    id: lefthelpMouse
                    anchors.fill: parent

                    hoverEnabled: true
                    onEntered:
                    {
                        lefttimerhelpshow.running = true
                    }
                    onExited:
                    {
                        lefttimerhelpshow.running = false
                    }
                }

                Timer {
                    id: lefttimerhelpshow
                    interval: 1000
                    onTriggered:
                    {
                        Qt_fun.helpButton("Добавить слово",271, 53);
                    }
                }

                MouseArea {
                    id: leftMouse
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onPressed: Qt_fun.addLearnWords()
                }
            }
       }

        onXChanged: Qt_fun.moveInputWords(inputLearnWords.x)
    }
}
