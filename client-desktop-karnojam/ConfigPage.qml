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


    ColumnLayout {
        width: parent.width
        spacing: 20
        Layout.topMargin: 10
        Component.onCompleted: {
            MachineConfigModel.refreshData();
        }

        ColumnLayout {
            width: parent.width
            Layout.alignment: Qt.AlignHCenter
            Button{
                text: "ADD a New Configuration"
                font.pixelSize: 22
                Layout.alignment: Qt.AlignHCenter
                highlighted: true
                Material.background: Material.Green
                onClicked: {
                    configNamePopup.open();
                }
            }

            RowLayout {
                width: parent.width
                Layout.alignment: Qt.AlignHCenter

                Text {
                    text: qsTr("Select Model")
                    font.pixelSize: 22
                }

                DropDown2 {
                    id: configSelection
                    model: MachineConfigModel
                    textRole: "ModelCode"
                    Layout.leftMargin: 15
                }
                Button {
                    text: qsTr("Set")
                    highlighted: true
                    Material.background: Material.Green
                    onClicked: {
                       MachineConfigModel.setMachineModel(configSelection.currentIndex);
                    }
                }
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
            contentWidth: 2800; contentHeight: 600
            ScrollBar.horizontal: ScrollBar { id: hbar; active: vbar.active }
            ScrollBar.vertical: ScrollBar { id: vbar; active: hbar.active }
            clip: true
            ListView {
                id: materialList
                x: 10
                Layout.leftMargin: 10
                width: 1700 //parent.width*0.95;
                height: 500
                spacing: 10
                Layout.alignment: Qt.AlignHCenter
                headerPositioning: ListView.OverlayHeader
                header: ConfigHeader {
                }

                model: MachineConfigModel

                delegate: ConfigItem {
                    configId: model.index+1
                    modelCode: model.ModelCode
                    gProjectWidth: model.gProjectWidth
                    gProjectHeight: model.gProjectHeight
                    machineNo: model.MachineNo
                    version: model.Version
                    subVersion: model.SubVersion
                    needLicense: model.NeedLicense
                    hasDoor: model.HasDoor
                    hasErm: model.HasErm
                    bUpTDownConfig: model.BUpTDownConfig
                    printerUnit: model.PrinterUnit
                    zUpperLimit: model.ZUpperLimit
                    projectorProtocol: model.ProjectorProtocol
                    noOfMaskPoints: model.NoOfMaskPoints
                    maxIntensity: model.MaxIntensity
                    minIntensity: model.MinIntensity

                    maxIntensitySensor: model.MaxIntensitySensor
                    minIntensitySensor: model.MinIntensitySensor

                    hasPlunger: model.HasPlunger
                    tDownZHomePos: model.TDownZHomePos
                    vacuumTimer: model.vacuumTimer
                    sensorSetPointVacuum: model.SensorSetPointVacuum
                    sensorSetPoint: model.SensorSetPoint
                    sensorThreshold: model.SensorThreshold
                    xShift: model.XShift
                    yShift: model.YShift






                    onConfigSelected: {


//                        configPopup.configId = configId;
//                        configPopup.modelCode = modelCode;

//                        configPopup.gProjectWidth = gProjectWidth;
//                        configPopup.gProjectHeight = gProjectHeight;
//                        configPopup.machineNo = gProjectHeight;
//                        configPopup.version = gProjectHeight;
//                        configPopup.subVersion = subVersion;
//                        configPopup.needLicense = needLicense;
//                        configPopup.hasDoor = hasDoor;
//                        configPopup.hasErm = hasErm;
//                        configPopup.bUpTDownConfig = bUpTDownConfig;
//                        configPopup.printerUnit = printerUnit;
//                        configPopup.zUpperLimit = zUpperLimit;
//                        configPopup.projectorProtocol = projectorProtocol;
//                        configPopup.noOfMaskPoints = noOfMaskPoints;
//                        configPopup.maxIntensity = maxIntensity;
//                        configPopup.minIntensity = minIntensity;

//                        configPopup.hasPlunger = hasPlunger;
//                        configPopup.tDownZHomePos = tDownZHomePos;
//                        configPopup.vacuumTimer = vacuumTimer;
//                        configPopup.sensorSetPointVacuum = sensorSetPointVacuum;
//                        configPopup.sensorSetPoint = sensorSetPoint;
//                        configPopup.sensorThreshold = sensorThreshold;
//                        configPopup.xShift = xShift;
//                        configPopup.yShift = yShift;




                        configPopup.configId = configVars[0];
                        configPopup.modelCode = configVars[1];

                        configPopup.gProjectWidth = configVars[2];
                        configPopup.gProjectHeight = configVars[3];
                        configPopup.machineNo = configVars[4];
                        configPopup.version = configVars[5];
                        configPopup.subVersion = configVars[6];
                        configPopup.needLicense = configVars[7];
                        configPopup.hasDoor = configVars[8];
                        configPopup.hasErm = configVars[9];
                        configPopup.bUpTDownConfig = configVars[10];
                        configPopup.printerUnit = configVars[11];
                        configPopup.zUpperLimit = configVars[12];
                        configPopup.projectorProtocol = configVars[13];
                        configPopup.noOfMaskPoints = configVars[14];
                        configPopup.maxIntensity = configVars[15];
                        configPopup.minIntensity = configVars[16];
                        configPopup.maxIntensitySensor = configVars[17];
                        configPopup.minIntensitySensor = configVars[18];

                        configPopup.hasPlunger = configVars[19];
                        configPopup.tDownZHomePos = configVars[20];
                        configPopup.vacuumTimer = configVars[21];
                        configPopup.sensorSetPointVacuum = configVars[22];
                        configPopup.sensorSetPoint = configVars[23];
                        configPopup.sensorThreshold = configVars[24];
                        configPopup.xShift = configVars[25];
                        configPopup.yShift = configVars[26];

                        configPopup.newOrEdit = false;
                        configPopup.open();
                    }

                    onConfigDelete: {
                        deleteDialog.configId = configId;
                        deleteDialog.open();
                    }
                }

            }

        }


    }

    Popup{
        id: configNamePopup
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
                label: "New Machine"
                placeHolder: "Machine Name"
                btnLabel: "Next"
                onAccept: {
                    if (!isNaN(inputText))
                    {
                        console.log(parseInt(inputText));
                        configPopup.modelCode = parseInt(inputText);
                        configPopup.newOrEdit = true;
                        configPopup.open();
                        configNamePopup.close();
                    }
                }
                onCancel: {
                    configNamePopup.close();
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
        property int configId: 1
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
                         MachineConfigModel.removeConfig(deleteDialog.configId);
                        deleteDialog.close();
                    }
                }
            }
        }
    }

    Popup{
        id: configPopup
//        anchors.centerIn: parent
        x: (parent.width - width)/2
        y: 50
        width: 700
        height: 600
        modal: false
        focus: true
        closePolicy: Popup.CloseOnEscape // | Popup.CloseOnPressOutside
        property bool newOrEdit: true
        property int configId: 1
        property int modelCode: 2162
        property int gProjectWidth: 3840
        property int gProjectHeight: 2160
        property string machineNo: "PD2162"
        property int version: 1
        property int subVersion: 0
        property bool needLicense: false
        property bool hasDoor: false
        property bool hasErm: false
        property bool bUpTDownConfig: true
        property real printerUnit: 1.25
        property int zUpperLimit: 100000
        property int projectorProtocol: 0
        property int noOfMaskPoints: 60
        property int maxIntensity: 1000
        property int minIntensity: 50

        property int maxIntensitySensor: 7450
        property int minIntensitySensor: 350

        property bool hasPlunger : false;
        property int tDownZHomePos : 40400;//40200;  //37900
        property real vacuumTimer : 1.3;//40; //Sec
        property real sensorSetPointVacuum : 0.35;//0.6; //mm
        property real sensorSetPoint : 1.1; //3.1; //mm   //16.4
        property real sensorThreshold : 0.003; //mm
        property real xShift : 0;
        property real yShift : 0;

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
                        x: (parent.width-width)/3
                        y: (parent.height-height)/2
                        text: qsTr("Model Code")
                        font.pointSize: 10
                        font.bold: true
                    }
                }
                SmallInput {
                    id: mcModelCode
                    text: qsTr(configPopup.modelCode+"")
                }
                Item {
                    width: 140
                    height: 50
                    Text {
                        text: qsTr("Version ")
                        x: (parent.width-width)/3
                        y: (parent.height-height)/2
                        font.pointSize: 10
                        font.bold: true
                    }
                }
                SmallInput {
                    id: mcVersion
                    text: qsTr(configPopup.version+"")
                    shift_y: true
                }
                Item {
                    width: 140
                    height: 50
                    Text {
                        text: qsTr("Sub Version ")
                        x: (parent.width-width)/3
                        y: (parent.height-height)/2
                        font.pointSize: 10
                        font.bold: true
                    }
                }
                SmallInput {
                    id: mcSubVersion
                    text: qsTr(configPopup.subVersion+"")
                    shift_y: true
                }


            }

           RowLayout{
               width: parent.width
               height: 50

               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Machine No ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               LargInput {
                   id: mcMachineNo
                   text: qsTr(configPopup.machineNo+"")
               }

           }

           RowLayout{
               Item {
                   width: 140
                   height: 50
                   Text {
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       text: qsTr("Projector Width ")
                       font.bold: true
                   }
               }
               MediumInput {
                   id: mcGProjectWidth
                   text: qsTr(configPopup.gProjectWidth+"")
               }
               width: parent.width
               height: 50
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Projector Height ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               MediumInput {
                   id: mcGProjectHeight
                   text: qsTr(configPopup.gProjectHeight+"")
               }

           }




           RowLayout{
               width: parent.width
               height: 50
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Z Upper Limit ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               MediumInput {
                   id: mcZUpperLimit
                   text: qsTr(configPopup.zUpperLimit+"")
                   shift_y: true
               }

               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Printer Unit ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               MediumInput {
                   id: mcPrinterUnit
                   text: qsTr(configPopup.printerUnit.toFixed(4)+"")
                   shift_y: true
               }
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Projector Protocol ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 12
                       font.bold: true
                   }
               }
               MediumInput {
                   id: mcProjectorProtocol
                   text: qsTr(configPopup.projectorProtocol+"")
                   shift_y: true
               }
           }

           RowLayout{
               width: parent.width
               height: 50
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("No Of Mask Points ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               SmallInput {
                   id: mcNoOfMaskPoints
                   text: qsTr(configPopup.noOfMaskPoints+"")
                   shift_y: true
               }
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Max Intensity ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               SmallInput {
                   id: mcMaxIntensity
                   text: qsTr(configPopup.maxIntensity+"")
                   shift_y: true
               }

               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Min Intensity")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               SmallInput {
                   id: mcMinIntensity
                   text: qsTr(configPopup.minIntensity+"")
                   shift_y: true
               }

           }


           RowLayout{

               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Max Intensity Sensor")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               SmallInput {
                   id: mcMaxIntensitySensor
                   text: qsTr(configPopup.maxIntensitySensor+"")
                   shift_y: true
               }

               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Min Intensity Sensor")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               SmallInput {
                   id: mcMinIntensitySensor
                   text: qsTr(configPopup.minIntensitySensor+"")
                   shift_y: true
               }
           }




           RowLayout{
               width: parent.width
               height: 50
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("xShift")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               SmallInput {
                   id: mcXShift
                   text: qsTr(configPopup.xShift.toFixed(4)+"")
                   shift_y: true
               }
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("yShift ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               SmallInput {
                   id: mcyShift
                   text: qsTr(configPopup.yShift.toFixed(4)+"")
                   shift_y: true
               }

           }


           RowLayout{
               width: parent.width
               height: 50
               Layout.alignment: Qt.AlignHCenter
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Need License ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               CheckBox {
                   id: mcNeedLicense
                   checked: configPopup.needLicense
//                   text: qsTr("I have centered the device.")
               }

               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Has Door ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               CheckBox {
                   id: mcHasDoor
                   checked: configPopup.hasDoor
               }

               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Has ERM ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               CheckBox {
                   id: mcHasErm
                   checked: configPopup.hasErm
               }
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("BUpTDownConfig ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               CheckBox {
                   id: mcBUpTDownConfig
                   checked: configPopup.bUpTDownConfig
               }
           }

           RowLayout{
               width: parent.width
               height: 50
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("TDown Z Home ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               SmallInput {
                   id: mcTDownZHomePos
                   text: qsTr(configPopup.tDownZHomePos+"")
                   shift_y: true
               }
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("vacuum Timer ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               SmallInput {
                   id: mcVacuumTimer
                   text: qsTr(configPopup.vacuumTimer.toFixed(2)+"")
                   shift_y: true
               }

               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("has Plunger ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               CheckBox {
                   id: mcHasPlunger
                   checked: configPopup.hasPlunger
//                   text: qsTr("I have centered the device.")
               }


           }

           RowLayout{
               width: parent.width
               height: 50
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("Vacuum SetPoint")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               SmallInput {
                   id: mcSensorSetPointVacuum
                   text: qsTr(configPopup.sensorSetPointVacuum.toFixed(2)+"")
                   shift_y: true
               }
               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("sensor SetPoint ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               SmallInput {
                   id: mcSensorSetPoint
                   text: qsTr(configPopup.sensorSetPoint.toFixed(2)+"")
                   shift_y: true
               }

               Item {
                   width: 140
                   height: 50
                   Text {
                       text: qsTr("sensor Threshold ")
                       x: (parent.width-width)/2
                       y: (parent.height-height)/2
                       font.pointSize: 10
                       font.bold: true
                   }
               }
               SmallInput {
                   id: mcSensorThreshold
                   text: qsTr(configPopup.sensorThreshold.toFixed(4)+"")
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
                     configPopup.close();
                   }
               }
               Button{
                   text: configPopup.newOrEdit ? qsTr("Create") : qsTr("Edit")
                   Layout.alignment: Qt.AlignHCenter
                   highlighted: true
                   Material.background: Material.Green
                   onClicked: {

                      if(configPopup.newOrEdit) {
                           MachineConfigModel.makeNewConfig(configPopup.modelCode, parseInt(mcGProjectWidth.text),
                           parseInt(mcGProjectHeight.text), mcMachineNo.text,
                           parseInt(mcVersion.text), parseInt(mcSubVersion.text),
                           mcNeedLicense.checked, mcHasDoor.checked, mcHasErm.checked, mcBUpTDownConfig.checked,
                           parseFloat(mcPrinterUnit.text).toFixed(4), parseInt(mcZUpperLimit.text),
                           parseInt(mcProjectorProtocol.text),
                           parseInt(mcNoOfMaskPoints.text), parseInt(mcMaxIntensity.text),parseInt(mcMinIntensity.text),
                           parseInt(mcMaxIntensitySensor.text),parseInt(mcMinIntensitySensor.text),
                           mcHasPlunger.checked, parseInt(mcTDownZHomePos.text), parseFloat(mcVacuumTimer.text).toFixed(4),
                           parseFloat(mcSensorSetPointVacuum.text).toFixed(4),parseFloat(mcSensorSetPoint.text).toFixed(4),parseFloat(mcSensorThreshold.text).toFixed(4),
                           parseFloat(mcXShift.text).toFixed(4),parseFloat(mcyShift.text).toFixed(4));
                      } else {
                          MachineConfigModel.setConfig(configPopup.configId, configPopup.modelCode,
                             parseInt(mcGProjectWidth.text), parseInt(mcGProjectHeight.text),
                             mcMachineNo.text, parseInt(mcVersion.text), parseInt(mcSubVersion.text),
                             mcNeedLicense.checked, mcHasDoor.checked, mcHasErm.checked, mcBUpTDownConfig.checked,
                             parseFloat(mcPrinterUnit.text).toFixed(4), parseInt(mcZUpperLimit.text),
                             parseInt(mcProjectorProtocol.text),
                             parseInt(mcNoOfMaskPoints.text), parseInt(mcMaxIntensity.text),parseInt(mcMinIntensity.text),
                             parseInt(mcMaxIntensitySensor.text),parseInt(mcMinIntensitySensor.text),
                             mcHasPlunger.checked, parseInt(mcTDownZHomePos.text), parseFloat(mcVacuumTimer.text).toFixed(4),
                             parseFloat(mcSensorSetPointVacuum.text).toFixed(4),parseFloat(mcSensorSetPoint.text).toFixed(4),parseFloat(mcSensorThreshold.text).toFixed(4),
                             parseFloat(mcXShift.text).toFixed(4),parseFloat(mcyShift.text).toFixed(4));
                      }
                      configPopup.close();
                   }
               }
           }


        }
    }

}

