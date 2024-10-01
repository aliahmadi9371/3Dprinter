import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

RowLayout {
    property var widthArray: []
   width: parent.width
   spacing: 10
   Repeater {
       model: ["  Name  ", "Layer Thickness", "Burn In Layers", "Material Config", "Normal CureTime", "Burn Intensity",
           "Intensity", "  Delete  ", "  Edit  "]
       Text {
           id: headerLabel
           Layout.alignment: Qt.AlignHCenter
           text: qsTr(modelData+"")
           font.pointSize: 16
           font.bold: true
//           width: Math.max(100, bar.width / 4)
           Component.onCompleted: {
               widthArray.push(width);
           }
       }
   }
}
