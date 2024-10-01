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

   Item {
       width: root.columnW_large
       height: 70
       Text {
           text: qsTr("Name")
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
           text: qsTr("Layer Z\n  Raise")
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
           text: qsTr("Layer Z\n  Lower")
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
           text: qsTr("Layer Tilt\n   Raise")
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
           text: qsTr("Layer Tilt\n   Lower")
           font.pointSize: 12
           font.bold: true
           x: (parent.width/2) - (width/2)
           y: (parent.height/2) - (height/2)
       }
   }

   ToolSeparator {}

   Item {
       width: root.columnW
       height: 70
       Text {
           text: qsTr("Layer Tilt\n   Percent")
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
           text: qsTr("  Layer\nOverlift")
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
           text: qsTr("  Layer\nBreathe")
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
           text: qsTr("  Layer\nSettle")
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
           text: qsTr("Cutoff\nLayers")
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
           text: qsTr("  Final\nOverlift")
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
           text: qsTr("Base Layer\n  Settle")
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
