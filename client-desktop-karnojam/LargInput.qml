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
//    inputMethodHints: Qt.ImhDigitsOnly
    property int globalY

    background: Rectangle {
        implicitWidth: 200
        height: 40
        color: customTextField.focus ? "white" : "white"
        border.color: customTextField.focus ? "#B23850" : "#E7E3D4"
        radius: 20
    }
}
