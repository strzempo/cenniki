import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQml.Models 2.2

Item {
    id: browser
   // property alias mainModel: mainModel.model
 //   width: 300
  //  height: 200
    property string sectionName
    property var mainModel: DelegateModel {
        model: mainTreeModel
        delegate: Rectangle {
            color: "transparent"
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
                    text: nodeName
                    font.pointSize: 12
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
            color: "lightgreen"
            //z:2
            Text {
                text: sectionName
                font.pointSize: 14
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    mainModel.rootIndex = mainModel.parentModelIndex()
                    sectionName = mainModel.model.sectionName(mainModel.rootIndex)
                }
            }
        }
    }
}
