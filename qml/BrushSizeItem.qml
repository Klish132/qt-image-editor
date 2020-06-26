import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    id: root
    width: background.width
    height: background.height
    property int value: sizeSlider.value

    Rectangle {
        id: background
        width: sizeSlider.width + 100 + 10
        height: 100 + 10
        color: "#f5f5f5"
        radius: 10
    }

    Rectangle {
        id: sizeExampleRect
        width: sizeSlider.value
        height: sizeSlider.value
        color: "transparent"
        border.color: "black"
        border.width: 1
        anchors.horizontalCenter: background.horizontalCenter
        anchors.horizontalCenterOffset: -60
        anchors.verticalCenter: background.verticalCenter

    }


    Column {
        id: brushSizeColumn
        spacing: 10
        anchors.verticalCenter: background.verticalCenter
        anchors.horizontalCenter: background.horizontalCenter
        anchors.horizontalCenterOffset: 60

        Text {
            id: brushSizeText
            text: "Размер кисти:"
        }

        Slider {
            id: sizeSlider
            width: 120
            from: 5
            to: 100
        }
    }
}
