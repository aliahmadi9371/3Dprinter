import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3

RowLayout {
   width: parent.width
   spacing: 10
//Pane {
    id: materialConfig
    property var arrayWidth: [100,100,100,100,100,100,100,100,100]
    property int materialConfigId: 1
    property string name: "materialConfig name"
    property int layerThickness: 27
    property int burnInLayers: 27
    property double burnInCureTime: 10
    property double normalCureTime: 10
    property double burnIntensity: 42
    property double intensity: 54
    property int columnW: 55
    property int columnW_small: 45
    property int columnW_large: 60
//    signal configSelected(int configId, string configName, int configLayerThickness,
//                          int configBurnInLayers, double configBurnInCureTime, double configNormalCureTime,
//                          double configBurnIntensity, double configIntensity);
    signal configSelected(var configVars);
    signal materialDelete(int materialId)
    //    implicitHeight: 70
//    implicitWidth: parent.width
//    Material.elevation: 5
//    Layout.alignment: Qt.AlignHCenter
//    Layout.topMargin: 0
//    anchors.horizontalCenter: parent.horizontalCenter

// RowLayout {
//    width: parent.width
//    spacing: 10

    Item {
        width: materialConfig.columnW_large
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(materialConfig.name)
            font.pointSize: 12
            //font.bold: true
        }
    }

    ToolSeparator {}

    Item {
        width: materialConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(materialConfig.layerThickness+" ")
            font.pointSize: 12
            //font.bold: true
        }
    }

    ToolSeparator {}

    Item {
        width: materialConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(materialConfig.burnInLayers+" ")
            font.pointSize: 12
            //font.bold: true
        }
    }

    ToolSeparator {}

    Item {
        width: materialConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(materialConfig.burnInCureTime+" ")
            font.pointSize: 12
            //font.bold: true
        }
    }

    ToolSeparator {}

    Item {
        width: materialConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(materialConfig.normalCureTime+" ")
            font.pointSize: 12
            //font.bold: true
        }
    }

    ToolSeparator {}

    Item {
        width: materialConfig.columnW
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(materialConfig.burnIntensity+" ")
            font.pointSize: 12
            //font.bold: true
        }
    }

    ToolSeparator {}

    Item {
        width: materialConfig.columnW_small
        height: 60
        Text {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            text: qsTr(materialConfig.intensity+" ")
            font.pointSize: 12
            //font.bold: true
        }
    }

    ToolSeparator {}

    Item {
        width: materialConfig.columnW_small
        height: 60
        Button {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Delete")
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            highlighted: true
            Material.background: Material.Red
            onClicked: {
                materialConfig.materialDelete(parseInt(materialConfig.materialConfigId));
//                MaterialConfigModel.removeConfig(parseInt(materialConfig.materialConfigId));
            }
        }
    }

    ToolSeparator {}

    Item {
        width: materialConfig.columnW_small
        height: 60
        Button {
            x: (parent.width/2)-(width/2)
            y: (parent.height/2) - (height/2)
            Layout.alignment: Qt.AlignHCenter
    //        implicitWidth: materialConfig.column
            text: qsTr("Edit")
            highlighted: true
            Material.background: Material.Blue
            onClicked: {               
                materialConfig.configSelected([materialConfig.name, materialConfig.materialConfigId,
                materialConfig.layerThickness, materialConfig.burnInLayers, materialConfig.burnInCureTime,
                materialConfig.normalCureTime, materialConfig.burnIntensity, materialConfig.intensity]);
            }
        }
    }
}
