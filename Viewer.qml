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
import QtQuick.Controls 2.0

Item {
    id: root

    property alias currentRootIndex: visualModel.rootIndex
    property string sectionName
    property string oldSectionName

    Component {
        id: dragDelegate

        Rectangle {
            id: itemRect

            property bool itIsMenu
            Component.onCompleted: itIsMenu = visualModel.model.isMenu(visualModel.modelIndex(index))

            color: "transparent"
            anchors { left: parent.left; right: parent.right }
            height: nodeNameText.contentHeight

            Image {
                id: icon
                width: 24
                height: width
                source: "images/ding.png"
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
                color: model.hasModelChildren ? "royalblue" : "steelblue"
            }
            MyText {
                id: nodeAboutText
                text: (nodeAbout) ? nodeAbout : ""
                font.pixelSize: 16
                color: "steelblue"
                font.italic: true
                opacity: 0
                width: 200
                height: parent.height
                anchors.verticalCenter: parent.verticalTop
                anchors.left: nodeNameText.right
                anchors.margins: 10
                wrapMode: Text.WordWrap

            }

            states: State {
                name: "active"; when: mouseArea.containsMouse == true
                PropertyChanges { target: icon; rotation: 90; x: 10 }
                PropertyChanges { target: nodeAboutText; opacity: 1 }
            }
            transitions: Transition {
                from: ""; to: "active"; reversible: true
                NumberAnimation { properties: "x,rotation,opacity"; duration: 500; easing.type: Easing.InOutQuad }
            }


            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    if (itIsMenu) {
                        oldSectionName = sectionName
                        sectionName = nodeName
                        currentRootIndex = visualModel.modelIndex(index)
                    } else
                        mainTreeModel.invokeAction(visualModel.modelIndex(index))
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

        spacing: 8
        cacheBuffer: 50
        clip: true

        ScrollBar.vertical: ScrollBar {
            contentItem.opacity: 1
        }

        remove: Transition {
            NumberAnimation { property: "opacity"; from: 1.0; to: 0; duration: 500 }
        }

        add: Transition {
            NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 1000 }
        }
    }
}
