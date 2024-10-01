import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4
import Qt.labs.qmlmodels 1.0

Page {
    id: root
    width: parent.width
    property int textLeftMargin: 40
//    header: PageHeader {
//    }

    ColumnLayout {
        width: parent.width
        spacing: 20
        Layout.topMargin: 10
        Component.onCompleted: {
            console.log("Material page onCompleted");
            console.log(MaterialConfigModel.size());
            MaterialConfigModel.refreshData();
        }

//        NameForm {
//            label: "Material Name"
//            placeHolder: "Material Name"
//            btnLabel: "Add New"
//            onAccept: {
//                materialConfigPopup.name = inputText;
//                materialConfigPopup.newOrEdit = true;
//                materialConfigPopup.open();
//            }
//        }

//        RowLayout{
//            Layout.alignment: Qt.AlignHCenter
//            Text {
//                Layout.alignment: Qt.AlignHCenter
//                text: qsTr("ADD a New Material")
//                font.pixelSize: 22
//            }

            Button{
                text: "ADD a New Material"
                font.pixelSize: 22
                Layout.alignment: Qt.AlignHCenter
                highlighted: true
                Material.background: Material.Green
                onClicked: {
                    materialNamePopup.open();
                }
            }

//        }


        ToolSeparator {
            orientation: Qt.Horizontal
            implicitWidth: parent.width*0.9
            Layout.alignment: Qt.AlignHCenter
        }

        Flickable {
            width: window.width*7/8
            height: window.width*5/8
            contentWidth: 900; contentHeight: 600
            ScrollBar.horizontal: ScrollBar { id: hbar; active: vbar.active }
            ScrollBar.vertical: ScrollBar { id: vbar; active: hbar.active }
            clip: true
            ListView {
                id: materialList
                x: 10
                Layout.leftMargin: 10
                width: 800 //parent.width*0.95;
                height: 500
                spacing: 10
                Layout.alignment: Qt.AlignHCenter
                headerPositioning: ListView.OverlayHeader
                header: MaterialHeader {
                }

                model: MaterialConfigModel

                delegate: MaterialConfig {
                    materialConfigId: model.index+1
                    name: model.Name
                    layerThickness: model.LayerThickness.toFixed(2)
                    burnInLayers: model.BurnInLayers.toFixed(2)
                    burnInCureTime: model.BurnInCureTime.toFixed(2)
                    normalCureTime: model.NormalCureTime.toFixed(2)
                    burnIntensity: model.BurnIntensity.toFixed(2)
                    intensity: model.Intensity.toFixed(2)


                    onConfigSelected: {

                        materialConfigPopup.name = configVars[0];
                        materialConfigPopup.materialConfigId = configVars[1];
                        materialConfigPopup.layerThickness = configVars[2];
                        materialConfigPopup.burnInLayers = configVars[3];
                        materialConfigPopup.burnInCureTime = configVars[4];
                        materialConfigPopup.normalCureTime = configVars[5];
                        materialConfigPopup.burnIntensity = configVars[6];
                        materialConfigPopup.intensity = configVars[7];
                        materialConfigPopup.newOrEdit = false;

                        console.log("materialConfigPopup.burnIntensity : ",materialConfigPopup.burnIntensity)
                        materialConfigPopup.open();

//                        materialConfigPopup.name = configName;
//                        materialConfigPopup.materialConfigId = configId;
//                        materialConfigPopup.layerThickness = configLayerThickness;
//                        materialConfigPopup.burnInCureTime = configBurnInCureTime;
//                        materialConfigPopup.burnInLayers = configBurnInLayers;
//                        materialConfigPopup.burnIntensity = configBurnIntensity;
//                        materialConfigPopup.normalCureTime = configNormalCureTime;
//                        materialConfigPopup.intensity = configIntensity;
//                        materialConfigPopup.newOrEdit = false;
//                        materialConfigPopup.open();
                    }

                    onMaterialDelete: {
                        deleteDialog.materialId = materialId;
                        deleteDialog.open();
                    }
                }

            }

        }


    }

    Popup{
        id: materialNamePopup
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
                label: "New Material"
                placeHolder: "Material Name"
                btnLabel: "Next"
                onAccept: {
                    if (inputText!="")
                    {
                        materialConfigPopup.name = inputText;
                        materialConfigPopup.newOrEdit = true;
                        materialConfigPopup.open();
                        materialNamePopup.close();
                    }
                }
                onCancel: {
                    materialNamePopup.close();
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
        property int materialId: 1
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
                         MaterialConfigModel.removeConfig(deleteDialog.materialId);
                        deleteDialog.close();
                    }
                }
            }
        }
    }

    Popup{
        id: materialConfigPopup
//        anchors.centerIn: parent
        x: (parent.width - width)/2
        y: 50
        width: 600
        height: 400
        modal: false
        focus: true
        closePolicy: Popup.CloseOnEscape // | Popup.CloseOnPressOutside
        property int materialConfigId: 1
        property string name: ""
        property int layerThickness
        property int burnInLayers
        property double burnInCureTime
        property double normalCureTime
        property double burnIntensity
        property double intensity
        property bool newOrEdit: false

        contentItem: ColumnLayout {
            width: parent.width*0.9
            Layout.alignment: Qt.AlignHCenter
            spacing: 5

           RowLayout{
               width: parent.width
               height: 50
               Item {
                   width: 140
                   height: 50
                   Text {
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       text: qsTr("Layer Thickness ")
                       font.pointSize: 12
                       font.bold: true
                   }
               }
               MediumInput {
                   id: mcLayerThickness
                   text: qsTr(materialConfigPopup.layerThickness+"")
               }
               Item {
                   width: 140
                   height: 50
                   Text {
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 12
                       text: qsTr("Burn In Layers ")
                       font.bold: true
                   }
               }
               MediumInput {
                   id: mcBurnInLayers
                   text: qsTr(materialConfigPopup.burnInLayers+"")
               }

           }

           RowLayout{
               width: parent.width
               height: 50
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Burn In CureTime ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 12
                       font.bold: true
                   }
               }
               MediumInput {
                   id: mcBurnInCureTime
                   text: qsTr(materialConfigPopup.burnInCureTime+"")
               }
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Normal Cure Time ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 12
                       font.bold: true
                   }
               }
               MediumInput {
                   id: mcNormalCureTime
                   text: qsTr(materialConfigPopup.normalCureTime+"")
               }
           }

           RowLayout{
               width: parent.width
               height: 50
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Burn In Intensity ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 12
                       font.bold: true
                   }
               }
               MediumInput {
                   id: mcBurnIntensity
                   text: qsTr(materialConfigPopup.burnIntensity+"")
                   shift_y: true
               }
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Intensity ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 12
                       font.bold: true
                   }
               }
               MediumInput {
                   id: mcIntensity
                   text: qsTr(materialConfigPopup.intensity+"")
                   shift_y: true
               }
           }

           RowLayout{
               Layout.alignment: Qt.AlignHCenter
               height: 50
               Button{
                   text: qsTr("Cancel")
                   Layout.alignment: Qt.AlignHCenter
                   highlighted: true
                   Material.background: Material.Red
                   onClicked: {
                     materialConfigPopup.close();
                   }
               }
               Button{
                   text: materialConfigPopup.newOrEdit ? qsTr("Create") : qsTr("Edit")
                   Layout.alignment: Qt.AlignHCenter
                   highlighted: true
                   Material.background: Material.Green
                   onClicked: {
                      if(materialConfigPopup.newOrEdit) {
                          //mcName.text
                        MaterialConfigModel.makeNewConfig(materialConfigPopup.name, parseInt(mcLayerThickness.text),
                           parseInt(mcBurnInLayers.text), parseFloat(mcBurnInCureTime.text).toFixed(2),
                           parseFloat(mcNormalCureTime.text).toFixed(2), parseFloat(mcBurnIntensity.text).toFixed(2),
                                                          parseFloat(mcIntensity.text).toFixed(2));
                      } else {
                          //mcName.text
                          MaterialConfigModel.setConfig(parseInt(materialConfigPopup.materialConfigId), materialConfigPopup.name,
                             parseInt(mcLayerThickness.text), parseInt(mcBurnInLayers.text),
                             parseFloat(mcBurnInCureTime.text).toFixed(2),
                             parseFloat(mcNormalCureTime.text).toFixed(2),
                             parseFloat(mcBurnIntensity.text).toFixed(2),
                             parseFloat(mcIntensity.text).toFixed(2));
                      }
                      materialConfigPopup.close();
                   }
               }
           }
        }
    }

}

