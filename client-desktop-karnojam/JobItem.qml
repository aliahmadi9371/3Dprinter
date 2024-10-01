import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4

RowLayout {
    id: root
    width: parent.width
    property string name: ""
    property int jobId: 1
    signal jobDelete(int jobId)

    Item {
        id: textContainer
        width: 200
        height: 50

//        ToolTip.visible: hovered
//        ToolTip.text: qsTr(root.name)
        Text {
            id: jobName
            y: (parent.height/2) - (height/2)
            text: qsTr(root.jobId+"."+root.name)
            font.pointSize: 12  
            Component.onCompleted: {
                if(root.name.length>=20)
                {
                    jobName.text = qsTr(root.jobId+"."+root.name.substring(0, 16)+"...")
                }
            }

            MouseArea {
               id: ma
               anchors.fill: parent
               hoverEnabled: true
            }
        }
        ToolTip {
//            parent: textContainer
            visible: ma.containsMouse
            text: qsTr(root.name)
        }
    }
    Image {
        sourceSize.width: (window.width/8)/4
        source: "images/garbage.png"
        scale:  mouseArea.containsMouse ? 0.8 : 1.0
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                root.jobDelete(parseInt(jobId));
//                JobModel.removeJob(parseInt(jobId))
            }
        }
    }

}
