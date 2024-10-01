import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: root
    height: window.height/8
    width: window.width*7/8
    color: "black"
    property string machineName: "Beta 1280"
    property string ipAddr: "192.168.4.1"
    property bool connectionState: true
    RowLayout {
        height: window.height/8
        width: window.width*7/8
//        implicitWidth: window.height/8
//        implicitHeight: window.width*7/8
        Item {
            width: ((window.width*7/8) - logo.width) / 2
            height: window.height/8
            Text {
                x: (parent.width/2) - (width/2)
                y: (parent.height/2) - (height/2)
                text: qsTr("Machine Name:"+root.machineName)
                color: "#F6F0F0"
                font.pointSize: 12
            }
        }
        Image {
            id: logo
            sourceSize.height:  (window.height/6)*0.8
            source: "images/logo1.png"
        }
        Item {
            width: ((window.width*7/8) - logo.width) / 4
            height: window.height/8
            Text {
                x: (parent.width/2) - (width/2)
                y: (parent.height/2) - (height/2)
                text: qsTr("Machine Name:"+root.ipAddr)
                font.pointSize: 12
                color: "#F6F0F0"
            }
        }
        Item {
            width: ((window.width*7/8) - logo.width) / 4
            height: window.height/8
            Text {
                x: (parent.width/2) - (width/2)
                y: (parent.height/2) - (height/2)
                text: root.connectionState ? qsTr("Status: Connected") : qsTr("Status: Disconnected")
                font.pointSize: 12
                color: "#F6F0F0"
            }
        }
    }
}
