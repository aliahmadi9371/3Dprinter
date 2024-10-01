import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

ColumnLayout{
    id: root
    Layout.topMargin: 10
    width: parent.width*0.7
    Layout.alignment: Qt.AlignHCenter
    property string label: ""
    property string btnLabel: ""
    property string placeHolder: ""
    property string inputText: ""
    signal accept();
    signal cancel();
    RowLayout {

        Layout.alignment: Qt.AlignHCenter
        spacing: 20

    //    Component.onCompleted: {
    //        console.log("Qt.fontFamilies() :")
    //        console.log(Qt.fontFamilies())
    //        console.log("my text font family");
    //        console.log(testText.font.family);
    //    }



        Text {
            id: testText
            y: (parent.height/2) - (height/2)
            text: qsTr(root.label)
            font.pointSize: 18
            font.bold: true
        }
        LargInput {
            id: textInput
            placeholderText: qsTr(root.placeHolder)
            text: qsTr(root.inputText)
            y: (parent.height-height)/2

        }

    }
    RowLayout {

        Layout.alignment: Qt.AlignHCenter
        spacing: 20

        Button {
            text: qsTr(root.btnLabel)
            highlighted: true
            Material.background: Material.Green
            onClicked: {
                root.inputText = textInput.text;
                accept();
            }
        }
        Button {
            text: "cancel"
            highlighted: true
            Material.background: Material.Red
            onClicked: {
                cancel();
            }
        }
    }

}
