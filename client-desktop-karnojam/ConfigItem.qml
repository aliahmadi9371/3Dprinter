import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3

RowLayout {
//   width: parent.width
   spacing: 10
    id: machineConfig
    property int columnW: 55
    property int columnW_small: 45
    property int columnW_large: 60
    property int configId: 2162
    property int modelCode: 2162
    property int gProjectWidth: 3840
    property int gProjectHeight: 2160
    property string machineNo: "PD-2162"
    property int version: 1
    property int subVersion: 0
    property bool needLicense: false
    property bool hasDoor: false
    property bool hasErm: false
    property bool bUpTDownConfig: false
    property real printerUnit: 1.25
    property int zUpperLimit: 90000
    property int projectorProtocol: 0
    property int noOfMaskPoints: 60
    property int maxIntensity: 1000
    property int minIntensity: 50
    property int maxIntensitySensor: 7450
    property int minIntensitySensor: 350

    //// for buttom Up
    property bool hasPlunger : false
    property int tDownZHomePos : 40400               //40200;  //37900
    property real vacuumTimer : 1.3               //40; //Sec
    property real sensorSetPointVacuum : 0.35      //0.6; //mm
    property real sensorSetPoint : 1.1             //3.1; //mm   //16.4
    property real sensorThreshold : 0.003          //mm
    property real xShift : 0                       // 2.025;
    property real yShift : 0



//    signal configSelected(int configId, int modelCode, int gProjectWidth, int gProjectHeight,
//                          string machineNo, int version, int subVersion,
//                           bool needLicense, bool hasDoor, bool hasErm, bool bUpTDownConfig, double printerUnit,
//                          int zUpperLimit, int projectorProtocol, int noOfMaskPoints, int maxIntensity,
//                          int minIntensity,bool hasPlunger,int tDownZHomePos,double vacuumTimer,double sensorSetPointVacuum,
//                          double sensorSetPoint,double sensorThreshold,double xShift,double yShift);
    signal configSelected(var configVars);
    signal configDelete(int configId)

//    Item {
//        width: machineConfig.columnW_large
//        height: 60
//        Text {
//            x: (parent.width/2)-(width/2)
//            y: (parent.height/2) - (height/2)
//            text: qsTr(machineConfig.modelCode+"")
//            font.pointSize: 12
//            //font.bold: true
//        }
//    }

//    ToolSeparator {}

    Item {
        width: machineConfig.columnW_large
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.modelCode+" ")
            font.pointSize: 12
            //font.bold: true
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.version+" ")
            font.pointSize: 12
            //font.bold: true
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.subVersion+" ")
            font.pointSize: 12
        }
    }



    ToolSeparator {}

    Item {
        width: machineConfig.columnW_large*2
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.machineNo+" ")
            font.pointSize: 12
            //font.bold: true
        }
    }



    ToolSeparator {}

    Item {
        width: machineConfig.columnW
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.gProjectWidth+" ")
            font.pointSize: 12
            //font.bold: true


        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.gProjectHeight+" ")
            font.pointSize: 12
            //font.bold: true
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.zUpperLimit+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}


    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.printerUnit.toFixed(4)+" ")



            font.pointSize: 12
        }
    }
    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.projectorProtocol+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.noOfMaskPoints+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.minIntensity+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.maxIntensity+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.minIntensitySensor+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.maxIntensitySensor+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.xShift.toFixed(4)+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.yShift.toFixed(4)+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.needLicense+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.hasDoor+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.hasErm+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_large
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.bUpTDownConfig+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_large
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.tDownZHomePos+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.vacuumTimer.toFixed(2)+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.hasPlunger+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.sensorSetPointVacuum.toFixed(2)+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.sensorSetPoint.toFixed(2)+" ")
            font.pointSize: 12
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_large
        height: 60
        Text {
            Layout.alignment: Qt.AlignHCenter
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(machineConfig.sensorThreshold.toFixed(4)+" ")
            font.pointSize: 12
        }
    }


    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Button {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Delete")
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            highlighted: true
            Material.background: Material.Red
            onClicked: {
                machineConfig.configDelete(parseInt(machineConfig.configId));
            }
        }
    }

    ToolSeparator {}

    Item {
        width: machineConfig.columnW_small
        height: 60
        Button {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Edit")
            highlighted: true
            Material.background: Material.Blue
            onClicked: {
//                machineConfig.configSelected(machineConfig.configId, machineConfig.modelCode,
//                machineConfig.gProjectWidth, machineConfig.gProjectHeight, machineConfig.machineNo,
//                machineConfig.version, machineConfig.subVersion, machineConfig.needLicense,
//                machineConfig.hasDoor, machineConfig.hasErm, machineConfig.bUpTDownConfig, machineConfig.printerUnit,
//                machineConfig.zUpperLimit, machineConfig.projectorProtocol, machineConfig.noOfMaskPoints,
//                machineConfig.maxIntensity, machineConfig.minIntensity,machineConfig.hasPlunger,machineConfig.tDownZHomePos,
//                machineConfig.vacuumTimer,machineConfig.sensorSetPointVacuum,machineConfig.sensorSetPoint,machineConfig.sensorThreshold,
//                                             machineConfig.xShift,machineConfig.yShift);

            machineConfig.configSelected([machineConfig.configId, machineConfig.modelCode,
            machineConfig.gProjectWidth, machineConfig.gProjectHeight, machineConfig.machineNo,
            machineConfig.version, machineConfig.subVersion, machineConfig.needLicense,
            machineConfig.hasDoor, machineConfig.hasErm, machineConfig.bUpTDownConfig, machineConfig.printerUnit,
            machineConfig.zUpperLimit, machineConfig.projectorProtocol, machineConfig.noOfMaskPoints,
            machineConfig.maxIntensity, machineConfig.minIntensity,machineConfig.maxIntensitySensor, machineConfig.minIntensitySensor,
            machineConfig.hasPlunger, machineConfig.tDownZHomePos, machineConfig.vacuumTimer,
            machineConfig.sensorSetPointVacuum, machineConfig.sensorSetPoint, machineConfig.sensorThreshold,
            machineConfig.xShift, machineConfig.yShift]);
            }
        }
    }

}
