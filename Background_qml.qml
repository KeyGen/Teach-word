// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: backenground
    width: 390
    height: 306

    gradient: Gradient {
        objectName: "background_color"
        GradientStop {
            objectName: "background_1.0"
            position: 1.0;
            color: "#363636"
        }

        GradientStop {
            objectName: "background_0.5"
            position: 0.5;
            color: "#9C9C9C"
        }

        GradientStop {
            objectName: "background_0.0"
            position: 0.0;
            color: "#9C9C9C"
        }
    }

    MouseArea {
        id: input_size_2_Mouse
        anchors.fill: parent
        onClicked: Qt.LeftButton
        onPositionChanged: Qt_fun.move_window();
        onEntered: Qt_fun.cursor_up()
        onExited: Qt_fun.cursor_down()
    }
}
