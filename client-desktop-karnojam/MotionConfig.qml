import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3

RowLayout {
    id: motionConfig
    width: parent.width
    spacing: 10
    property string name: ""
    property int motionConfigId: 1
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
//    signal configSelected(int configId, string configName, int configLayer_Z_Raise1,
//                          int configLayer_Z_Raise2, int configLayer_Z_Lower1, int configLayer_Z_Lower2,
//                          int configLayer_Tilt_Raise1, int configLayer_Tilt_Raise2, int configLayer_Tilt_Lower1,
//                          int configLayer_Tilt_Lower2, int configLayer_Overlift1, int configLayer_Overlift2,
//                          int configLayer_Breathe1, int configLayer_Breathe2, int configLayer_Settle1,
//                          int configLayer_Settle2, int configLayer_Tilt_Percent1, int configLayer_Tilt_Percent2,
//                          int cut_Off_Layers, int final_OverLift, int base_Layer_settle);

    signal configSelected(var configVars);

    property int columnW: 55
    property int columnW_small: 45
    property int columnW_large: 60
    signal motionDelete(int motionId)

    Item {
        width: motionConfig.columnW_large
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(motionConfig.name)
            font.pointSize: 12
        }
    }
    ToolSeparator {}
    Item {
        width: motionConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(motionConfig.layer_Z_Raise1+" - "+motionConfig.layer_Z_Raise2)
            font.pointSize: 12
        }
    }
    ToolSeparator {}
    Item {
        width: motionConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(motionConfig.layer_Z_Lower1+" - "+motionConfig.layer_Z_Lower2)
            font.pointSize: 12
        }
    }
    ToolSeparator {}
    Item {
        width: motionConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(motionConfig.layer_Tilt_Raise1+" - "+motionConfig.layer_Tilt_Raise2)
            font.pointSize: 12
        }
    }
    ToolSeparator {}
    Item {
        width: motionConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(motionConfig.layer_Tilt_Lower1+" - "+motionConfig.layer_Tilt_Lower2)
            font.pointSize: 12
        }
    }
    ToolSeparator {}
    Item {
        width: motionConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(motionConfig.layer_Tilt_Percent1+" - "+motionConfig.layer_Tilt_Percent2)
            font.pointSize: 12
        }
    }
    ToolSeparator {}
    Item {
        width: motionConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(motionConfig.layer_Overlift1+" - "+motionConfig.layer_Overlift2)
            font.pointSize: 12
        }
    }
    ToolSeparator {}
    Item {
        width: motionConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(motionConfig.layer_Breathe1+" - "+motionConfig.layer_Breathe2)
            font.pointSize: 12
        }
    }
    ToolSeparator {}
    Item {
        width: motionConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(motionConfig.layer_Settle1+" - "+motionConfig.layer_Settle2)
            font.pointSize: 12
        }
    }
    ToolSeparator {}
    Item {
        width: motionConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(motionConfig.cut_Off_Layers+"")
            font.pointSize: 12
        }
    }
    ToolSeparator {}
    Item {
        width: motionConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(motionConfig.final_OverLift+"")
            font.pointSize: 12
        }
    }
    ToolSeparator {}
    Item {
        width: motionConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(motionConfig.base_Layer_settle+"")
            font.pointSize: 12
        }
    }
    ToolSeparator {}

    Item {
        width: motionConfig.columnW_small
        height: 60
        Button {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Delete")
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            highlighted: true
            Material.background: Material.Red
            onClicked: {
                motionConfig.motionDelete(parseInt(motionConfig.motionConfigId));
//                MotionConfigModel.removeConfig(parseInt(motionConfig.motionConfigId));
            }
        }
    }

    ToolSeparator {}

    Item {
        width: motionConfig.columnW_small
        height: 60
        Button {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Edit")
            highlighted: true
            Material.background: Material.Blue
//            onClicked: {
//                motionConfig.configSelected(motionConfig.motionConfigId, motionConfig.name,
//                motionConfig.layer_Z_Raise1, motionConfig.layer_Z_Raise2, motionConfig.layer_Z_Lower1,
//                motionConfig.layer_Z_Lower2, motionConfig.layer_Tilt_Raise1, motionConfig.layer_Tilt_Raise2,
//                motionConfig.layer_Tilt_Lower1, motionConfig.layer_Tilt_Lower2, motionConfig.layer_Overlift1,
//                motionConfig.layer_Overlift2, motionConfig.layer_Breathe1, motionConfig.layer_Breathe2,
//                motionConfig.layer_Settle1, motionConfig.layer_Settle2, motionConfig.layer_Tilt_Percent1,
//                motionConfig.layer_Tilt_Percent2, motionConfig.cut_Off_Layers, motionConfig.final_OverLift,
//                                            motionConfig.base_Layer_settle);

            onClicked: {
                motionConfig.configSelected([motionConfig.name,motionConfig.motionConfigId,
                motionConfig.layer_Z_Raise1, motionConfig.layer_Z_Raise2, motionConfig.layer_Z_Lower1,
                motionConfig.layer_Z_Lower2, motionConfig.layer_Tilt_Raise1, motionConfig.layer_Tilt_Raise2,
                motionConfig.layer_Tilt_Lower1, motionConfig.layer_Tilt_Lower2, motionConfig.layer_Overlift1,
                motionConfig.layer_Overlift2, motionConfig.layer_Breathe1, motionConfig.layer_Breathe2,
                motionConfig.layer_Settle1, motionConfig.layer_Settle2, motionConfig.layer_Tilt_Percent1,
                motionConfig.layer_Tilt_Percent2, motionConfig.cut_Off_Layers, motionConfig.final_OverLift,
                                            motionConfig.base_Layer_settle]);
            }
        }
    }
