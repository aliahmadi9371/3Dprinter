import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4


Page {
    id: root
    width: parent.width
    property int currentLayer: 0
    property int numOfLayers: 0
    property string timeToFinish: "00:00:00"
    property int textLeftMargin: 40
    property int printingState: 0

    ColumnLayout {
        width: parent.width
        spacing: 10
        property bool printing: false

        RowLayout {
            width: parent.width
            spacing: 15
            ColumnLayout {
                width: parent.width*0.8
                Layout.topMargin: 15
                RowLayout {
                    width: parent.width*0.9
                    spacing: 10
//                    Layout.alignment: Qt.AlignHCenter
                    Layout.alignment: Qt.AlignRight
                    Item {
                        width: 140
                        Text {
                            x: root.textLeftMargin
                            text: qsTr("File name")
                            font.pointSize: 14
                            font.bold: true
                            y: (parent.height/2) - (height/2)
                        }
                    }
                    DropDown {
                        id: fileDropDown
                        width: 430
                        model: JobModel
                        textRole: "Name"
                    }
                }

                RowLayout {
                    width: parent.width*0.9
//                    Layout.alignment: Qt.AlignHCenter
                    Layout.alignment: Qt.AlignRight
                    spacing: 10
                    Item {
                        width: 130
                        Text {
                             x: root.textLeftMargin
                            text: qsTr("Material")
                            font.pointSize: 14
                            font.bold: true
                            y: (parent.height/2) - (height/2)
                        }
                    }
                    DropDown {
                        id: materialDropDown
                        width: 160
                        model: MaterialConfigModel
                        textRole: "Name"
                    }
                    Item {
                        width: 90
                        Text {
                            text: qsTr("Motion")
                            font.pointSize: 14
                            font.bold: true
                            y: (parent.height/2) - (height/2)
                        }
                    }
                    DropDown {
                        id: motionDropDown
                        width: 160
                        model: MotionConfigModel
                        textRole: "Name"
                    }
                }
            }
            ColumnLayout {
                width: parent.width*0.2
                spacing: 0
                Image {
                    Layout.alignment: Qt.AlignHCenter
                    sourceSize.width: (window.width/8)
                    source: "images/play-box-outline.png"
                    visible: (root.printingState == 0 || root.printingState == 2)
                    cache: false
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ackDialog.btnState = 0;
                            ackDialog.open();
                        }
                    }
                }
                Image {
                    Layout.alignment: Qt.AlignHCenter
                    sourceSize.width: (window.width/8)
                    source: "images/pause-circle-outline.png"
                    visible: (root.printingState == 1 )
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("pause print")
                            ackDialog.btnState = 1;
                            ackDialog.open();
                        }
                    }
                }
                Image {
                    Layout.alignment: Qt.AlignHCenter
                    sourceSize.width: (window.width/8)
                    source: "images/stop-circle-outline.png"
                    visible: (root.printingState == 1 || root.printingState == 2)
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("stop print")
                            ackDialog.btnState = 2;
                            ackDialog.open();
                        }
                    }
                }
            }

            ColumnLayout {
                width: parent.width*0.2
                spacing: 0
                Image {
                    Layout.alignment: Qt.AlignHCenter
                    sourceSize.width: (window.width/16)
                    source: "images/refresh.png"
                    visible: (root.printingState == 0 || root.printingState == 2)
                    cache: false
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            route.checkServerState();
                        }
                    }
                }
            }


