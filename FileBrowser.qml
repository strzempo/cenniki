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
    id: browser
    property string sectionName
    property string oldSectionName
    property var mainModel: DelegateModel {
        property var mainMenuIndex: rootIndex
        model: mainTreeModel
        delegate: Rectangle {
            color: "transparent"
            width: view.width
            height: nodeNameText.contentHeight + 8

            Image {
                id: icon
                width: 24
                height: width
                source: "images/ding.png"
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
            }
            Text {
                id: nodeAboutText
                text: nodeAbout
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
                    if (model.hasModelChildren) {
                        oldSectionName = sectionName
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
        }

        add: Transition {
            NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 1000 }
        }

        headerPositioning: ListView.OverlayHeader
        header: Rectangle {
            width: browser.width
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
                width: browser.width
                height: 1.5 * goBack.contentHeight
                color: "transparent"
                visible: oldSectionName
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
                        mainModel.rootIndex = mainModel.rootIndex.parent //mainModel.model.parent(mainModel.rootIndex)
                        sectionName = mainModel.model.sectionName(mainModel.rootIndex)
                        oldSectionName = mainModel.model.sectionName(mainModel.rootIndex.parent)
                    }
                }
            }
            Rectangle {
                width: browser.width
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
                        mainModel.rootIndex = 0// mainModel.model.rootIndex()
                        sectionName = ""
                        oldSectionName = ""
                    }
                }
            }
        }
    }
}
