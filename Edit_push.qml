import QtQuick 1.1

//////////////////////////////////////
//////////////////// Кнопка редактирования словоря

Image {
    id: edit //Имя кнопки

    state: "normal"

            states: [
                State {
                    name: "normal"
                    PropertyChanges {
                        target: edit
                        source: ":/icon/edit"
                    }
                },
                State {
                    name: "shift"
                    PropertyChanges {
                        target: edit
                        source: ":/icon/edit_activ"
                    }
                }
            ]

    width: 41
    height: 41

    x: 4.5

    scale: qtMouse.pressed ? 0.8 : 1.0

    smooth: true
    rotation: -90

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
            Qt_fun.exec_dialog_input()
        }
    }
}
