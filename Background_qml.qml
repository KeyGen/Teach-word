// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 390
    height: 300

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
}
