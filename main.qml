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

    FileBrowser {
        anchors.fill: parent
 //       path: "file:///home/" // let's start with the Home folder
    }
  /*
    color: "lightgray"

    header: Text {
        id: headerText
        text: qsTr("Aliaxis Utility and Industry\nMarek Strzempowicz")
        font.pointSize: 24
    }

    ListModel {
        id: mainListModel
        ListElement { name: qsTr("First Item") }
        ListElement { name: qsTr("second item") }
    }

    Component {
        id: listDelegate
        Text {
            text: name;
            font.pixelSize: 18;
        }
    }

    ListView {
        id: mainListView
        anchors.fill: parent
        model: mainListModel
        delegate: listDelegate

        highlight: Rectangle {
            width: parent.width
            color: "red"
        }
    }

    footer: ToolBar {
        id: bottomToolBar

        ToolButton {
            id: returnToolButton1
            text: qsTr("Powrót")
        }
    }
    */
}