// RowLayout {
//    width: parent.width
//    spacing: 5

//    Item {
//        width: columnW*3
//        height: 60
//        Text {
//            text: qsTr(motionConfig.name)
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.layer_Z_Raise1+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.layer_Z_Raise2+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.layer_Z_Lower1+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.layer_Z_Lower2+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.layer_Overlift1+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.layer_Overlift2+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.layer_Breathe1+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.layer_Breathe2+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.layer_Settle1+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.layer_Settle2+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.layer_Tilt_Percent1+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.layer_Tilt_Percent2+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.cut_Off_Layers+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.final_OverLift+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Item {
//        width: columnW
//        height: 60
//        Text {
//            text: qsTr(motionConfig.base_Layer_settle+" ")
//            font.pointSize: 20
//            font.bold: true
//        }
//    }
//    Button{
//        text: "Delete"
//        onClicked: {
//          MotionConfigModel.removeConfig(parseInt(motionConfig.motionConfigId));
//        }
//    }
//    Button{
//        text: "Edit"
//        onClicked: {

//            motionConfig.configSelected(motionConfig.motionConfigId, motionConfig.name,
//            motionConfig.layer_Z_Raise1, motionConfig.layer_Z_Raise2, motionConfig.layer_Z_Lower1,
//            motionConfig.layer_Z_Lower2, motionConfig.layer_Tilt_Raise1, motionConfig.layer_Tilt_Raise2,
//            motionConfig.layer_Tilt_Lower1, motionConfig.layer_Tilt_Lower2, motionConfig.layer_Overlift1,
//            motionConfig.layer_Overlift2, motionConfig.layer_Breathe1, motionConfig.layer_Breathe2,
//            motionConfig.layer_Settle1, motionConfig.layer_Settle2, motionConfig.layer_Tilt_Percent1,
//            motionConfig.layer_Tilt_Percent2, motionConfig.cut_Off_Layers, motionConfig.final_OverLift,
//                                        motionConfig.base_Layer_settle);
//        }
//    }
// }
}
