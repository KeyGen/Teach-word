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

    property alias textInput: textInput.text
    TextInput {
        id: textInput
        objectName: "textInput"

        width: 200
        x: 10
        focus: true

        text: ""
        color: "black"
        font.pixelSize : 17
        cursorVisible: true
        activeFocusOnPress: true
        font.bold: true
        anchors.verticalCenter: textRecInput.verticalCenter
        selectByMouse: true

        Timer {
            id: timerFocus
            interval: 600;
            onTriggered:
            {
                if(show4.objectName=="show_1" && show5.objectName == "show_1")
                {
                    showleftopacity.objectName = "show_5"
                    show1.objectName = "show_4"
                    show2.objectName = "show_3"
                    show3.objectName = "show_2"
                    show4.objectName = "show_1"
                    show5.objectName = "show_9"
                    show6.objectName = "show_8"
                    show7.objectName = "show_7"
                    showrightopacity.objectName = "show_6"

                    showleftopacity.z = -4
                    show1.z = -3
                    show2.z = -2
                    show3.z = -1
                    show4.z = 0
                    show5.z = -1
                    show6.z = -2
                    show7.z = -3
                    showrightopacity.z = -4

                    showleftopacity.scale = 0.3
                    show1.scale = 0.4
                    show2.scale = 0.6
                    show3.scale = 0.8
                    show4.scale = 1.0
                    show5.scale = 0.8
                    show6.scale = 0.6
                    show7.scale = 0.4
                    showrightopacity.scale = 0.3

                    show5.x = show6.x
                    show5.y = show6.y
                    show5.opacity = show6.opacity

                    show6.x = show7.x
                    show6.y = show7.y
                    show6.opacity = show7.opacity

                    show7.x = showrightopacity.x
                    show7.y = showrightopacity.y
                    show7.opacity = showrightopacity.opacity

                    showrightopacity.x = showleftopacity.x
                    showrightopacity.y = showleftopacity.y
                    showrightopacity.opacity = showleftopacity.opacity

                    showleftopacity.x = show1.x
                    showleftopacity.y = show1.y
                    showleftopacity.opacity = show1.opacity

                    show1.x = show2.x
                    show1.y = show2.y
                    show1.opacity = show2.opacity

                    show2.x = show3.x
                    show2.y = show3.y
                    show2.opacity = show3.opacity

                    show3.x = show4.x
                    show3.y = show4.y
                    show3.opacity = show4.opacity

                    show4.x = show5.x
                    show4.y = show5.y
                    show4.opacity = show5.opacity
                }
                else
                {
                    show5.x = show6.x
                    show5.y = show6.y
                    show5.scale = show6.scale
                    show5.opacity = show6.opacity
                    show5.objectName = show6.objectName

                    show6.x = show7.x
                    show6.y = show7.y
                    show6.scale = show7.scale
                    show6.opacity = show7.opacity
                    show6.objectName = show7.objectName

                    show7.x = showrightopacity.x
                    show7.y = showrightopacity.y
                    show7.scale = showrightopacity.scale
                    show7.opacity = showrightopacity.opacity
                    show7.objectName = showrightopacity.objectName

                    showrightopacity.x = showleftopacity.x
                    showrightopacity.y = showleftopacity.y
                    showrightopacity.scale = showleftopacity.scale
                    showrightopacity.opacity = showleftopacity.opacity
                    showrightopacity.objectName = showleftopacity.objectName

                    showleftopacity.x = show1.x
                    showleftopacity.y = show1.y
                    showleftopacity.scale = show1.scale
                    showleftopacity.opacity = show1.opacity
                    showleftopacity.objectName = show1.objectName

                    show1.x = show2.x
                    show1.y = show2.y
                    show1.scale = show2.scale
                    show1.opacity = show2.opacity
                    show1.objectName = show2.objectName

                    show2.x = show3.x
                    show2.y = show3.y
                    show2.scale = show3.scale
                    show2.opacity = show3.opacity
                    show2.objectName = show3.objectName

                    show3.x = show4.x
                    show3.y = show4.y
                    show3.scale = show4.scale
                    show3.opacity = show4.opacity
                    show3.objectName = show4.objectName

                    show4.x = show5.x
                    show4.y = show5.y
                    show4.scale = show5.scale
                    if(show5.opacity != 0.01)
                    show4.opacity = show5.opacity
                    show4.objectName = show5.objectName

                    if(showleftopacity.objectName == "show_1")
                    {
                        showleftopacity.z = -0
                        show1.z = -1
                        show2.z = -2
                        show3.z = -3
                        show4.z = -4
                        show5.z = -4
                        show6.z = -3
                        show7.z = -2
                        showrightopacity.z = -1
                    }

                    if(show1.objectName == "show_1")
                    {
                        showleftopacity.z = -1
                        show1.z = 0
                        show2.z = -1
                        show3.z = -2
                        show4.z = -3
                        show5.z = -4
                        show6.z = -4
                        show7.z = -3
                        showrightopacity.z = -2
                    }

                    if(show2.objectName == "show_1")
                    {
                        showleftopacity.z = -2
                        show1.z = -1
                        show2.z = 0
                        show3.z = -1
                        show4.z = -2
                        show5.z = -3
                        show6.z = -4
                        show7.z = -4
                        showrightopacity.z = -3
                    }

                    if(show3.objectName == "show_1")
                    {
                        showleftopacity.z = -3
                        show1.z = -2
                        show2.z = -1
                        show3.z = 0
                        show4.z = -1
                        show5.z = -2
                        show6.z = -3
                        show7.z = -4
                        showrightopacity.z = -4
                    }

                    if(show4.objectName == "show_1")
                    {
                        showleftopacity.z = -4
                        show1.z = -3
                        show2.z = -2
                        show3.z = -1
                        show4.z = 0
                        show5.z = -1
                        show6.z = -2
                        show7.z = -3
                        showrightopacity.z = -4
                    }

                    if(show5.objectName == "show_1")
                    {
                        showleftopacity.z = -4
                        show1.z = -4
                        show2.z = -3
                        show3.z = -2
                        show4.z = -1
                        show5.z = 0
                        show6.z = -1
                        show7.z = -2
                        showrightopacity.z = -3
                    }

                    if(show6.objectName == "show_1")
                    {
                        showleftopacity.z = -3
                        show1.z = -4
                        show2.z = -4
                        show3.z = -3
                        show4.z = -2
                        show5.z = -1
                        show6.z = 0
                        show7.z = -1
                        showrightopacity.z = -2
                    }

                    if(show7.objectName == "show_1")
                    {
                        showleftopacity.z = -2
                        show1.z = -3
                        show2.z = -4
                        show3.z = -4
                        show4.z = -3
                        show5.z = -2
                        show6.z = -1
                        show7.z = 0
                        showrightopacity.z = -1
                    }

                    if(showrightopacity.objectName == "show_1")
                    {
                        showleftopacity.z = -1
                        show1.z = -2
                        show2.z = -3
                        show3.z = -4
                        show4.z = -4
                        show5.z = -3
                        show6.z = -2
                        show7.z = -1
                        showrightopacity.z = 0
                    }
                }
                timerFocus.running = false

                if(show4.objectName == "show_5" && show5.objectName == "show_5")
                {
                    showleftopacity.objectName = "show_1"
                    show1.objectName = "show_9"
                    show2.objectName = "show_8"
                    show3.objectName = "show_7"
                    show4.objectName = "show_6"
                    show5.objectName = "show_5"
                    show6.objectName = "show_4"
                    show7.objectName = "show_3"
                    showrightopacity.objectName = "show_2"
                }

                if(show4.objectName == "show_4" && show5.objectName == "show_4")
                {
                    showleftopacity.objectName = "show_9"
                    show1.objectName = "show_8"
                    show2.objectName = "show_7"
                    show3.objectName = "show_6"
                    show4.objectName = "show_5"
                    show5.objectName = "show_4"
                    show6.objectName = "show_3"
                    show7.objectName = "show_2"
                    showrightopacity.objectName = "show_1"
                }

                if(show4.objectName == "show_3" && show5.objectName == "show_3")
                {
                    showleftopacity.objectName = "show_8"
                    show1.objectName = "show_7"
                    show2.objectName = "show_6"
                    show3.objectName = "show_5"
                    show4.objectName = "show_4"
                    show5.objectName = "show_3"
                    show6.objectName = "show_2"
                    show7.objectName = "show_1"
                    showrightopacity.objectName = "show_9"
                }

//                console.log("showleftopacity", showleftopacity.objectName)
//                console.log("show1", show1.objectName)
//                console.log("show2", show2.objectName)
//                console.log("show3", show3.objectName)
//                console.log("show4", show4.objectName)
//                console.log("show5", show5.objectName)
//                console.log("show6", show6.objectName)
//                console.log("show7", show7.objectName)
//                console.log("showrightopacity", showrightopacity.objectName)

            }
        }

        Timer {
            id: timerTwoFocus
            interval: 300;
            onTriggered:
            {
                if(showleftopacity.objectName == "show_1")
                {
                    showleftopacity.scale = 1.0
                }

                else if(show1.objectName == "show_1")
                {
                    show1.scale = 1.0
                }

                else if(show2.objectName == "show_1")
                {
                    show2.scale = 1.0
                }

                else if(show3.objectName == "show_1")
                {
                    show3.scale = 1.0
                }

                else if(showrightopacity.objectName == "show_1")
                {
                    showrightopacity.scale = 1.0
                }

                else if(show5.objectName == "show_1")
                {
                    show5.scale = 1.0
                }

                else if(show4.objectName == "show_1")
                {
                    show4.scale = 1.0
                }

                else if(show6.objectName == "show_1")
                {
                    show6.scale = 1.0
                }

                else if(show7.objectName == "show_1")
                {
                    show7.scale = 1.0
                }

                timerTwoFocus.running = false
            }
        }

        Timer {
            id: timerThreeFocus
            interval: 1200;
            onTriggered:
            {
                timerThreeFocus.running = false
            }
        }

        onAccepted: {

            if(timerThreeFocus.running != true)
            {
                var textOne;
                if(showleftopacity.objectName == "show_1")
                {
                    textOne = showleftopacity.textShow
                }

                else if(show1.objectName == "show_1")
                {
                    textOne = show1.textShow
                }

                else if(show2.objectName == "show_1")
                {
                    textOne = show2.textShow
                }

                else if(show3.objectName == "show_1")
                {
                    textOne = show3.textShow
                }

                else if(showrightopacity.objectName == "show_1")
                {
                    textOne = showrightopacity.textShow
                }

                else if(show5.objectName == "show_1")
                {
                    textOne = show5.textShow
                }

                else if(show4.objectName == "show_1")
                {
                    textOne = show4.textShow
                }

                else if(show6.objectName == "show_1")
                {
                    textOne = show6.textShow
                }

                else if(show7.objectName == "show_1")
                {
                    textOne = show7.textShow
                }

                if(Qt_fun.inputShowWords(textOne, textInput.text))
                {
                    if(showleftopacity.objectName == "show_1")
                    {
                        showleftopacity.scale = 1.3
                    }

                    else if(show1.objectName == "show_1")
                    {
                        show1.scale = 1.3
                    }

                    else if(show2.objectName == "show_1")
                    {
                        show2.scale = 1.3
                    }

                    else if(show3.objectName == "show_1")
                    {
                        show3.scale = 1.3
                    }

                    else if(showrightopacity.objectName == "show_1")
                    {
                        showrightopacity.scale = 1.3
                    }

                    else if(show5.objectName == "show_1")
                    {
                        show5.scale = 1.3
                    }

                    else if(show4.objectName == "show_1")
                    {
                        show4.scale = 1.3
                    }

                    else if(show6.objectName == "show_1")
                    {
                        show6.scale = 1.3
                    }

                    else if(show7.objectName == "show_1")
                    {
                        show7.scale = 1.3
                    }

                    timerFocus.running = true
                    timerTwoFocus.running = true
                    timerThreeFocus.running = true

                    textInput.text = ""
                }
            }
        }


        onTextChanged: // Срабатывает при изменении текста textInput
        {
            if(textInput.color != "black")
                textInput.color = "black"
        }
    }

    Keys.onRightPressed: idhelp.objectName = "temp"

    Help_word{
        id: idhelp
        objectName: "temp"
    }
}
