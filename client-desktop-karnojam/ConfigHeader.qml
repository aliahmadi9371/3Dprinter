import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

RowLayout {
//   width: parent.width
    id: root
   spacing: 10
   property int columnW: 55
   property int columnW_small: 45
   property int columnW_large: 60

//   property int modelCode: 123456
//   property int gProjectWidth: 27
//   property int gProjectHeight: 27
//   property string machineNo: ""
//   property int version: 10
//   property int subVersion: 42
//   property bool needLicense: false
//   property bool hasDoor: false
//   property bool hasErm: false
//   property bool bUpTDownConfig: false
//   property double printerUnit: 0
//   property int zUpperLimit: 0
//   property int projectorProtocol: 0
//   property int noOfMaskPoints: 0
//   property int maxIntensity: 0
//   property int minIntensity: 0

   Item {
       width: columnW_large
       height: 70
       Text {
           text: qsTr("Model\nCode")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: columnW
       height: 70
       Text {
           text: qsTr("Version")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {}

   Item {
       width: columnW
       height: 70
       Text {
           text: qsTr("  Sub\nVersion")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: columnW_large*2
       height: 70
       Text {
           text: qsTr("Machine\n   No")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }



   ToolSeparator {
   }

   Item {
       width: columnW
       height: 70
       Text {
           text: qsTr("G Project\n  Width")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: columnW
       height: 70
       Text {
           text: qsTr("G Project\n  Height")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("Z Upper\n Limit")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("Printer\n  Unit")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("Projector\n Protocol")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }



   ToolSeparator {
   }

   Item {
       width: root.columnW
       height: 70
       Text {
           text: qsTr("No Of Mask\n   Points")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("   Min\nIntensity")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("   Max\nIntensity")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("   Min\nIntensity Sensor")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("   Max\nIntensity Sensor")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr(" XShift")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr(" YShift")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }



   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("  Need\nLicense")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr(" Has\nDoor")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr(" Has\nERM")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }


   ToolSeparator {
   }

   Item {
       width: root.columnW_large
       height: 70
       Text {
           text: qsTr("   B Up T\nDownConfig")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }


   ToolSeparator {
   }

   Item {
       width: root.columnW_large
       height: 70
       Text {
           text: qsTr("   TDown\n   ZHome   ")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("   Vacuum\n   Timer  ")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }


   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("    Has\n Plunger ")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }


   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("   Vacuum \n  Setpoint  ")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("   Sensor \n  Setpoint  ")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_large
       height: 70
       Text {
           text: qsTr("  Sensor\nThreshold")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("Delete")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {
   }

   Item {
       width: root.columnW_small
       height: 70
       Text {
           text: qsTr("Edit")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

}
