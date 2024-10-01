import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtGraphicalEffects 1.12

Rectangle {
    id: root
     implicitWidth: 150
     height: 45
//     width: childrenRect.width + 30
//     height: childrenRect.height + 10
     color: "#FCECEC"
     border.color: "#C29B9B"
     radius: 10
//     opacity: 0.2
     layer.enabled: true
     layer.effect: DropShadow {
             transparentBorder: true
             horizontalOffset: 2
             verticalOffset: 7
             color: "#C95757"
             opacity: 0.7
     }

     property string text: "Button Text"
     property int fontSize: 14
     signal buttonPressed();

     Text {
        x: (root.width/2) - (width/2)
        y: (root.height/2) - (height/2)
        text: qsTr(root.text)
        font.pointSize: root.fontSize
        font.bold: true
//        verticalAlignment: Text.AlignVCenter
//        horizontalAlignment: Text.AlignHCenter
        color: "black"
     }

     MouseArea {
         anchors.fill: parent
         onClicked: {
             buttonPressed();
         }
     }
}
