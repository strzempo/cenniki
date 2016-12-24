import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    width: 100
    height: 100
    color: "lightgray"
    TextArea {
        id: textArea
        anchors.centerIn: parent
        text:
            "Lorem ipsum dolor sit amet, consectetur adipisicing elit,\n" +
            "sed do eiusmod tempor incididunt ut labore et dolore magna\n" +
            "aliqua. Ut enim ad minim veniam, quis nostrud exercitation\n" +
            "ullamco laboris nisi ut aliquip ex ea commodo cosnsequat.\n";
        selectByKeyboard: true
        selectByMouse: true
        wrapMode: "WordWrap"
        width: parent.width
        height: parent.height
        /*
        onCursorRectangleChanged: {
            copy()
            deselect()
        }
        */
        /*MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: {
                if(mouseArea.pressedButtons & Qt.RightButton) {
                    textArea.copy();
                }
            }
        }*/
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
/*
Rectangle {
    id: editor
    color: "lightGrey"
    width: 640; height: 480

    Rectangle {
        color: "white"
        anchors.fill: parent
        anchors.margins: 20

        BorderImage {
            id: startHandle
          //  source: "pics/startHandle.sci"
            opacity: 0.0
            width: 10
            x: edit.positionToRectangle(edit.selectionStart).x - flick.contentX-width
            y: edit.positionToRectangle(edit.selectionStart).y - flick.contentY
            height: edit.positionToRectangle(edit.selectionStart).height
        }

        BorderImage {
            id: endHandle
           // source: "pics/endHandle.sci"
            opacity: 0.0
            width: 10
            x: edit.positionToRectangle(edit.selectionEnd).x - flick.contentX
            y: edit.positionToRectangle(edit.selectionEnd).y - flick.contentY
            height: edit.positionToRectangle(edit.selectionEnd).height
        }

        Flickable {
            id: flick

            anchors.fill: parent
            contentWidth: edit.paintedWidth
            contentHeight: edit.paintedHeight
            interactive: true
            clip: true

            function ensureVisible(r) {
                if (contentX >= r.x)
                    contentX = r.x;
                else if (contentX+width <= r.x+r.width)
                    contentX = r.x+r.width-width;
                if (contentY >= r.y)
                    contentY = r.y;
                else if (contentY+height <= r.y+r.height)
                    contentY = r.y+r.height-height;
            }

            TextEdit {
                id: edit
                width: flick.width
                height: flick.height
                focus: true
                wrapMode: TextEdit.Wrap
                textFormat: TextEdit.RichText

                onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)

                text: "<h1>Text Selection</h1>"
                    +"<p>This example is a whacky text selection mechanisms, showing how these can be implemented in the TextEdit element, to cater for whatever style is appropriate for the target platform."
                    +"<p><b>Press-and-hold</b> to select a word, then drag the selection handles."
                    +"<p><b>Drag outside the selection</b> to scroll the text."
                    +"<p><b>Click inside the selection</b> to cut/copy/paste/cancel selection."
                    +"<p>It's too whacky to let you paste if there is no current selection."

            }
        }

        Item {
            id: menu
            opacity: 0.0
            width: 100
            height: 120
            anchors.centerIn: parent

            Rectangle {
                border.width: 1
                border.color: "darkBlue"
                radius: 15
                color: "#806080FF"
                anchors.fill: parent
            }

            Column {
                anchors.centerIn: parent
                spacing: 8

                Rectangle {
                    border.width: 1
                    border.color: "darkBlue"
                    color: "#ff7090FF"
                    width: 60
                    height: 16

                    Text { anchors.centerIn: parent; text: "Cut" }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: { edit.cut(); editor.state = "" }
                    }
                }

                Rectangle {
                    border.width: 1
                    border.color: "darkBlue"
                    color: "#ff7090FF"
                    width: 60
                    height: 16

                    Text { anchors.centerIn: parent; text: "Copy" }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: { edit.copy(); editor.state = "selection" }
                    }
                }

                Rectangle {
                    border.width: 1
                    border.color: "darkBlue"
                    color: "#ff7090FF"
                    width: 60
                    height: 16

                    Text { anchors.centerIn: parent; text: "Paste" }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: { edit.paste(); edit.cursorPosition = edit.selectionEnd; editor.state = "" }
                    }
                }

                Rectangle {
                    border.width: 1
                    border.color: "darkBlue"
                    color: "#ff7090FF"
                    width: 60
                    height: 16

                    Text { anchors.centerIn: parent; text: "Deselect" }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            edit.cursorPosition = edit.selectionEnd;
                            edit.deselect();
                            editor.state = ""
                        }
                    }
                }
            }
        }
    }

    states: [
        State {
            name: "selection"
            PropertyChanges { target: startHandle; opacity: 1.0 }
            PropertyChanges { target: endHandle; opacity: 1.0 }
        },
        State {
            name: "menu"
            PropertyChanges { target: startHandle; opacity: 0.5 }
            PropertyChanges { target: endHandle; opacity: 0.5 }
            PropertyChanges { target: menu; opacity: 1.0 }
        }
    ]
}
*/
