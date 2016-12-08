import QtQuick 2.7
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

            Image {
                id: icon
                width: 24//delegate.height - 2
                height: width
                source: "images/ding.png"
            }
            Text {
                id: text
                text: nodeName
                font.pixelSize: 20
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: icon.right
                anchors.leftMargin: 4
            }

            states: State {
                name: "active"; when: mouseArea.containsMouse == true
                PropertyChanges { target: icon; rotation: 90; x: 10 }
            }
            transitions: Transition {
                from: ""; to: "active"; reversible: true
                ParallelAnimation {
                    NumberAnimation { properties: "x,rotation"; duration: 500; easing.type: Easing.InOutQuad }
                    ColorAnimation { duration: 500 }
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
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

        remove: Transition {
            NumberAnimation { property: "opacity"; from: 1.0; to: 0; duration: 500 }
         //   NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 400 }
        }

        add: Transition {
            NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 1000 }
//            NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }
        }



        headerPositioning: ListView.OverlayHeader
        header: Rectangle {
            width: browser.width
            height: 34
            color: "transparent" //"lightgreen"
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
