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
            height: text.contentHeight + 8

            Image {
                id: icon
                width: 24
                height: width
                source: "images/ding.png"
            }
            Text {
                id: text
                text: nodeName
                font.pixelSize: 20
                width: parent.width - icon.width - (anchors.leftMargin * 2)
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: icon.right
                anchors.leftMargin: 4
                wrapMode: Text.WordWrap
                //clip: true
                color: model.hasModelChildren ? "black" : "steelblue"
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
            height: 1.5 * text.contentHeight
            color: "transparent"
            Text {
                text: sectionName
                font.pixelSize: 24
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        footer: Column {
            Rectangle {
                width: browser.width
                height: 1.5 * text.contentHeight
                color: "transparent"
                visible: oldSectionName
                Text {
                    text: "⤺" + oldSectionName //" Powrót"
                    font.pixelSize: 20
                    color: "midnightblue"
                    anchors.fill: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        mainModel.rootIndex = mainModel.parentModelIndex()
                        sectionName = mainModel.model.sectionName(mainModel.rootIndex)
                        oldSectionName = mainModel.model.sectionName(mainModel.rootIndex.parent)
                    }
                }
            }
            Rectangle {
                width: browser.width
                height: 1.5 * text.contentHeight
                color: "transparent"
                visible: sectionName
                Text {
                    text: "↶ Menu Główne"
                    font.pixelSize: 20
                    color: "darkblue"
                    anchors.fill: parent
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        mainModel.rootIndex = mainModel.model.rootIndex()
                        sectionName = ""
                        oldSectionName = ""
                    }
                }
            }
        }
    }
}
