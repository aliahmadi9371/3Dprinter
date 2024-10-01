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
    property int slideNum: 1
//    header: PageHeader {
//    }

    Flickable {
        width: root.width
        height: root.height
        contentWidth: root.width; contentHeight: root.height*1.7
//        ScrollBar.horizontal: ScrollBar { id: hbar; active: vbar.active }
        ScrollBar.vertical: ScrollBar { id: vbar; active: hbar.active }
        clip: true

        ColumnLayout {
          width: parent.width*0.9
          Layout.alignment: Qt.AlignHCenter
          x: root.textLeftMargin
          y:10
    //      topPadding: 10
    //      Layout.topPadding: 10
          spacing: 10

          RowLayout {
              spacing: 10

              Button{
                  text: qsTr("Go Home")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Green
                  onClicked: {
                      ackDialog.open();
    //                  if(BackEnd.goHomeProjectorCalib()) {

    //                  } else {

    //                  }
                  }

              }

              Item {
                  width: 250
                  Text {
                      y: (parent.height - height)/2
                      text: qsTr("Home value is (mm):")
                      font.pointSize: 14
                  }
              }



          }

          RowLayout {
              spacing: 10
              Item {
                  width: 250
                  Text {
                      y: (parent.height - height)/2
                      text: qsTr("Position Above Zero (mm):")
                      font.pointSize: 14
                  }
              }

              SmallInput {
                 id: positionInput
              }
              Button{
                  text: qsTr("Go")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Blue
                  onClicked: {
                      if(BackEnd.goPositionProjectorCalib(parseInt(positionInput.text))) {

                      } else {

                      }
                  }
              }
          }
          RowLayout {
              spacing: 10
              Item {
                  width: 250
                  visible: !BackEnd.isTopDown()

                  Text {
                      y: (parent.height - height)/2
                      text: qsTr("Eject Calibration")
                      font.pointSize: 14
                  }
              }
              Button{

                  visible: !BackEnd.isTopDown()
                  text: qsTr("Up")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Blue
                  onClicked: {
                      if(BackEnd.ejectUpProjectorCalib()) {

                      } else {

                      }
                  }
              }
              Button{

                  visible: !BackEnd.isTopDown()
                  text: qsTr("Down")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Blue
                  onClicked: {
                      if(BackEnd.ejectDownProjectorCalib()) {

                      } else {

                      }
                  }
              }

              Item {
                  width: 250
                  Text {
                      visible: BackEnd.isTopDown()
                      y: (parent.height - height)/2
                      text: qsTr("Move Recoater")
                      font.pointSize: 14
                  }
              }
              Button{
                  visible: BackEnd.isTopDown()
                  text: qsTr("Front")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Blue
                  onClicked: {

                      console.log("Up clicked")
                     if(BackEnd.manualMV(2, 1)) {

                     } else {

                     }

                  }
              }

              Button{
                  visible: BackEnd.isTopDown()
                  text: qsTr("Back")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Blue
                  onClicked: {

                      console.log("Down clicked")
                     if(BackEnd.manualMV(2, 0)) {

                     } else {

                     }

                  }
              }

          }

          RowLayout {
              spacing: 10

              Item {
                  width: 250
                  Text {
                      visible: BackEnd.isTopDown()
                      y: (parent.height - height)/2
                      text: qsTr("Material level (mm)")
                      font.pointSize: 14

                  }
              }
              SmallInput {
                 id: materialLevelInput
                 visible: BackEnd.isTopDown()
              }
              Button{
                  visible: BackEnd.isTopDown()
                  text: qsTr("start")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Blue
                  onClicked: {
                      if(BackEnd.materialLevelProjectorCalib(parseFloat(materialLevelInput.text))) {

                      } else {

                      }
                  }
              }

    //          Button{
    //              visible: BackEnd.isTopDown()
    //              text: qsTr("Deplete")
    //              Layout.alignment: Qt.AlignHCenter
    //              highlighted: true
    //              Material.background: Material.Red
    //              onClicked: {

    //              }
    //          }

          }

          RowLayout {
              spacing: 10

              Item {
                  width: 250
                  Text {
                      visible: BackEnd.isTopDown()
                      y: (parent.height - height)/2
                      text: qsTr("SRV(sec)")
                      font.pointSize: 14
                  }
              }

              SmallInput {
                 id: vacuumInput
                 visible: BackEnd.isTopDown()
              }
              Button{
                  visible: BackEnd.isTopDown()
                  text: qsTr("start")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Blue
                  onClicked: {
                      if(BackEnd.fillVacuumProjectorCalib(parseFloat(vacuumInput.text))) {

                      } else {

                      }
                  }
              }

    //          Button{
    //              visible: BackEnd.isTopDown()
    //              text: qsTr("Deplete")
    //              Layout.alignment: Qt.AlignHCenter
    //              highlighted: true
    //              Material.background: Material.Red
    //              onClicked: {

    //              }
    //          }

          }


          RowLayout {
              spacing: 10

              Item {
                  width: 250
                  Text {
                      id: sensorText
                      visible: BackEnd.isTopDown()
                      y: (parent.height - height)/2
                      text: qsTr("Sensor Data:")
                      font.pointSize: 14
                  }
              }


              Button{
                  visible: BackEnd.isTopDown()
                  text: qsTr("Update")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Blue
                  onClicked: {
                      sensorText.text = qsTr("Sensor Data:" + BackEnd.getSensorProjectorCalib().toFixed(4));
                  }
              }

          }

          RowLayout {
              spacing: 10

              Button{
                  text: qsTr("Start Projector Calibration")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Green
                  onClicked: {
                      //                  Q_INVOKABLE bool turnOffProjectorCalib();
                      //                  Q_INVOKABLE bool MaterialTestProjectorCalib(int position, int matPat);
                      if(BackEnd.startProjectorCalib()) {

                      } else {

                      }
                  }
              }
          }

    //      Button{
    //          text: qsTr("Change Mask")
    //          Layout.alignment: Qt.AlignHCenter
    //          highlighted: true
    //          Material.background: Material.Blue
    //          onClicked: {
    //              route.currentIndex = 6;
    //          }
    //      }

          RowLayout {
              spacing: 10
              Item {
                  width: 250
                  Text {
                      y: (parent.height - height)/2
                      text: qsTr("Projector Intensity (uw/cm2):")
                      font.pointSize: 14
                  }
              }

              SmallInput {
                  id: intensityText
              }
              Button{
                  text: qsTr("Set")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Blue
                  onClicked: {
                      if(BackEnd.ledIntensityProjectorCalib(parseInt(intensityText.text))) {

                      } else {

                      }
                  }
              }
          }



          RowLayout {
              spacing: 10
              Item {
                  width: 250
                  Text {
                      y: (parent.height - height)/2
                      text: qsTr("LED")
                      font.pointSize: 14
                  }
              }
              Button{
                  text: qsTr("Turn On")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Blue
                  onClicked: {
                      if(BackEnd.ledTurnOnProjectorCalib()) {

                      } else {

                      }
                  }
              }
              Button{
                  text: qsTr("Turn Off")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Red
                  onClicked: {
                      if(BackEnd.ledTurnOffProjectorCalib()) {

                      } else {

                      }
                  }
              }
          }

          RowLayout {
              spacing: 10
              Item {
                  width: 250
                  Text {
                      y: (parent.height - height)/2
                      text: qsTr("Projector Test Pattern")
                      font.pointSize: 14
                  }
              }
              DropDownListModel {
                  id: pattenDropDown
                  model: ["Show Grid", "Show Rectangle", "Show Circle", "Show Text"]
              }
              Button{
                  text: qsTr("Set")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Blue
                  onClicked: {
                    if(BackEnd.setPattern(pattenDropDown.currentIndex+1)) {

                     } else {

                     }
                  }
              }
          }

          RowLayout {
              spacing: 10
              Item {
                  width: 250
                  Text {
                      text: qsTr("Material Test")
                      font.pointSize: 14
                  }
              }
              SmallInput {
                 id: matPosition
                 shift_y: true
              }
              Button{
                  text: qsTr("Set")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Blue
                  onClicked: {
                    if(BackEnd.materialTestProjectorCalib(parseInt(matPosition.text), pattenDropDown.currentIndex+1)) {

                     } else {

                     }
                  }
              }
          }
          RowLayout {
              Layout.alignment: Qt.AlignLeft
              spacing: 10
              Button{
                  text: qsTr("Disconnect")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Red
                  onClicked: {
                      disconnectMessage.open();
                  }
              }
              Button{
                  text: qsTr("Finish")
                  Layout.alignment: Qt.AlignHCenter
                  highlighted: true
                  Material.background: Material.Red
                  onClicked: {
                      if(BackEnd.finishProjectorCalib()) {

                      } else {

                      }
                  }
              }
          }



          Popup{
              id: ackDialog
      //        anchors.centerIn: parent
              x: (parent.width - width)/2
              y: 50
              width: 400
              height: 200
              modal: true
              focus: true
              contentItem: ColumnLayout {
                  width: parent.width*0.9
                  Layout.alignment: Qt.AlignHCenter
                  spacing: 5
                  Text {
                      Layout.alignment: Qt.AlignHCenter
                      text: qsTr("Are you sure?")
                      font.pixelSize: 22
                  }
                  RowLayout {
                      width: parent.width
                      Layout.alignment: Qt.AlignHCenter
                      spacing: 30
                      Button {
                          text: qsTr("No")
                          highlighted: true
                          Material.background: Material.Red
                          onClicked: {
                             ackDialog.close();
                          }
                      }
                      Button {
                          text: qsTr("Yes")
                          highlighted: true
                          Material.background: Material.Green
                          onClicked: {
                              if(BackEnd.goHomeProjectorCalib()) {

                              } else {

                              }
                              ackDialog.close();
                          }
                      }
                  }
              }
          }

        }
    }

}
