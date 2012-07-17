// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle{
    id: show
    width: 300
    height: 150

    x: parent.width/2 - show.width/2
    y: parent.height/2 - 75

    color: "green"

//    gradient: Gradient {
//        GradientStop { position: 0.0; color: "#00358c"}
//        GradientStop { position: 0.3; color: "#0075cd"}
//        GradientStop { position: 0.5; color: "#00c7e6"}
//        GradientStop { position: 0.7; color: "#0075cd"}
//        GradientStop { position: 1.0; color: "#00358c"}
//    }


    smooth: true
    radius: 10
    border.width: 2
    border.color: "#4c0000"

    Behavior on x { PropertyAnimation {duration: 600; easing.type: Easing.InCurve} }
    Behavior on y { PropertyAnimation {duration: 600; easing.type: Easing.InOutSine} }
    Behavior on scale { PropertyAnimation {duration: 400; easing.type: Easing.InOutSine} }
    Behavior on opacity { PropertyAnimation {duration: 600; easing.type: Easing.InOutSine} }

    // Разрешаем доступ textButton
    property alias textShow: text.text
    Text {
        id: text
        font.pixelSize: 40

        anchors.verticalCenter: show.verticalCenter
        anchors.horizontalCenter: show.horizontalCenter
    }
}
