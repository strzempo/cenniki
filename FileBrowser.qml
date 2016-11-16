import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQml.Models 2.2

Item {
    id: browser
   // property alias mainModel: mainModel.model
    width: 300
    height: 200
    property string sectionName
    property var mainModel: DelegateModel {
        model: mainTreeModel
        delegate: Rectangle {
            width: view.width
            height:34
            Row {
                anchors.fill: parent
                /*
                Image {
                    id: icon
                    width: delegate.height - 2
                    height:width
                    source: "image://iconProvider/"+filePath
                }*/
                Text {
                    text: nodeName //fileName
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (model.hasModelChildren) {
                        sectionName = nodeName
                        mainModel.rootIndex = mainModel.modelIndex(index)
                    } else
                        mainModel.model.invokeAction(mainModel.modelIndex(index))
                }
            }
        }
    }
    ListView {
        id: view
        anchors.fill: parent
        model: mainModel
        headerPositioning: ListView.OverlayHeader
        header: Rectangle {
            width: browser.width
            height: 34
            color: "yellow"
            z:2
            Row {
                anchors.fill: parent
                Button {
                    width:32
                    height :32
                    text: "<<<"
                    onClicked: {
                        mainModel.rootIndex = mainModel.parentModelIndex()
                        sectionName = mainModel.model.sectionName(mainModel.rootIndex)
                    }
                }
                Text {
                    text: sectionName
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
        /*
        footerPositioning: ListView.OverlayHeader
        footer: Rectangle {
            width: browser.width
            height: 34
            color: "yellow"
            z:2
            Row {
                anchors.fill: parent
                Text {
                    text: "["+folder.count+" Files]"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }*/
    }
}
