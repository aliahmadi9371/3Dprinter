import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Page {
    id: root
    width: parent.width
    property int textLeftMargin: 40

//    header: PageHeader {
//    }

    ColumnLayout {
      width: parent.width
      Layout.topMargin: 10
      Component.onCompleted: {
           MotionConfigModel.refreshData();
      }

//      NameForm {
//          label: "Motion Name"
//          placeHolder: "Motion Name"
//          btnLabel: "Add New"
//          onAccept: {
//              motionConfigPopup.name = inputText;
//              motionConfigPopup.newOrEdit = true;
//              motionConfigPopup.open();
//          }
//      }
      Button{
          text: "ADD a New Motion"
          font.pixelSize: 22
          Layout.alignment: Qt.AlignHCenter
          highlighted: true
          Material.background: Material.Green
          onClicked: {
              motionNamePopup.open();
          }
      }

      ToolSeparator {
          orientation: Qt.Horizontal
          implicitWidth: parent.width*0.9
           Layout.alignment: Qt.AlignHCenter
      }

      Flickable {
          width: window.width*7/8
          height: window.width*5/8
          contentWidth: 1450; contentHeight: 700
          ScrollBar.horizontal: ScrollBar { id: hbar; active: vbar.active }
          ScrollBar.vertical: ScrollBar { id: vbar; active: hbar.active }
          clip: true
          ListView {
              id: materialList
              x: 10
              Layout.leftMargin: 10
              width: 1000 //parent.width*0.95;
              height: 500
              spacing: 10
              Layout.alignment: Qt.AlignHCenter
              headerPositioning: ListView.OverlayHeader
              header: MotionHeader {
              }

              model: MotionConfigModel

              delegate: MotionConfig {
                  onMotionDelete: {
                      deleteDialog.motionId = motionId;
                      deleteDialog.open();
                  }

                  onConfigSelected: {
                      motionConfigPopup.newOrEdit = false;
//                      motionConfigPopup.name = configName;
                      motionConfigPopup.name = configVars[0];

                      motionConfigPopup.motionConfigId = configVars[1]; //configId;
                      motionConfigPopup.layer_Z_Raise1 = configVars[2]; //configLayer_Z_Raise1;
                      motionConfigPopup.layer_Z_Raise2 = configVars[3]; //configLayer_Z_Raise2;
                      motionConfigPopup.layer_Z_Lower1 = configVars[4]; //configLayer_Z_Lower1;
                      motionConfigPopup.layer_Z_Lower2 = configVars[5]; //configLayer_Z_Lower2;
                      motionConfigPopup.layer_Tilt_Raise1 = configVars[6]; //configLayer_Tilt_Raise1;
                      motionConfigPopup.layer_Tilt_Raise2 = configVars[7]; //configLayer_Tilt_Raise2;
                      motionConfigPopup.layer_Tilt_Lower1 = configVars[8]; //configLayer_Tilt_Lower1;
                      motionConfigPopup.layer_Tilt_Lower2 = configVars[9]; //configLayer_Tilt_Lower2;
                      motionConfigPopup.layer_Overlift1 = configVars[10]; //configLayer_Overlift1;
                      motionConfigPopup.layer_Overlift2 = configVars[11]; //configLayer_Overlift2
                      motionConfigPopup.layer_Breathe1 = configVars[12]; //configLayer_Breathe1;
                      motionConfigPopup.layer_Breathe2 = configVars[13]; //configLayer_Breathe2;
                      motionConfigPopup.layer_Settle1 = configVars[14]; //configLayer_Settle1;
                      motionConfigPopup.layer_Settle2 = configVars[15]; //configLayer_Settle2;
                      motionConfigPopup.layer_Tilt_Percent1 = configVars[16]; //configLayer_Tilt_Percent1;
                      motionConfigPopup.layer_Tilt_Percent2 = configVars[17]; //configLayer_Tilt_Percent2;
                      motionConfigPopup.cut_Off_Layers = configVars[18]; //cut_Off_Layers;
                      motionConfigPopup.final_OverLift = configVars[19]; //final_OverLift;
                      motionConfigPopup.base_Layer_settle = configVars[20]; //base_Layer_settle;

                      motionConfigPopup.open();

//                      motionConfigPopup.newOrEdit = false;
//                      motionConfigPopup.name = configName;
//                      motionConfigPopup.motionConfigId = configId;
//                      motionConfigPopup.layer_Breathe1 = configLayer_Breathe1;
//                      motionConfigPopup.layer_Breathe2 = configLayer_Breathe2;
//                      motionConfigPopup.layer_Overlift1 = configLayer_Overlift1;
//                      motionConfigPopup.layer_Overlift2 = configLayer_Overlift2;
//                      motionConfigPopup.layer_Settle1 = configLayer_Settle1;
//                      motionConfigPopup.layer_Settle2 = configLayer_Settle2;
//                      motionConfigPopup.layer_Tilt_Lower1 = configLayer_Tilt_Lower1;
//                      motionConfigPopup.layer_Tilt_Lower2 = configLayer_Tilt_Lower2;
//                      motionConfigPopup.layer_Tilt_Percent1 = configLayer_Tilt_Percent1;
//                      motionConfigPopup.layer_Tilt_Percent2 = configLayer_Tilt_Percent2;
//                      motionConfigPopup.layer_Tilt_Raise1 = configLayer_Tilt_Raise1;
//                      motionConfigPopup.layer_Tilt_Raise2 = configLayer_Tilt_Raise2;
//                      motionConfigPopup.layer_Z_Lower1 = configLayer_Z_Lower1;
//                      motionConfigPopup.layer_Z_Lower2 = configLayer_Z_Lower2;
//                      motionConfigPopup.layer_Z_Raise1 = configLayer_Z_Raise1;
//                      motionConfigPopup.layer_Z_Raise2 = configLayer_Z_Raise2;
//                      motionConfigPopup.cut_Off_Layers = cut_Off_Layers;
//                      motionConfigPopup.final_OverLift = final_OverLift;
//                      motionConfigPopup.base_Layer_settle = base_Layer_settle;
//                      motionConfigPopup.open();
                  }
                         motionConfigId: model.index+1
                         name: model.Name
                         layer_Breathe1: model.Layer_Breathe1
                         layer_Breathe2: model.Layer_Breathe2
                         layer_Overlift1: model.Layer_Overlift1
                         layer_Overlift2: model.Layer_Overlift2
                         layer_Settle1: model.Layer_Settle1
                         layer_Settle2: model.Layer_Settle2
                         layer_Tilt_Lower1: model.Layer_Tilt_Lower1
                         layer_Tilt_Lower2: model.Layer_Tilt_Lower2
                         layer_Tilt_Percent1: model.Layer_Tilt_Percent1
                         layer_Tilt_Percent2: model.Layer_Tilt_Percent2
                         layer_Tilt_Raise1: model.Layer_Tilt_Raise1
                         layer_Tilt_Raise2: model.Layer_Tilt_Raise2
                         layer_Z_Lower1: model.Layer_Z_Lower1
                         layer_Z_Lower2: model.Layer_Z_Lower2
                         layer_Z_Raise1: model.Layer_Z_Raise1
                         layer_Z_Raise2: model.Layer_Z_Raise2
                         cut_Off_Layers: model.Cut_Off_Layers
                         final_OverLift: model.Final_OverLift
                         base_Layer_settle: model.Base_Layer_settle

               }

          }

      }



    }

    Popup{
        id: motionNamePopup
        x: (parent.width - width)/2
        y: 50
        width: 400
        height: 200
        modal: true
        focus: true
//        closePolicy: Popup.NoAutoClose
        contentItem: ColumnLayout {
            width: parent.width*0.9
            Layout.alignment: Qt.AlignHCenter
            spacing: 5

            NameForm {
                label: "New Motion"
                placeHolder: "Motion Name"
                btnLabel: "Next"
                onAccept: {
                    if (inputText!="")
                    {
                        motionConfigPopup.name = inputText;
                        motionConfigPopup.newOrEdit = true;
                        motionConfigPopup.open();
                        motionNamePopup.close();
                    }
                }
                onCancel: {
                    motionNamePopup.close();
                }
            }

        }
    }

    Popup{
        id: deleteDialog
//        anchors.centerIn: parent
        x: (parent.width - width)/2
        y: 50
        width: 400
        height: 200
        modal: true
        focus: true
        property int motionId: 1
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
                       deleteDialog.close();
                    }
                }
                Button {
                    text: qsTr("Yes")
                    highlighted: true
                    Material.background: Material.Green
                    onClicked: {
                        MotionConfigModel.removeConfig(deleteDialog.motionId);
                        deleteDialog.close();
                    }
                }
            }
        }
    }

    Popup{
        id: motionConfigPopup
        x: (parent.width - width)/2
        y: 50
        width: 650
        height: 400

        modal: false
        focus: true
        closePolicy: Popup.CloseOnEscape //| Popup.CloseOnPressOutside
        property int motionConfigId: 1
        property string name: ""
        property int layer_Z_Raise1
        property int layer_Z_Raise2
        property int layer_Z_Lower1
        property int layer_Z_Lower2
        property int layer_Tilt_Raise1
        property int layer_Tilt_Raise2
        property int layer_Tilt_Lower1
        property int layer_Tilt_Lower2
        property int layer_Overlift1
        property int layer_Overlift2
        property int layer_Breathe1
        property int layer_Breathe2
        property int layer_Settle1
        property int layer_Settle2
        property int layer_Tilt_Percent1
        property int layer_Tilt_Percent2
        property int cut_Off_Layers
        property int final_OverLift
        property int base_Layer_settle
        property bool newOrEdit: false

        contentItem: ColumnLayout {
            width: parent.width*0.95
            Layout.alignment: Qt.AlignHCenter
           RowLayout{
               width: parent.width
               spacing: 15
               ColumnLayout {
                  width: parent.width*0.45
                  RowLayout {
                      width: parent.width
                      Item {
                          width: 125
                          Text {
                              text: qsTr("Layer Z Raise ")
                              font.pointSize: 12
                              y: (parent.height-height)/2
                          }
                      }
                      SmallInput {
                          id: mcLayer_Z_Raise1
                          text: qsTr(motionConfigPopup.layer_Z_Raise1+"")
                      }
                      SmallInput {
                          id: mcLayer_Z_Raise2
                          text: qsTr(motionConfigPopup.layer_Z_Raise2+"")
                      }
                  }

                  RowLayout {
                      width: parent.width
                      Item {
                          width: 125
                          Text {
                              text: qsTr("Layer Z Lower ")
                              font.pointSize: 12
                              y: (parent.height-height)/2
                          }
                      }
                      SmallInput {
                          id: mcLayer_Z_Lower1
                          text: qsTr(motionConfigPopup.layer_Z_Lower1+"")
                      }
                      SmallInput {
                          id: mcLayer_Z_Lower2
                          text: qsTr(motionConfigPopup.layer_Z_Lower2+"")
                      }
                  }

                  RowLayout{
                      width: parent.width
                      Item {
                          width: 125
                          Text {
                              text: qsTr("Layer Tilt Raise ")
                              font.pointSize: 12
                              y: (parent.height-height)/2
                          }
                      }
                      SmallInput {
                          id: mcLayer_Tilt_Raise1
                          text: qsTr(motionConfigPopup.layer_Tilt_Raise1+"")
                      }
                      SmallInput {
                          id: mcLayer_Tilt_Raise2
                          text: qsTr(motionConfigPopup.layer_Tilt_Raise2+"")
                      }
                  }

                  RowLayout{
                      width: parent.width
                      Item {
                          width: 125
                          Text {
                              text: qsTr("Layer Tilt Lower ")
                              font.pointSize: 12
                              y: (parent.height-height)/2
                          }
                      }
                      SmallInput {
                          id: mcLayer_Tilt_Lower1
                          text: qsTr(motionConfigPopup.layer_Tilt_Lower1+"")
                      }
                      SmallInput {
                          id: mcLayer_Tilt_Lower2
                          text: qsTr(motionConfigPopup.layer_Tilt_Lower2+"")
                      }
                  }

                  RowLayout{
                      width: parent.width
                      Item {
                          width: 125
                          Text {
                              text: qsTr("Layer Overlift1 ")
                              font.pointSize: 12
                              y: (parent.height-height)/2
                          }
                      }
                      SmallInput {
                          id: mcLayer_Overlift1
                          text: qsTr(motionConfigPopup.layer_Overlift1+"")
                          shift_y: true
                      }
                      SmallInput {
                          id: mcLayer_Overlift2
                          text: qsTr(motionConfigPopup.layer_Overlift2+"")
                          shift_y: true
                      }
                  }

                  RowLayout{
                      width: parent.width
                      Item {
                          width: 125
                          Text {
                              text: qsTr("Layer Breathe ")
                              font.pointSize: 12
                              y: (parent.height-height)/2
                          }
                      }
                      SmallInput {
                          id: mcLayer_Breathe1
                          text: qsTr(motionConfigPopup.layer_Breathe1+"")
                          shift_y: true
                      }
                      SmallInput {
                          id: mcLayer_Breathe2
                          text: qsTr(motionConfigPopup.layer_Breathe2+"")
                          shift_y: true
                      }
                  }

               }
               ColumnLayout {
                  width: parent.width*0.45
                  RowLayout{
                      width: parent.width
                      Item {
                          width: 125
                          Text {
                              text: qsTr("Layer Settle ")
                              font.pointSize: 12
                              y: (parent.height-height)/2
                          }
                      }
                      SmallInput {
                          id: mcLayer_Settle1
                          text: qsTr(motionConfigPopup.layer_Settle1+"")
                      }
                      SmallInput {
                          id: mcLayer_Settle2
                          text: qsTr(motionConfigPopup.layer_Settle2+"")
                      }
                  }

                  RowLayout{
                      width: parent.width
                      Item {
                          width: 125
                          Text {
                              text: qsTr("Layer Tilt Percent ")
                              font.pointSize: 12
                              y: (parent.height-height)/2
                          }
                      }
                      SmallInput {
                          id: mcLayer_Tilt_Percent1
                          text: qsTr(motionConfigPopup.layer_Tilt_Percent1+"")
                      }
                      SmallInput {
                          id: mcLayer_Tilt_Percent2
                          text: qsTr(motionConfigPopup.layer_Tilt_Percent2+"")
                      }
                  }

                  RowLayout{
                      width: parent.width
                      Item {
                          width: 125
                          Text {
                              text: qsTr("Cut Off Layers ")
                              font.pointSize: 12
                              y: (parent.height-height)/2
                          }
                      }
                      MediumInput {
                          id: mcCut_Off_Layers
                          input_width: 180
                          text: qsTr(motionConfigPopup.cut_Off_Layers+"")
                      }
                  }

                  RowLayout{
                      width: parent.width
                      Item {
                          width: 125
                          Text {
                              text: qsTr("Final OverLift ")
                              font.pointSize: 12
                              y: (parent.height-height)/2
                          }
                      }
                      MediumInput {
                          id: mcFinal_OverLift
                          text: qsTr(motionConfigPopup.final_OverLift+"")
                          input_width: 180
                      }
                  }

                  RowLayout{
                      width: parent.width
                      Item {
                          width: 125
                          Text {
                              text: qsTr("Base Layer settle ")
                              font.pointSize: 12
                              y: (parent.height-height)/2
                          }
                      }
                      MediumInput {
                          id: mcBase_Layer_settle
                          text: qsTr(motionConfigPopup.base_Layer_settle+"")
                          input_width: 180
                          shift_y: true
                      }
                  }

               }

           }

           RowLayout{
               Layout.alignment: Qt.AlignHCenter
               height: 70

               Button{
                   text: qsTr("Cancel")
                   Layout.alignment: Qt.AlignHCenter
                   highlighted: true
                   Material.background: Material.Red
                   onClicked: {
                     motionConfigPopup.close();
                   }
               }
               Button{
                   text: motionConfigPopup.newOrEdit ? qsTr("Create") : qsTr("Edit")
                   Layout.alignment: Qt.AlignHCenter
                   highlighted: true
                   Material.background: Material.Green
                   onClicked: {
                      if(motionConfigPopup.newOrEdit) {
                        MotionConfigModel.makeNewConfig(motionConfigPopup.name, parseInt(mcLayer_Z_Raise1.text),
                           parseInt(mcLayer_Z_Raise2.text), parseInt(mcLayer_Z_Lower1.text), parseInt(mcLayer_Z_Lower2.text),
                           parseInt(mcLayer_Tilt_Raise1.text), parseInt(mcLayer_Tilt_Raise2.text), parseInt(mcLayer_Tilt_Lower1.text),
                           parseInt(mcLayer_Tilt_Lower2.text), parseInt(mcLayer_Overlift1.text), parseInt(mcLayer_Overlift2.text),
                           parseInt(mcLayer_Breathe1.text), parseInt(mcLayer_Breathe2.text), parseInt(mcLayer_Settle1.text),
                           parseInt(mcLayer_Settle2.text), parseInt(mcLayer_Tilt_Percent1.text), parseInt(mcLayer_Tilt_Percent2.text),
                           parseInt(mcCut_Off_Layers.text), parseInt(mcFinal_OverLift.text), parseInt(mcBase_Layer_settle.text) );
                      } else {
                          MotionConfigModel.setConfig(motionConfigPopup.motionConfigId, motionConfigPopup.name, parseInt(mcLayer_Z_Raise1.text),
                                                      parseInt(mcLayer_Z_Raise2.text), parseInt(mcLayer_Z_Lower1.text), parseInt(mcLayer_Z_Lower2.text),
                                                      parseInt(mcLayer_Tilt_Raise1.text), parseInt(mcLayer_Tilt_Raise2.text), parseInt(mcLayer_Tilt_Lower1.text),
                                                      parseInt(mcLayer_Tilt_Lower2.text), parseInt(mcLayer_Overlift1.text), parseInt(mcLayer_Overlift2.text),
                                                      parseInt(mcLayer_Breathe1.text), parseInt(mcLayer_Breathe2.text), parseInt(mcLayer_Settle1.text),
                                                      parseInt(mcLayer_Settle2.text), parseInt(mcLayer_Tilt_Percent1.text), parseInt(mcLayer_Tilt_Percent2.text),
                                                      parseInt(mcCut_Off_Layers.text), parseInt(mcFinal_OverLift.text), parseInt(mcBase_Layer_settle.text) );
                      }
                      motionConfigPopup.close();
                   }
               }
           }
        }
    }

}
