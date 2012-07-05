// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

//////////////////////////////////////
//////////////////// Кнопка редактирования словоря

Image {
    id: edit //Имя кнопки

    width: 41
    height: 41

    x: 4.5

    scale: qtMouse.pressed ? 0.8 : 1.0

    smooth: true
    rotation: -90

    state: "normal"

            states: [
                State {
                    name: "normal"
                    PropertyChanges {
                        target: edit
                        source: ":/icon/mask"
                    }
                },
                State {
                    name: "shift"
                    PropertyChanges {
                        target: edit
                        source: ":/icon/mask_activ"
                    }
                }
            ]

    MouseArea {
        id: quitMouse
        anchors.fill: parent

        hoverEnabled: true
        onEntered:
        {
            edit.state = 'shift'
            Qt_fun.startSoundButton()
        }
        onExited: edit.state = 'normal'
    }

    MouseArea {
        id: qtMouse
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked:
        {
            edit.state = 'normal'
            Qt_fun.maskProgramm()
        }
    }
}
