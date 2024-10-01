import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4


Page {
    id: root
    width: parent.width
    property int textLeftMargin: 40
    property int zoneNum: 1
    property int zoneValue: 4

    ColumnLayout {
      width: parent.width*0.9
      Layout.alignment: Qt.AlignHCenter
      x: root.textLeftMargin
      y:10
      spacing: 10

      RowLayout {
          width: parent.width
          spacing: 25
          ColumnLayout {
              width: parent.width/2
              RowLayout {
                  width: parent.width
                  spacing: 10
                  Button{
                      text: qsTr("Start Projector")
                      highlighted: true
                      Material.background: Material.Green
                      onClicked: {
                      }
                  }
                  Button{
                      text: qsTr("Stop Projector")
                      highlighted: true
                      Material.background: Material.Red
                      onClicked: {
                      }
                  }
              }

              RowLayout {
                  width: parent.width
                  spacing: 10
                  Text {
                      text: qsTr("LED")
                      font.pointSize: 14
                  }
                  Button{
                      text: qsTr("Turn on")
                      highlighted: true
                      Material.background: Material.Green
                      onClicked: {
                      }
                  }
                  Button{
                      text: qsTr("Turn off")
                      highlighted: true
                      Material.background: Material.Red
                      onClicked: {
                      }
                  }
              }
          }

          ColumnLayout {
              width: parent.width*0.40
              Text {
                  font.pointSize: 16
                  text: qsTr("Circle Zone")
                  font.bold: true
              }
              RowLayout {
                  width: parent.width
                  Item {
                      width: 100
                      Text {
//                          x: (parent.width-width)/2
                          y: (parent.height-height)/2
                          font.pointSize: 16
                          text: qsTr("Number:")
                      }
                  }
                  Button{
                      text: qsTr("-")
                      highlighted: true
                      Material.background: Material.Red
//                          font.pixelSize: 30
                      font.pointSize: 30
                      font.bold: true
                      bottomPadding: 0
                      topPadding: 0
                      leftPadding: 0
                      rightPadding: 0
                      onClicked: {
                          root.zoneNum--;
                          if(root.zoneNum === -1) {
                              root.zoneNum = BackEnd.getZonQuantity();
                              root.zoneValue = BackEnd.getZonValue(root.zoneNum);
                          }
                      }
                  }
                  Item {
                      width: 40
                      Text {
                          x: (parent.width-width)/2
                          y: (parent.height-height)/2
                          font.pointSize: 16
                          text: qsTr(root.zoneNum+"")
                      }
                  }
                  Button{
                      text: qsTr("+")
                      highlighted: true
                      Material.background: Material.Green
//                          font.pixelSize: 30
                      font.pointSize: 30
                      font.bold: true
                      bottomPadding: 0
                      topPadding: 0
                      leftPadding: 0
                      rightPadding: 0
                      onClicked: {
                          root.zoneNum++;
                          if(root.zoneNum === BackEnd.getZonQuantity()) {
                              root.zoneNum = 0;
                              root.zoneValue = BackEnd.getZonValue(root.zoneNum);
                          }
                      }
                  }

              }

              RowLayout {
                  width: parent.width
                  Item {
                      width: 100
                      Text {
//                          x: (parent.width-width)/2
                          y: (parent.height-height)/2
                          font.pointSize: 16
                          text: qsTr("Value:")
                      }
                  }
                      Button{
                          text: qsTr("-")
                          highlighted: true
                          Material.background: Material.Red
//                          font.pixelSize: 30
                          font.pointSize: 30
                          font.bold: true
                          bottomPadding: 0
                          topPadding: 0
                          leftPadding: 0
                          rightPadding: 0
                          onClicked: {
                              root.zoneValue--;
                              if(root.zoneValue === -1) {
                                  root.zoneValue = 255;
                              }
                          }
                      }
                      Item {
                          width: 40
                          Text {
                              x: (parent.width-width)/2
                              y: (parent.height-height)/2
                              font.pointSize: 16
                              text: qsTr(root.zoneValue+"")
                          }
                      }

                      Button{
                          text: qsTr("+")
                          highlighted: true
                          Material.background: Material.Green
//                          font.pixelSize: 30
                          font.pointSize: 30
                          font.bold: true
                          bottomPadding: 0
                          topPadding: 0
                          leftPadding: 0
                          rightPadding: 0
                          onClicked: {
                              root.zoneValue++;
                              if(root.zoneValue === 256) {
                                  root.zoneValue = 0;
                              }
                          }
                      }
              }

              Button{
                  text: qsTr("Set Config")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Green
                  onClicked: {
                     BackEnd.setZoonValue(root.zoonNum, root.zoonValue);
                  }
              }
          }
      }

      Image {
          id: previewImg
          sourceSize.width:  window.width*6/8
          source: "images/preview.png"
      }

    }
}
