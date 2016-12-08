import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow {
    id: mainWindow
    visible: true
    title: qsTr("Aliaxis-UI")

    height: 730
    width: (height - header.height +1) * 1500/1173

    flags: Qt.FramelessWindowHint | Qt.MSWindowsFixedSizeDialogHint

    FontLoader { id: localFont; source: "fonts/SourceSansPro-Semibold.otf" }

    background: Image {
        source: "images/background.png"
     //   height: parent.height - parent.header.height
     //   width:  parent.width
      //  anchors.top: header.bottom
        verticalAlignment: Image.AlignBottom
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
    }

    header: Rectangle {
        height: 20
        width: parent.width
        color: "steelblue"//"slategray"

        Text {
            text: qsTr("Aliaxis Utility and Industry")
            font.pixelSize: 14
  //          width: parent.width
            anchors.fill: parent
//            height: parent.
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            anchors.fill: parent
            property variant clickPos: "1,1"

            onPressed: {
                clickPos  = Qt.point(mouse.x,mouse.y)
            }

            onPositionChanged: {
                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                mainWindow.x += delta.x;
                mainWindow.y += delta.y;
            }
        }
    }

    FileBrowser {
        height: 500
        width: 250
        x: parent.width - width
        y: 35
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
