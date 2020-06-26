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
    minimumHeight: mainItem.height + 80
    minimumWidth: mainItem.width + 80
    title: "Image editor"

    property bool hasImage: (paintedItem.itemWidth == 0) ? false : true
    property bool applyModeEnabled: contrastItem.checked || sharpenItem.checked

    Rectangle {
        id: wrapper
        anchors.fill: parent
    }

    FileDialog {
        id: openDialog
        title: "Select an image"
        folder: shortcuts.home
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        onAccepted: {
            var urlNoProtocol = (openDialog.fileUrl+"").replace('file:///', '');
            paintedItem.setImage(urlNoProtocol, 500, 500)
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
        width: (hasImage == true) ? paintedItem.width : 500
        height: (hasImage == true) ? paintedItem.height : 500
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 30
        PaintedItem {
            id: paintedItem
            width: itemWidth
            height: itemHeight
            anchors.top: parent.top
            anchors.left: parent.left
        }
        MouseArea {
            id: itemMouseArea
            anchors.fill: parent
            hoverEnabled: true
            property bool held: false
            property bool containsCursor: (mouseX > 0 && mouseX < parent.width && mouseY > 0 && mouseY < parent.height) ? true : false
            property int timing: 0
            onPressed: {
                if (applyModeEnabled){
                    paintedItem.addBackup()
                }
                held = true
            }
            onReleased: {
                held = false
            }
            onPositionChanged: {
                var mapped = wrapper.mapToItem(mainItem, 0, 0)
                cursor_rect.x = mouse.x - mapped.x - brushSizeItem.value / 2
                cursor_rect.y = mouse.y - mapped.y - brushSizeItem.value / 2
                if (hasImage && held){
                    if (timing != 10) {
                        timing += 1
                    } else {
                        if (containsCursor) {
                            timing = 0
                            if (contrastItem.checked) {
                                paintedItem.contrastImage(contrastItem.value, mouse.x, mouse.y, brushSizeItem.value)
                            }
                            if (sharpenItem.checked) {
                                paintedItem.sharpenImage(sharpenItem.value, mouse.x, mouse.y, brushSizeItem.value)
                            }
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id: cursor_rect
        border.color: "black"
        border.width: 1
        color: "transparent"
        visible: itemMouseArea.containsCursor
        width: brushSizeItem.value
        height: brushSizeItem.value
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
            font.pointSize: 7
            text: "Открыть"
            onClicked: {
                openDialog.open()
            }
        }

        Button {
            id: blurButton
            width: 50
            height: 40
            font.pointSize: 8
            text: "Размы-\nтие"
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
            font.pointSize: 8
            text: "Контр-\nаст"
            enabled: hasImage
            checkable: true
        }
        ContrastItem {
            id: contrastItem
            anchors.top: contrastButton.bottom
            anchors.left: contrastButton.right
            visible: contrastButton.checked
            onVisibleChanged: {
                checked = false
            }
        }
        Button {
            id: sharpenButton
            width: 50
            height: 40
            font.pointSize: 8
            text: "Резко-\nсть"
            enabled: hasImage
            checkable: true

        }
        SharpenItem {
            id: sharpenItem
            anchors.top: sharpenButton.bottom
            anchors.left: sharpenButton.right
            visible: sharpenButton.checked
            onVisibleChanged: {
                checked = false
            }
        }
        Button {
            id: saveButton
            width: 50
            height: 40
            font.pointSize: 8
            text: "Сохра-\nнить"
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

    Button {
        id: brushSizeButton
        width: 50
        height: 40
        text: "Размер \n кисти"
        checkable: true
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: buttonRow.left
        anchors.rightMargin: 10
    }

    BrushSizeItem {
        id: brushSizeItem
        anchors.top: brushSizeButton.bottom
        anchors.right: brushSizeButton.left
        visible: brushSizeButton.checked
    }

    Row {
        id: buttonRow
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10

        Button {
            id: backupButton
            width: 50
            height: 40
            font.pointSize: 8
            text: "Отмен-\nить"
            enabled: hasImage
            onClicked: {
                paintedItem.loadBackup()
            }
        }
        Button {
            id: redoButton
            width: 50
            height: 40
            font.pointSize: 8
            text: "Повтор-\nить"
            enabled: hasImage
            onClicked: {
                paintedItem.loadRedo()
            }
        }
    }
}
