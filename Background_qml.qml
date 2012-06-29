// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 390
    height: 300

    gradient: Gradient {
        GradientStop { position: 1.0; color: "#363636" }
        GradientStop { position: 0.5; color: "#9C9C9C" }
        GradientStop { position: 0.0; color: "#9C9C9C" }
    }
}
