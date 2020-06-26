import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    id: root
    property int value: radiusSlider.value
    signal clicked()

    Rectangle {
        id: background
        width: radiusSlider.width + 10
        height: blurColumn.height + 10
        color: "#f5f5f5"
        radius: 10
    }

    Column {
        id: blurColumn
        spacing: 10
        anchors.verticalCenter: background.verticalCenter
        anchors.horizontalCenter: background.horizontalCenter

        Text {
            id: radiusText
            text: "Радиус размытия:"
        }

        Slider {
            id: radiusSlider
            width: 120
            from: 0
            to: 30
        }
        Button {
            id: applyButton
            text: "Применить"
            width: background.width/2 + 10
            height: 20
            onClicked: root.clicked()
        }
    }
}
