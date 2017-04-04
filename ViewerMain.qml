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
import QtQuick.Controls 2.0
import QtQml.Models 2.2

ApplicationWindow {
    id: mainWindow
    visible: true
    title: qsTr("Aliaxis-UI")

    height: 730
    width: (height - header.height +1) * 1500/1173

    flags: Qt.FramelessWindowHint | Qt.MSWindowsFixedSizeDialogHint

    background: Image {
        source: "images/background.png"
        verticalAlignment: Image.AlignBottom
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
    }

    header: Rectangle {
        height: 24
        width: parent.width
        color: "steelblue"

        MyText {
            text: "Aliaxis Utilities & Industry"
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 16
        }

        MouseArea {
            anchors.fill: parent
            property var clickPos: "1,1"

            onPressed: {
                clickPos  = Qt.point(mouse.x,mouse.y)
            }

            onPositionChanged: {
                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                mainWindow.x += delta.x;
                mainWindow.y += delta.y;
            }
        }
    }

    Rectangle {
        id: sectionHeader
        x: view.x
        y: 35
        width: view.width
        height: sectionHeaderText.height * 1.5
        color: "transparent"
        MyText {
            id: sectionHeaderText
            text: view.sectionName
            font.pixelSize: 24
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Viewer {
        id: view
        height: 365
        width: 500
        x: parent.width - width
        anchors.top: sectionHeader.bottom
    }

    Loader {
        id: ld
        anchors.centerIn: parent
    }

    footer: Column {
        anchors.bottomMargin: 25
        x: 50
        spacing: 8

        Rectangle {
            width: goBack.contentWidth
            height: goBack.contentHeight
            color: "transparent"
            visible: view.oldSectionName
            MyText {
                id: goBack
                text: "⤺" + view.oldSectionName
                anchors.fill: parent
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    view.currentRootIndex = view.currentRootIndex.parent
                    view.sectionName = view.oldSectionName
                    view.oldSectionName = mainTreeModel.sectionName(view.currentRootIndex.parent)
                }
            }
        }

        Rectangle {
            width: goMenu.contentWidth
            height: goMenu.contentHeight
            color: "transparent"
            visible: view.sectionName
            MyText {
                id: goMenu
                text: "↶ Menu Główne"
                anchors.fill: parent
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    view.currentRootIndex = 0
                    view.sectionName = ""
                    view.oldSectionName = ""
                }
            }
        }

        Rectangle {
            height: kontakt.contentHeight
            width: kontakt.contentWidth
            color: "transparent"
            MyText {
                id: kontakt
                text: "☎ Kontakt"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: ld.source="Kontakt.qml"
            }
        }

        Rectangle {
            height: zamknij.contentHeight
            width: zamknij.contentWidth
            color: "transparent"
            MyText {
                id: zamknij
                text: " ✗  Zamknij"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: Qt.quit()
            }
        }
    }
}