//            ColumnLayout {
//                width: parent.width*0.5
//                spacing: 0
//                Image {
//                    Layout.alignment: Qt.AlignHCenter
//                    sourceSize.width: (window.width/16)
//                    source: "images/exit.png"
//                    visible: (root.printingState == 0 || root.printingState == 2)
//                    cache: false
//                    MouseArea {
//                        anchors.fill: parent
//                        onClicked: {
//                            ackExit.open();
//                        }
//                    }
//                }
//            }
        }

        ToolSeparator {
            orientation: Qt.Horizontal
            implicitWidth: parent.width*0.9
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            width: parent.width*0.9
            Layout.alignment: Qt.AlignHCenter
            spacing: 5

            ColumnLayout {
                width: parent.width*0.6
                Text {
                    text: qsTr("Preview")
                    font.pointSize: 12
                }
                Image {
                    id: previewImg
                    sourceSize.width: window.width*4.5/8
                    source: "images/preview.png"
                    cache: false
                }
            }
            ColumnLayout {
                width: parent.width*0.35
                spacing: 5
                Text {
                    text: qsTr("Number of Layers: "+root.currentLayer+" of "+root.numOfLayers)
                    font.pointSize: 12
                }
                Text {
                    text: qsTr("Time to Finish: "+root.timeToFinish)
                    font.pointSize: 12
                }
                CircleProgress {
                    id: printProgress
                   Layout.alignment: Qt.AlignHCenter
                   currentValue: 0
                }
            }
        }

        Popup{
            id: ackDialog
    //        anchors.centerIn: parent
            x: (parent.width - width)/2
            y: 50
            width: 400
            height: 200
            modal: true
            focus: true
            property int btnState: 0
            contentItem: ColumnLayout {
                width: parent.width*0.9
                Layout.alignment: Qt.AlignHCenter
                spacing: 5
                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Are you sure?")
                    font.pixelSize: 22
                }
                RowLayout {
                    width: parent.width
                    Layout.alignment: Qt.AlignHCenter
                    spacing: 30
                    Button {
                        text: qsTr("No")
                        highlighted: true
                        Material.background: Material.Red
                        onClicked: {
                           ackDialog.close();
                        }
                    }
                    Button {
                        text: qsTr("Yes")
                        highlighted: true
                        Material.background: Material.Green
                        onClicked: {
                            if(ackDialog.btnState === 0) {
                                printProgress.currentValue = 0;
                                console.log("start print")
                                root.printingState = 1;
                                BackEnd.startPrint(materialDropDown.currentIndex, motionDropDown.currentIndex , fileDropDown.currentIndex);
                            } else if(ackDialog.btnState === 1) {
                                root.printingState = 2;
                                BackEnd.pausePrint();
                            } else if(ackDialog.btnState === 2) {
                                root.printingState = 0;
                                printProgress.currentValue = 0;
                                previewImg.source =  "images/preview.png";
                                BackEnd.stopPrint();
                           }
                            ackDialog.close();
                        }
                    }
                }
            }
        }

        Popup{
            id: finishedMsg
    //        anchors.centerIn: parent
            x: (parent.width - width)/2
            y: 50
            width: 400
            height: 200
            modal: true
            focus: true
            contentItem: ColumnLayout {
                width: parent.width*0.9
                Layout.alignment: Qt.AlignHCenter
                spacing: 5
                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Print Finished")
                    font.pixelSize: 22
                }
                RowLayout {
                    width: parent.width
                    Layout.alignment: Qt.AlignHCenter
                    spacing: 30
                    Button {
                        text: qsTr("Ok")
                        highlighted: true
                        Material.background: Material.Red
                        onClicked: {
                           finishedMsg.close();
                        }
                    }
                }
            }
        }


        Popup{
            id: ackExit
    //        anchors.centerIn: parent
            x: (parent.width - width)/2
            y: 50
            width: 400
            height: 200
            modal: true
            focus: true
            property int btnState: 0
            contentItem: ColumnLayout {
                width: parent.width*0.9
                Layout.alignment: Qt.AlignHCenter
                spacing: 5
                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Please insert the passwor:")
                    font.pixelSize: 22
                }
                RowLayout {
                    width: parent.width
                    Layout.alignment: Qt.AlignHCenter
                    spacing: 30
                    LargInput{
                        id:exitPass
                        echoMode: TextInput.Password
                    }

                    Button {
                        text: qsTr("Ok")
                        highlighted: true
                        Material.background: Material.Green
                        onClicked: {
                            if(exitPass.text === "User@LcdRaspberry") {
                                Qt.callLater(Qt.quit);
                                ackDialog.close();
                            }

                        }
                    }
                }
            }
        }

    }

    Connections {
        target: BackEnd

        onChangeImageView: {
            previewImg.source = imageSource ;
//            console.log("onChangeImageView:")
//            console.log(previewImg.source);
        }
    }

    Timer{
        id: progressUpadterTimer
        interval: 1000
        repeat: true
        running: true
        triggeredOnStart: true
        function msToTime(duration) {
                      var milliseconds = parseInt((duration % 1000) / 100),
                        seconds = Math.floor((duration / 1000) % 60),
                        minutes = Math.floor((duration / (1000 * 60)) % 60),
                        hours = Math.floor((duration / (1000 * 60 * 60)) % 24);

                      hours = (hours < 10) ? "0" + hours : hours;
                      minutes = (minutes < 10) ? "0" + minutes : minutes;
                      seconds = (seconds < 10) ? "0" + seconds : seconds;

                      return hours + ":" + minutes + ":" + seconds;
        }

        onTriggered: {
            if(root.printingState == 1) {
//               previewImg.source = BackEnd.getImagePreview();
//               console.log(previewImg.source);
               root.timeToFinish = progressUpadterTimer.msToTime(BackEnd.getRemainingTime()*1000);
               printProgress.currentValue = BackEnd.getPrintProgress();
               root.currentLayer = BackEnd.getPrintCurrentSlice();
               root.numOfLayers = BackEnd.getPrintTotalSlice();
               if(BackEnd.isLastPrintFile()) {
                   printProgress.currentValue = 0;
                   root.printingState = 0;
                   root.currentLayer = 0;
                   root.numOfLayers = 0;
                   previewImg.source =  "images/preview.png";
                   finishedMsg.open();
               }
            }


    //            console.log("timer");
    //            console.log(sliceImage.source);
        }
    }
}



