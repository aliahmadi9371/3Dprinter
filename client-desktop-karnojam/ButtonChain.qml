import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3

//RowLayout {
Rectangle {
    id: root
   width: 210
   height: 40
//   spacing: 0
   property int activeBtn: 1
   property int btnWidth: 70
   property int step: 1
   property bool topDown: BackEnd.isTopDown()
   Rectangle {
      x: 0
      width: root.btnWidth
      height: 40
      border.width: root.activeBtn == 1 ? 2 : 1
      radius: 20
      z: root.activeBtn == 1 ? 2 : 1
      color: root.activeBtn == 1 ? "#FFF2F2" : "white"
      Text {
         x: (parent.width/2) - (width/2)
         y: (parent.height/2) - (height/2)
         text: topDown ? qsTr("Pump") : qsTr("1")
         font.pointSize: root.activeBtn == 1 ? 14 : 12
         font.bold: root.activeBtn == 1 ? true : false
         color: "black"
      }

      MouseArea {
          anchors.fill: parent
          onClicked: {
              root.activeBtn = 1;
              root.step = 1;
          }
      }
   }

   Rectangle {
      width: root.btnWidth
      height: 40
      x: root.btnWidth - 10
      radius: 20
      z: root.activeBtn == 2 ? 2 : 1
      border.width: root.activeBtn == 2 ? 2 : 1
      color: root.activeBtn == 2 ? "#FFF2F2" : "white"
      Text {
         x: (parent.width/2) - (width/2)
         y: (parent.height/2) - (height/2)
         text: topDown ? qsTr("PL") : qsTr("10")
         font.pointSize: root.activeBtn == 2 ? 14 : 12
         font.bold: root.activeBtn == 2 ? true : false
         color: "black"
      }

      MouseArea {
          anchors.fill: parent
          onClicked: {
              root.activeBtn = 2;
              root.step = 10;
          }
      }
   }


   Rectangle {
      id:rectangle50
      visible: false
      width: root.btnWidth
      height: 40
      x: root.btnWidth*2 - 20
      radius: 20
      z: root.activeBtn == 3 ? 2 : 1
      border.width: root.activeBtn == 3 ? 2 : 1
      color: root.activeBtn == 3 ? "#FFF2F2" : "white"
      Text {
         x: (parent.width/2) - (width/2)
         y: (parent.height/2) - (height/2)
         text: topDown ? qsTr("Stop") : qsTr("50")
         font.pointSize: root.activeBtn == 3 ? 14 : 12
         font.bold: root.activeBtn == 3 ? true : false
         color: "black"
      }

      MouseArea {
          anchors.fill: parent
          onClicked: {
              root.activeBtn = 3;
              root.step = 50;
          }
      }
   }
   Component.onCompleted: {
//       root.topDown = BackEnd.isTopDown();
       if(!topDown)
       {
           rectangle50.visible = true;
       }
   }
}
