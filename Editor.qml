/**
    cenniki - Menu used in CD with promotion materials for Aliaxis Utilities and Industry.
    Copyright (C) 2016  Kamil 'konserw' Strzempowicz, konserw@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

import QtQuick 2.7
import QtQml.Models 2.2
Item {
    id: editor
    property string sectionName
    property string oldSectionName
    property var mainModel: DelegateModel {
        model: mainTreeModel
        delegate: MouseArea {
            id: dragArea
            anchors { left: parent.left; right: parent.right }
            //width: view.width
            height: itemRect.height
            property bool held: false
/*
            onClicked: console.log("area clicked")
            onDoubleClicked: console.log("area double clicked")
            onEntered: console.log("mouse entered the area")
            onExited: console.log("mouse left the area")
            onPressAndHold: console.log("mouse held")
            onReleased: console.log("mouse released")
*/
            //property int visualIndex: DelegateModel.itemsIndex
            drag.target: held ? itemRect : undefined
            drag.axis: Drag.YAxis

            onPressAndHold: held = true
            onReleased: held = false
            onClicked: {
                if (model.hasModelChildren) {
                    oldSectionName = sectionName
                    sectionName = nodeName
                    mainModel.rootIndex = mainModel.modelIndex(index)
                } else
                    mainModel.model.invokeAction(mainModel.modelIndex(index))
            }
/*
            DropArea {
                anchors { fill: parent; margins: 5 }
                onEntered: visualModel.items.move(drag.source.visualIndex, delegateRoot.visualIndex)
            }
*/

            DropArea {
                anchors { fill: parent; margins: 10 }

                onEntered: {
                    visualModel.items.move(
                            drag.source.DelegateModel.itemsIndex,
                            dragArea.DelegateModel.itemsIndex)
                }
            }
            Rectangle {
                id: itemRect
                color: dragArea.held ? "lightgrey" : "transparent"
                Behavior on color { ColorAnimation { duration: 200; easing.type: Easing.InOutQuad } }
                border.width: 2
                border.color: "lightsteelblue"
               // anchors.fill: parent
                width: dragArea.width
                height: nodeNameText.contentHeight + 8
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }

                Drag.active: dragArea.held
                Drag.source: dragArea
       //         Drag.hotSpot.x: width / 2
       //         Drag.hotspot.y: height / 2

                states: [
                State {
                        when: dragArea.held
                        ParentChange {
                            target: itemRect
                            parent: view
                        }
                        AnchorChanges {
                            target: itemRect
                            anchors.horizontalCenter: undefined
                            anchors.verticalCenter: undefined
                        }

                    }

                ]

                Image {
                    id: icon
                    width: 24
                    height: width
                    source: "images/cross.png"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: mainModel.model.removeItem(mainModel.rootIndex, mainModel.modelIndex(index))
                    }
                }
                Text {
                    id: nodeNameText
                    text: nodeName
                    font.pixelSize: 20
                    property int w: parent.width - icon.width - anchors.leftMargin - 10
                    width: w < contentWidth ? w : contentWidth
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: icon.right
                    anchors.leftMargin: 4
                    wrapMode: Text.WordWrap
                    color: model.hasModelChildren ? "black" : "steelblue"
/*
                    MouseArea {
                        id: mouseArea
                        propagateComposedEvents: true
                        anchors.fill: parent
                        onClicked: {
                            if (model.hasModelChildren) {
                                oldSectionName = sectionName
                                sectionName = nodeName
                                mainModel.rootIndex = mainModel.modelIndex(index)
                            } else
                                mainModel.model.invokeAction(mainModel.modelIndex(index))
                        }
                    }
  */
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
            width: editor.width
            height: 1.5 * sectionNameText.contentHeight
            color: "transparent"
            Text {
                id: sectionNameText
                text: sectionName
                font.pixelSize: 24
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        footer: Column {
            Rectangle {
                width: editor.width
                height: 1.5 * goBack.contentHeight
                color: "transparent"
                visible: (oldSectionName)
                Text {
                    id: goBack
                    text: "⤺" + oldSectionName
                    font.pixelSize: 20
                    color: "midnightblue"
                    anchors.fill: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        mainModel.rootIndex = mainModel.rootIndex.parent
                        sectionName = mainModel.model.sectionName(mainModel.rootIndex)
                        oldSectionName = mainModel.model.sectionName(mainModel.rootIndex.parent)
                    }
                }
            }
            Rectangle {
                width: editor.width
                height: 1.5 * goMenu.contentHeight
                color: "transparent"
                visible: sectionName
                Text {
                    id: goMenu
                    text: "↶ Menu Główne"
                    font.pixelSize: 20
                    color: "darkblue"
                    anchors.fill: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        mainModel.rootIndex = 0
                        sectionName = ""
                        oldSectionName = ""
                    }
                }
            }
        }
    }
}
