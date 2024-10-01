import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

TextField {
    id: customTextField
//    placeholderText: qsTr("Enter description")
    height: 40
    implicitHeight: 40
    bottomPadding: 6
    leftPadding: 5
    font.pixelSize: 20
    inputMethodHints: Qt.ImhDigitsOnly
    property int globalY

    background: Rectangle {
        implicitWidth: 140
//        implicitHeight: 20
        height: 40
        color: customTextField.enabled ? "white" : "#353637"
        border.color: customTextField.enabled ? "#48887B" : "transparent"
        radius: 5
    }

//    Component.onCompleted: {
//        customTextField.globalY = customTextField.mapToItem(stackView.parent, 0, 0).y
////        console.log("X: " + globalCoordinares.x + " y: " + globalCoordinares.y)
//    }

//    states: [
//        State {
//                name: "keyVisible"
//                when: (Qt.inputMethod.visible && ( (stackView.height - customTextField.globalY) < inputPanel.height))
//                PropertyChanges {
//                    target: stackView
//                    y: ( (stackView.height - customTextField.globalY) < inputPanel.height) ? (-inputPanel.height) : 0
//                }
//         },
//         State {
//                name: "keyInvisible"
//                when: ((!Qt.inputMethod.visible) && ( (stackView.height - customTextField.globalY) < inputPanel.height))
//                PropertyChanges {
//                    target: stackView
//                    y: 0
//                }
//        }
//    ]

//    onPressed: {
////        var globalCoordinares = customTextField.mapToItem(stackView.parent, 0, 0)
////        console.log("X: " + globalCoordinares.x + " y: " + globalCoordinares.y)
//        console.log("globalY:"+customTextField.globalY);
//        console.log("(window.height - customTextField.globalY):"+(stackView.height - customTextField.globalY));
//        console.log("inputPanel.height:"+inputPanel.height);
//        console.log("state:"+ ((stackView.height - customTextField.globalY) < inputPanel.height));
////        console.log("text field pressed :"+customTextField.y+", customTextField.cursorPosition:"+customTextField.cursorPosition+", customTextField.top:"+customTextField.);
//    }
}
