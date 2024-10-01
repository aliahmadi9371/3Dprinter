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
       width: columnW_large
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
       width: columnW
       height: 70
       Text {
           text: qsTr("    Layer\nThickness")
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
           text: qsTr("Burn In\n Layers")
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
           text: qsTr("  Burn In\nCure Time")
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
           text: qsTr(" Normal\nCureTime")
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
           text: qsTr("   Burn\nIntensity")
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
           text: qsTr("Intensity")
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
