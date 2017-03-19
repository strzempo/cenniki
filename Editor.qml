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
    id: root

    property var currentParent: visualModel.rootIndex
    property string sectionName
    property string oldSectionName

    Component {
        id: dragDelegate

        MouseArea {
            id: dragArea
            anchors { left: parent.left; right: parent.right }
            height: itemRect.height

            property bool itIsMenu
            Component.onCompleted: itIsMenu = visualModel.model.isMenu(visualModel.modelIndex(index))

            property bool held: false
            onHeldChanged: {
                if (held == false)
                    mainTreeModel.reorder(visualModel.rootIndex, visualModel.modelIndex(index), dragArea.DelegateModel.itemsIndex)
            }

            drag.target: held ? itemRect : undefined
            drag.axis: Drag.YAxis

            onPressAndHold: held = true
            onReleased: held = false
            onClicked: {
                if (itIsMenu) {
                    oldSectionName = sectionName
                    sectionName = nodeName
                    visualModel.rootIndex = visualModel.modelIndex(index)
                } else
                    visualModel.model.invokeAction(visualModel.modelIndex(index))
            }

            DropArea {
                anchors { fill: parent; margins: 2 }
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
                width: dragArea.width
                height: nodeNameText.contentHeight + 8
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }

                Drag.active: dragArea.held
                Drag.source: dragArea
                Drag.hotSpot.x: width / 2
                Drag.hotSpot.y: height / 2

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
                        onClicked: visualModel.model.removeItem(visualModel.rootIndex, visualModel.modelIndex(index))
                    }
                }

                MyText {
                    id: nodeNameText
                    text: nodeName
                    property int w: parent.width - icon.width - anchors.leftMargin - 10
                    width: w < contentWidth ? w : contentWidth
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: icon.right
                    anchors.leftMargin: 4
                    wrapMode: Text.WordWrap
                    color: itIsMenu ? "black" : "steelblue"
                }
            }
        }
    }

    DelegateModel {
        id: visualModel
        model: mainTreeModel
        delegate: dragDelegate


        function insertPosition(item) {
            var lower = 0
            var upper = items.count
            while (lower < upper) {
                var middle = Math.floor(lower + (upper - lower) / 2)
                var result = item.model.nodeSequence < items.get(middle).model.nodeSequence
                if (result) {
                    upper = middle
                } else {
                    lower = middle + 1
                }
            }
            return lower
        }
        function sort()
        {
            while (unsortedItems.count > 0) {
                var item = unsortedItems.get(0)
                var index = insertPosition(item)

                item.groups = "items"
                items.move(item.itemsIndex, index)
            }
        }

        items.includeByDefault: false
        groups: VisualDataGroup {
            id: unsortedItems
            name: "unsorted"

            includeByDefault: true
            onChanged: {
                visualModel.sort()
            }
        }
    }

    ListView {
        id: view
        anchors.fill: parent
        model: visualModel

        spacing: 4
        cacheBuffer: 50

        headerPositioning: ListView.OverlayHeader
        header: Rectangle {
            width: root.width
            height: 1.5 * sectionNameText.contentHeight
            color: "transparent"
            MyText {
                id: sectionNameText
                text: sectionName
                font.pixelSize: 24
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        footer: Column {
            Rectangle {
                width: root.width
                height: 1.5 * goBack.contentHeight
                color: "transparent"
                visible: (oldSectionName)
                MyText {
                    id: goBack
                    text: "⤺" + oldSectionName
                    anchors.fill: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        visualModel.rootIndex = visualModel.rootIndex.parent
                        sectionName = oldSectionName
                        oldSectionName = visualModel.model.sectionName(visualModel.rootIndex.parent)
                    }
                }
            }
            Rectangle {
                width: root.width
                height: 1.5 * goMenu.contentHeight
                color: "transparent"
                visible: sectionName
                MyText {
                    id: goMenu
                    text: "↶ Menu Główne"
                    anchors.fill: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        visualModel.rootIndex = 0
                        sectionName = ""
                        oldSectionName = ""
                    }
                }
            }
        }
    }
}
