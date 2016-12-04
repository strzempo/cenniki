import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: qsTr("Aliaxis-UI")

    width: 750 //542 //826//413
    height: 587 //768 //1169//584

    flags: Qt.FramelessWindowHint | Qt.MSWindowsFixedSizeDialogHint

    FontLoader { id: localFont; source: "fonts/SourceSansPro-Semibold.otf" }

    background: Image {
        source: "images/background.png" //"fip.png"
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
    }

/*
    style: ApplicationWindowStyle {
        background: Image {
            source: "qrc:/fip.png"
        }
    }
*/
  //      anchors.fill: parent

    header: Rectangle {
        height: 8
        width: parent.width
        color: "slategray"

        /*Text {
            text: qsTr("Aliaxis Utility and Industry\nMarek Strzempowicz")
            font.pointSize: 20
*/

    MouseArea {
        anchors.fill: parent
        property variant clickPos: "1,1"

        onPressed: {
            clickPos  = Qt.point(mouse.x,mouse.y)
   //         console.log("presed", clickPos)
        }

        onPositionChanged: {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
     //       console.log("delta", delta)
            mainWindow.x += delta.x;
            mainWindow.y += delta.y;
        }
    }
    }

    FileBrowser {
        anchors.fill: parent
    }

    footer: Rectangle {
        height: 30
        color: "transparent"
        Text {
            text: qsTr("    Zamknij")
            color: "black"//"lightsteelblue"
            font { family: localFont.name; pixelSize: 20 }
        }
        MouseArea {
            anchors.fill: parent
            onPressed: Qt.quit()
        }
    }
}
