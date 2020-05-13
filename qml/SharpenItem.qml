import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    id: root
    property int value: sharpenSlider.value
    signal clicked()

    Rectangle {
        id: background
        width: sharpenSlider.width + 10
        height: sharpenColumn.height + 10
        color: "#f5f5f5"
        radius: 10
    }

    Column {
        id: sharpenColumn
        spacing: 10
        anchors.verticalCenter: background.verticalCenter
        anchors.horizontalCenter: background.horizontalCenter

        Text {
            id: sharpenText
            text: "Sharpen:"
        }

        Slider {
            id: sharpenSlider
            width: 120
            from: 10
            to: 90
        }
        Button {
            id: applyButton
            text: "Apply"
            width: background.width/2
            height: 20
            onClicked: root.clicked()
        }
    }
}
