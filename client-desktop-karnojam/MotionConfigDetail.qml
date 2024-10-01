import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3

RowLayout {
    id: root
    width: parent.width*0.95
    Layout.alignment: Qt.AlignHCenter
    property string name: ""
    property int motionConfigId: 1
//    id: motionConfig
//    property string name: "motionConfig name"
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
    property bool isEdiatabl: false

    ColumnLayout {
        width: parent.width/2
        // name
        RowLayout {
            width: parent.width
            spacing: 5
            Item {
                width: 100
                Text {
                    text: qsTr("Motion Name")
                    font.bold: true
                }
            }
            MediumInput {
                id: name_text
              visible: !root.isEdiatabl
            }
            Item {
                visible: root.isEdiatabl
                width: 100
                Text {
                    text: qsTr(root.name+"")
                }
            }
        }
        // Layer Z Raise
        RowLayout {
            width: parent.width
            spacing: 5
            Item {
                width: 100
                Text {
                    text: qsTr("Layer Z Raise")
                    font.bold: true
                }
            }
            SmallInput {
                id:layer_Z_Raise1_text
              visible: !root.isEdiatabl
            }
            SmallInput {
                id:layer_Z_Raise2_text
              visible: !root.isEdiatabl
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Z_Raise1+"")
                }
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Z_Raise2+"")
                }
            }
        }
        // Layer Z Lower
        RowLayout {
            width: parent.width
            spacing: 5
            Item {
                width: 100
                Text {
                    text: qsTr("Layer Z Lower")
                    font.bold: true
                }
            }
            SmallInput {
                id: layer_Z_Lower1_text
              visible: !root.isEdiatabl
            }
            SmallInput {
                id: layer_Z_Lower2_text
              visible: !root.isEdiatabl
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Z_Lower1+"")
                }
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Z_Lower2+"")
                }
            }
        }
        // Layer Tilt Raise
        RowLayout {
            width: parent.width
            spacing: 5
            Item {
                width: 100
                Text {
                    text: qsTr("Layer Tilt Raise")
                    font.bold: true
                }
            }
            SmallInput {
                id: layer_Tilt_Raise1_text
              visible: !root.isEdiatabl
            }
            SmallInput {
                id: layer_Tilt_Raise2_text
              visible: !root.isEdiatabl
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Tilt_Raise1+"")
                }
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Tilt_Raise2+"")
                }
            }
        }
        // Layer Tilt Lower
        RowLayout {
            width: parent.width
            spacing: 5
            Item {
                width: 100
                Text {
                    text: qsTr("Layer Tilt Lower")
                    font.bold: true
                }
            }
            SmallInput {
                id: layer_Tilt_Lower1_text
              visible: !root.isEdiatabl
            }
            SmallInput {
                id: layer_Tilt_Lower2_text
              visible: !root.isEdiatabl
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Tilt_Lower1+"")
                }
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Tilt_Lower2+"")
                }
            }
        }
        // Layer Tilt Percent
        RowLayout {
            width: parent.width
            spacing: 5
            Item {
                width: 100
                Text {
                    text: qsTr("Layer Tilt Percent")
                    font.bold: true
                }
            }
            SmallInput {
                id: layer_Tilt_Percent1_text
              visible: !root.isEdiatabl
            }
            SmallInput {
                id: layer_Tilt_Percent2_text
              visible: !root.isEdiatabl
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Tilt_Percent1+"")
                }
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Tilt_Percent2+"")
                }
            }
        }
    }

    ColumnLayout {
        width: parent.width/2
        // Layer Overlift
        RowLayout {
            width: parent.width
            spacing: 5
            Item {
                width: 100
                Text {
                    text: qsTr("Layer Overlift")
                    font.bold: true
                }
            }
            SmallInput {
                id: layer_Overlift1_text
              visible: !root.isEdiatabl
            }
            SmallInput {
                id: layer_Overlift2_text
              visible: !root.isEdiatabl
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Overlift1+"")
                }
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Overlift2+"")
                }
            }
        }
        // Layer Breathe
        RowLayout {
            width: parent.width
            spacing: 5
            Item {
                width: 100
                Text {
                    text: qsTr("Layer Breathe")
                    font.bold: true
                }
            }
            SmallInput {
                id: layer_Breathe1_text
              visible: !root.isEdiatabl
            }
            SmallInput {
                id: layer_Breathe2_text
              visible: !root.isEdiatabl
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Breathe1+"")
                }
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Breathe2+"")
                }
            }
        }
        // Layer Settle
        RowLayout {
            width: parent.width
            spacing: 5
            Item {
                width: 100
                Text {
                    text: qsTr("Layer Settle")
                    font.bold: true
                }
            }
            SmallInput {
                id: layer_Settle1_text
              visible: !root.isEdiatabl
            }
            SmallInput {
                id: layer_Settle2_text
              visible: !root.isEdiatabl
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Settle1+"")
                }
            }
            Item {
                visible: root.isEdiatabl
                width: 50
                Text {
                    text: qsTr(root.layer_Settle2+"")
                }
            }
        }
        // Cutoff Layers
        RowLayout {
            width: parent.width
            spacing: 5
            Item {
                width: 100
                Text {
                    text: qsTr("Cutoff Layers")
                    font.bold: true
                }
            }
            MediumInput {
                id: cutoff_layer_text
              visible: !root.isEdiatabl
            }
            Item {
                visible: root.isEdiatabl
                width: 100
                Text {
                    text: qsTr(root.cut_Off_Layers+"")
                }
            }
        }
        // Final Overlift
        RowLayout {
            width: parent.width
            spacing: 5
            Item {
                width: 100
                Text {
                    text: qsTr("Final Overlift")
                    font.bold: true
                }
            }
            MediumInput {
                id: final_OverLift_text
              visible: !root.isEdiatabl
            }
            Item {
                visible: root.isEdiatabl
                width: 100
                Text {
                    text: qsTr(root.final_OverLift+"")
                }
            }
        }
        // Base Layer Settle
        RowLayout {
            width: parent.width
            spacing: 5
            Item {
                width: 100
                Text {
                    text: qsTr("Base Layer Settle")
                    font.bold: true
                }
            }
            MediumInput {
                id: base_Layer_settle_text
              visible: !root.isEdiatabl
            }
            Item {
                visible: root.isEdiatabl
                width: 100
                Text {
                    text: qsTr(root.base_Layer_settle+"")
                }
            }
        }
    }
}
