import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2

Item {
    id: root
    property string qualityValue: qualityField.text
    signal clicked()

    Rectangle {
        id: background
        width: qualityField.width + 10
        height: saveColumn.height + 10
        color: "#f5f5f5"
        radius: 10
    }

    Column {
        id: saveColumn
        spacing: 10
        anchors.verticalCenter: background.verticalCenter
        anchors.horizontalCenter: background.horizontalCenter

        Text {
            id: saveText
            text: "Качество:"
        }

        TextField {
            id: qualityField
            width: 120
            height: 30
            font.pixelSize: 16
            placeholderText: "100"
            selectByMouse: true
        }
        Button {
            id: saveButton
            text: "Сохранить"
            width: background.width/2 + 10
            height: 20
            onClicked: root.clicked()
        }
    }
}
