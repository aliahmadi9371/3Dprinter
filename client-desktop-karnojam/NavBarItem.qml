import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Rectangle {

    property int pageIndex: 0
    property bool showConfig: BackEnd.showConfig()
    property int imageHeight: showConfig ? (window.height/7)*0.5 : (window.height/6)*0.5
    property string imageSource: "images/logo1.png"
    property string activeImageSource: "images/logo1.png"
    property string name: ""

   id: root
   width: parent.width
   height: showConfig ? window.height/7 : window.height/6

   color: "#314455"


   Column {
       width: parent.width
       Image {
           Layout.alignment: Qt.AlignHCenter
           sourceSize.height:  root.imageHeight
           source: (route.currentIndex === root.pageIndex) ? root.activeImageSource : root.imageSource
           x: (root.width/2) - (width/2)
//           Component.onCompleted: {
//               console.log("nav item image :");
//               console.log(width)
//               console.log(height)
//           }
       }
       Text {
           x: (root.width/2) - (width/2)
           text: qsTr(name)
           font.pointSize: 12
           color: (route.currentIndex === root.pageIndex) ? "#B23850" : "#E7E3D4"
       }
   }


}
