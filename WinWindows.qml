import QtQuick 2.0
import QtQuick.Controls 1.3

Rectangle {
    property alias newGame: newGame
    id: winWindows
    color: "white"
    border.width: 0
    border.color: "#00000000"
    anchors.centerIn: parent
    width: 200
    height: 200

    Text {
        x: 35
        y: 37
        text: "You've won!"
        font.pointSize: 18
    }

    Button {
        id: newGame
        x: 55
        y: 158
        text: "New game"
        isDefault: true
    }
}
