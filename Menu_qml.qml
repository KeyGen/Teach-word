// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {
    width: 390
    height: 60

    Rectangle{

        width: 50
        height: 388

        x: 170
        y: -168

        border.width: 2

        border.color: "#303030"
        smooth: true

        rotation: 90

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#363636" }
            GradientStop { position: 0.4; color: "#9C9C9C" }
            GradientStop { position: 0.4; color: "#9C9C9C" }
            GradientStop { position: 0.6; color: "#9C9C9C" }
            GradientStop { position: 0.6; color: "#9C9C9C" }
            GradientStop { position: 1.0; color: "#363636" }
        }

        Edit_push{
            id: edit
            y: parent.height-62
        }

        Setting_push{
            id: setting
            y: edit.y - 44 - 5
        }

        Style_push{
            id: style
            y: setting.y - 47 - 5
        }

        Help_push{
            id: help
            y: style.y - 50 - 5
        }

        Info_push{
            id:info
            y: help.y - 47 - 5
        }

        Exit_push{
            id:exit
            y: info.y - 44 - 5
        }

        Mask_push{
            id:mask
            y: exit.y - 41 - 5
        }

    }
}
