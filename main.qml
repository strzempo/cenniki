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
    id: mainWindow
    visible: true
    title: qsTr("Aliaxis-UI")

    height: 730
    width: (height - header.height +1) * 1500/1173

    flags: Qt.FramelessWindowHint | Qt.MSWindowsFixedSizeDialogHint

    FontLoader { id: localFont; source: "qrc:/fonts/SourceSansPro-Semibold.otf" }

    background: Image {
        source: "images/background.png"
        verticalAlignment: Image.AlignBottom
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
    }

    header: Rectangle {
        height: 20
        width: parent.width
        color: "steelblue"

        Text {
            text: "Aliaxis Utilities & Industry"
            font { family: localFont.name; pixelSize: 14 }
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            anchors.fill: parent
            property variant clickPos: "1,1"

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

    FileBrowser {
        height: 600
        width: 500
        x: parent.width - width
        y: 35
    }

    Loader {
        id: ld
        anchors.fill: parent
    }

    footer: Column {
        x: 20
        Rectangle {
            height: kontakt.contentHeight + 10
            width: kontakt.contentWidth
            color: "transparent"
            Text {
                id: kontakt
                text: "☎ Kontakt"
                color: "black"
                font { family: localFont.name; pixelSize: 20 }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: ld.source="kontakt.qml"
            }
        }
        Rectangle {
            height: zamknij.contentHeight + 10
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
                onClicked: Qt.quit()
            }
        }
    }
}
