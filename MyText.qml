import QtQuick 2.7


Text {
    FontLoader { id: localFont; source: "fonts/SourceSansPro-Semibold.otf" }

    font {
        family: localFont.name
        pixelSize: 20
    }
    color: "white"
}
