import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.12

TextField {
    id: customTextField
    height: 40
    implicitHeight: 40
    bottomPadding: 8
    leftPadding: 10
    font.pixelSize: 18
    inputMethodHints: Qt.ImhFormattedNumbersOnly
    property int globalY
    property int input_width: 140
    property bool shift_y: false


//    Component.onCompleted: {
//        var globalCoordinares = customTextField.mapToItem(route, 0, 0)
//        customTextField.globalY = globalCoordinares.y;
//    }

    background: Rectangle {
        implicitWidth: customTextField.input_width
        height: 40
        color: customTextField.focus ? "white" : "white"
        border.color: customTextField.focus ? "#B23850" : "#E7E3D4"
        radius: 20
    }

    onPressed: {
//        if(!customTextField.shift_y) {
//            route.y = 0;
//        } else {
//            route.y = -inputPanel.height;
//        }
    }


}
