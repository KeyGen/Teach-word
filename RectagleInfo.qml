// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: recinfo
    objectName: "info"
    width: 560
    height: 180

    radius: 10
    smooth: true

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#4c0000"}
        GradientStop { position: 0.5; color: "#df8c73"}
        GradientStop { position: 1.0; color: "#4c0000"}
    }

    y: 60
    x: 20

    border.width: 3
    border.color: "#080808"

    Image {
        id: iconPr
        source: ":/picture/icon"
        smooth: true

        width: 90
        height: 90

        y: -44.4
        x: parent.width/2 - iconPr.width/2
    }

    Text {
        id: textInfo
        text:
"<center>
<span style=\" font-size:6pt;\">&#32;<br></span>
<span style=\" font-size:14pt;\"><b>Learn words v 2.0</b></span>
<span style=\" font-size:6pt;\">&#32;<br></span>
<span style=\" font-size:6pt;\">&#32;<br></span>
<span style=\" font-size:11pt;\">Халявная прога т.е <span style=\" color:#004000;\">OpenSours</span></span>
<span style=\" font-size:6pt;\">&#32;<br></span>
<span style=\" font-size:11pt;\">Написана на Qt 4.8 т.е межплатформенная</span>
<span style=\" font-size:6pt;\">&#32;<br></span>
<span style=\" font-size:11pt;\">Написал KeyGen</span>
<span style=\" font-size:6pt;\">&#32;<br></span>
<span style=\" font-size:11pt;\">Учись!</span>
</center>"

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

