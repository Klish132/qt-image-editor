import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import QtQuick 2.9
import "qml"
import PaintedItem 1.0

Window {
    id: window
    visible: true
    height: 640
    width: 480
    minimumHeight: mainItem.height + 20
    minimumWidth: mainItem.width + 80
    title: "Image editor"

    property bool hasImage: (paintedItem.itemWidth == 0) ? false : true

    FileDialog {
        id: openDialog
        title: "Select an image"
        folder: shortcuts.home
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        onAccepted: {
            var urlNoProtocol = (openDialog.fileUrl+"").replace('file:///', '');
            paintedItem.setImage(urlNoProtocol)
            paintedItem.fitToitem(mainItem.height, mainItem.width)
        }
    }
    FileDialog {
        id: saveDialog
        title: "Save image"
        folder: shortcuts.home
        selectExisting: false
        onAccepted: {
                var urlNoProtocol = (saveDialog.fileUrl+"").replace('file:///', '');
                paintedItem.saveImage(urlNoProtocol, saveItem.quality)
            }
        }
    Item {
        id: mainItem
        width: 500
        height: 500
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent. horizontalCenter
        anchors.horizontalCenterOffset: 30
        PaintedItem {
            id: paintedItem
            width: itemWidth
            height: itemHeight
            anchors.top: parent.top
            anchors.left: parent.left
        }
    }
    Column {
        id: buttonColumn
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10

        Button {
            id: openButton
            width: 50
            height: 40
            text: "Open"
            onClicked: {
                openDialog.open()
            }
        }
        Button {
            id: backupButton
            width: 50
            height: 40
            text: "Load Backup"
            enabled: hasImage
            onClicked: {
                paintedItem.loadBackup()
            }
        }

        Button {
            id: blurButton
            width: 50
            height: 40
            text: "Blur"
            enabled: hasImage
            checkable: true
        }
        BlurItem {
            id: blurItem
            anchors.top: blurButton.bottom
            anchors.left: blurButton.right
            visible: blurButton.checked
            onClicked: {
                paintedItem.blurImage(blurItem.value)
            }
        }
        Button {
            id: contrastButton
            width: 50
            height: 40
            text: "Contrast"
            enabled: hasImage
            checkable: true
        }
        ContrastItem {
            id: contrastItem
            anchors.top: contrastButton.bottom
            anchors.left: contrastButton.right
            visible: contrastButton.checked
            onClicked: {
                paintedItem.contrastImage(contrastItem.value)
            }
        }
        Button {
            id: saveButton
            width: 50
            height: 40
            text: "Save"
            enabled: hasImage
            checkable: true
        }
        SaveItem {
            id: saveItem
            anchors.top: saveButton.bottom
            anchors.left: saveButton.right
            visible: saveButton.checked
            property string quality: saveItem.qualityValue
            onClicked: {
                saveDialog.open()
            }
        }
    }
}
