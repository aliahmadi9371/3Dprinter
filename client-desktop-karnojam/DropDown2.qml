import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

ComboBox {
    id: control
    Component.onCompleted: {
        currentIndex = 0;
    }

    model: ["First", "Second", "Third"]
//    model: MaterialConfigModel.getNameList()
//    model: MaterialConfigModel

    delegate: ItemDelegate {
        width: control.width
        contentItem: Text {
            text: ModelCode
//            text: modelData
//            color: "#21be2b"
            color: "#B23850"
            font: control.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        highlighted: control.highlightedIndex === index
    }

    indicator: Canvas {
        id: canvas
        x: control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2
        width: 12
        height: 8
        contextType: "2d"

        Connections {
            target: control
            onPressedChanged: canvas.requestPaint()
        }

        onPaint: {
            context.reset();
            context.moveTo(0, 0);
            context.lineTo(width, 0);
            context.lineTo(width / 2, height);
            context.closePath();
//            context.fillStyle = control.pressed ? "#17a81a" : "#21be2b";
            context.fillStyle = control.pressed ? "#A0A0A0" : "#A0A0A0";
            context.fill();
        }
    }

    contentItem: Text {
        leftPadding: 13
        rightPadding: control.indicator.width + control.spacing

        text: control.displayText
        font: control.font
        color: control.pressed ? "black" : "black"
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 160
        implicitHeight: 50
        border.color: control.pressed ? "#B23850" : "#B23850"
        border.width: control.visualFocus ? 2 : 1
        radius: 25
        color: "white"
    }

    popup: Popup {
        y: control.height - 1
        width: control.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            border.color: "transparent"
            radius: 2

        }
    }
}
