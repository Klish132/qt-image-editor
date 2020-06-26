import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    id: root
    property int value: contrastSlider.value
    property bool checked: false

    Rectangle {
        id: background
        width: contrastSlider.width + 10
        height: contrastColumn.height + 10
        color: "#f5f5f5"
        radius: 10
    }

    Column {
        id: contrastColumn
        spacing: 10
        anchors.verticalCenter: background.verticalCenter
        anchors.horizontalCenter: background.horizontalCenter

        Text {
            id: contrastText
            text: "Значение контраста:"
        }

        Slider {
            id: contrastSlider
            width: 120
            from: 100
            to: 255
        }
        Button {
            id: applyButton
            text: "Применить"
            width: background.width/2 + 10
            height: 20
            checked: root.checked
            onClicked: {
                root.checked = !root.checked
            }
        }
    }
}
