import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

RowLayout {
    id: root
    Layout.alignment: Qt.AlignHCenter

    property string name: ""
    property bool isDirectory: true
    property string path: ""
    signal selected(string filePath, string fileName)

    width: 500
    height: 80
    Image {
        sourceSize.height:  48
        sourceSize.width:  48
        source: root.isDirectory ? "images/folder.png" : "images/file.png"//
    }
    Text {
        text: qsTr(name)
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
             console.log("MouseArea")
          if(isDirectory) {
             FileItemsModel.goToDirectory(path);
          } else {
//              FileItemsModel.selectFile(path);
              root.selected(path, name);
          }
        }
    }
}
