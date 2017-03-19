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

ApplicationWindow {
    visible: true
    title: qsTr("Cenniki Editor")

    height: 730
    width: (height +1) * 1500/1173

    FontLoader { id: localFont; source: "fonts/SourceSansPro-Semibold.otf" }

    background: Image {
        source: "images/background.png"
        verticalAlignment: Image.AlignBottom
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
    }

    Editor {
        id: editor
        height: 600
        width: 532
        x: parent.width - width
        y: 35
    }

    footer: Column {
        x: 20

        Rectangle {
            height: dodajMenu.contentHeight + 10
            width: dodajMenu.contentWidth
            color: "transparent"
            Text {
                id: dodajMenu
                text: "Dodaj Menu"
                color: "black"
                font { family: localFont.name; pixelSize: 20 }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: mainTreeModel.insertMenu("nowe Menu", editor.currentParent)
            }
        }

        Rectangle {
            height: dodaj.contentHeight + 10
            width: dodaj.contentWidth
            color: "transparent"
            Text {
                id: dodaj
                text: "Dodaj Element"
                color: "black"
                font { family: localFont.name; pixelSize: 20 }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: mainTreeModel.insertItem("nowy element", editor.currentParent)
            }
        }
        Rectangle {
            height: zapisz.contentHeight + 10
            width: zapisz.contentWidth
            color: "transparent"
            Text {
                id: zapisz
                text: "Zapisz"
                color: "red"
                font { family: localFont.name; pixelSize: 20 }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: mainTreeModel.save()
            }
        }
    }
}
