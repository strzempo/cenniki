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

Rectangle {
    width: 100
    height: 100
    color: "lightgray"
    TextArea {
        id: textArea
        anchors.centerIn: parent
        font.pixelSize: 18
        text:
            "Aliaxis Utilities & Industry Sp. z o.o.\n" +
            "ul. Annopol 4a, budynek C\n" +
            "03 - 236 Warszawa\n" +
            "NIP: 951 - 00 - 51 - 202\n" +
            "Tel. +48 22 329 79 00\n" +
            "marek.strzempowicz@aliaxis-ui.pl"
        selectByKeyboard: true
        selectByMouse: true
        wrapMode: "WordWrap"
        width: parent.width
        height: parent.height
    }
    Rectangle {
        color: "steelBlue"
        width: 70
        height: 1.5 * kopiuj.contentHeight
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10

        Text {
            id: kopiuj
            anchors.centerIn: parent
            text: "Kopiuj"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {textArea.copy(); textArea.deselect() }
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        height: zamknij.contentHeight + 8
        width: zamknij.contentWidth
        color: "transparent"
        Text {
            id: zamknij
            text: "✗   Zamknij"
            color: "black"
            font { family: localFont.name; pixelSize: 20 }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: ld.source=""
        }
    }
}
