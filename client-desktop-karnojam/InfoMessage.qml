import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Popup {
        id: notify
        x: 10
        y: 10
        width: 300
        height: 50
//        modal: true
        padding: 0
//        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        property string message: ""

        function trigerTime() {
           notifyTimer.running = true;
        }

       Rectangle {
           color: "blue"
           width: 300
           height: 50
//           radius: 5

           Text {
               x: (parent.width/2) - (width/2)
               y: (parent.height/2) - (height/2)
               Layout.alignment: Qt.AlignHCenter
//               anchors.centerIn: parent.Center
//               anchors.alignWhenCentered: false
               text: qsTr(notify.message)
               color: "white"
               font.pointSize: 16
//               verticalAlignment: Text.AlignVCenter
//               horizontalAlignment: Text.AlignHCenter
           }
       }

       Timer {
           id: notifyTimer
           interval: 2000//30 // 60 Hz
           running: false
           repeat: false
           onTriggered: {
               notify.close();
           }
       }

       Timer {
           id: notifyTimer2
           interval: 1000//30 // 60 Hz
           running: true
           repeat: true
           onTriggered: {
               var temp = UIMessages.getMessage();
               if( temp !== "") {
                   notify.message = temp;
                   notify.open();
                   notify.trigerTime();
               }
           }
       }
}
