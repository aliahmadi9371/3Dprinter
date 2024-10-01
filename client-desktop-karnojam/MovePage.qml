import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4

Page {
    id: root
    width: parent.width
    property int textLeftMargin: 40
    property bool topDown: BackEnd.isTopDown()

//    header: PageHeader {
//    }

    ColumnLayout {
        width: parent.width
        height: window.height*7/8

        RowLayout {
            width: parent.width
            Item {
                width: parent.width/5
                Text {
                    x: root.textLeftMargin
                    y: (parent.height/2) - (height/2)
                    text: topDown ? qsTr("SRV") : qsTr("Door")
                    font.pointSize: 20
                    font.bold: true
                }
            }
            Image {
                sourceSize.width: (window.width/10)
                source: "images/up_arrow.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                         console.log("Up clicked")
                       if(BackEnd.manualMV(0, 1)) {

                       } else {

                       }
                    }
                }
            }
            Item {
                width: parent.width/5
                Text {
                    x: root.textLeftMargin
                    y: (parent.height/2) - (height/2)
                    text: topDown ? qsTr("Fill") : qsTr("Up")
                    font.pointSize: 14
                }
            }
            Image {
                sourceSize.width: (window.width/10)
                source: "images/bottom.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                         console.log("Down clicked")
                        if(BackEnd.manualMV(0, 0)) {

                        } else {

                        }
                    }
                }
            }
            Item {
                width: parent.width/5
                Text {
                    x: root.textLeftMargin
                    y: (parent.height/2) - (height/2)
                    text: topDown ? qsTr("Deplete") : qsTr("Down")
                    font.pointSize: 14
                }
            }

            Image {
                id: vaccumStop
                visible: false
                sourceSize.width: (window.width/12)
                source: "images/stop.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                         console.log("Down clicked")
                        if(BackEnd.manualMV(1, 50)) {

                        } else {

                        }
                    }
                }
            }
        }

        ToolSeparator {
            orientation: Qt.Horizontal
            implicitWidth: parent.width*0.9
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            width: parent.width
            Item {
                width: parent.width/5
                Text {
                    x: root.textLeftMargin
                    y: (parent.height/2) - (height/2)
                    text: topDown ? qsTr("Material") : qsTr("Build")
                    font.pointSize: 20
                    font.bold: true
                }
            }
            Image {
                sourceSize.width: (window.width/10)
                source: "images/up_arrow.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                         console.log("Up clicked")
                        if(BackEnd.manualMV(1, btnChain.step)) {

                        } else {

                        }
                    }
                }
            }
            Item {
                width: parent.width/5
                Text {
                    x: root.textLeftMargin
                    y: (parent.height/2) - (height/2)
                    text: topDown ? qsTr("Fill") : qsTr("Up")
                    font.pointSize: 14
                }
            }
            Image {
                sourceSize.width: (window.width/10)
                source: "images/bottom.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                         console.log("Down clicked")
                        if(BackEnd.manualMV(1, btnChain.step* (-1) )) {

                        } else {

                        }
                    }
                }
            }
            Item {
                width: parent.width/5
                Text {
                    x: root.textLeftMargin
                    y: (parent.height/2) - (height/2)
                    text: topDown ? qsTr("Drain") : qsTr("Down")
                    font.pointSize: 14
                }
            }

            Image {
                id: materiallevelStop
                visible: false
                sourceSize.width: (window.width/12)
                source: "images/stop.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                         console.log("Down clicked")
                        if(BackEnd.manualMV(1, 50)) {

                        } else {

                        }
                    }
                }
            }
        }

        ButtonChain {
            id: btnChain
            Layout.alignment: Qt.AlignHCenter
        }

        ToolSeparator {
            orientation: Qt.Horizontal
            implicitWidth: parent.width*0.9
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            width: parent.width
            Item {
                width: parent.width/5
                Text {
                    x: root.textLeftMargin
                    y: (parent.height/2) - (height/2)
                    text: topDown ? qsTr("Sweeper") : qsTr("Tilt")
                    font.pointSize: 20
                    font.bold: true
                }
            }
            Image {
                sourceSize.width: (window.width/10)
                source: "images/up_arrow.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                         console.log("Up clicked")
                        if(BackEnd.manualMV(2, 1)) {

                        } else {

                        }
                    }
                }
            }
            Item {
                width: parent.width/5
                Text {
                    x: root.textLeftMargin
                    y: (parent.height/2) - (height/2)
                    text: topDown ? qsTr("Front") : qsTr("Up")
                    font.pointSize: 14
                }
            }
            Image {
                sourceSize.width: (window.width/10)
                source: "images/bottom.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                         console.log("Down clicked")
                        if(BackEnd.manualMV(2, 0)) {

                        } else {

                        }
                    }
                }
            }
            Item {
                width: parent.width/5
                Text {
                    x: root.textLeftMargin
                    y: (parent.height/2) - (height/2)
                    text: topDown ? qsTr("Back") : qsTr("Down")
                    font.pointSize: 14
                }
            }
            Image {
                id: sweeperStop
                visible: false
                sourceSize.width: (window.width/12)
                source: "images/stop.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                         console.log("Down clicked")
                        if(BackEnd.manualMV(1, 50)) {

                        } else {

                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {

//        topDown = BackEnd.isTopDown();
        if (topDown){
            vaccumStop.visible = true
            materiallevelStop.visible = true
            sweeperStop.visible = true
        }
    }

}
