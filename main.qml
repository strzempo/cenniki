import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2
import Qt.labs.folderlistmodel 2.1
import QtQuick.Layouts 1.0


ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    title: qsTr("Aliaxis-UI")

    color: "lightgray"

    header: Text {
        id: headerText
        text: qsTr("Aliaxis Utility and Industry\nMarek Strzempowicz")
        font.pointSize: 20
    }

    FileBrowser {
        anchors.fill: parent
    }
}
