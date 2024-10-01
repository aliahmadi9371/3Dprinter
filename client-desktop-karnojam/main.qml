import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.FreeVirtualKeyboard 1.0

Window {

    property bool isLcd: BackEnd.isLcd()

    id: window
    visible: true
    visibility: window.isLcd ? "FullScreen" : "normal"
    width: window.isLcd ? 1024:1280
    height: window.isLcd ? 600:800
    title: qsTr("Karnojam")


//    Component.onCompleted: {
//        if(BackEnd.isLcd)
//        {
//            window.width = 1024
//            window.height = 600
//            window.visibility = "FullScreen"
//        }

////            window.showFullScreen();
//    }

    NavBar {
        id: navBar
    }

    StackLayout {
        id: route
        anchors.left: navBar.right
        width: window.width*7/8
        height: window.isLcd ? 600:800
        currentIndex: 0
        property bool connected: false
        function checkServerState() {
            if(BackEnd.getServerState() === 1) {
                printPage.printingState = 1;
            }
        }

        Component.onCompleted: {
            if(BackEnd.connectToThis(BackEnd.getIpAddress(), "7002")) { //192.168.1.134
                route.checkServerState();
                route.connected = true;
                console.log("connect to server successfully") ;
            } else {
                route.connected = false;
                console.log("Could not connect to server");
                disconnectMessage.open();
            }
        }

        PrintPage {
            id: printPage
        }

        MovePage {

        }

        JobsPage {

        }

        MaterialPage {
            id: materialPage
        }

        MotionPage {
            id: motionPage
        }

        CalibrationPage {

        }

        ConfigPage {
        }

        MaskPage {

        }

    }

    Popup{
        id: disconnectMessage
        x: (parent.width - width)/2
        y: 50
        width: 400
        height: 200
        modal: true
        focus: true
        closePolicy: Popup.NoAutoClose
        contentItem: ColumnLayout {
            width: parent.width*0.9
            Layout.alignment: Qt.AlignHCenter
            spacing: 5
            Text {
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Not Connected")
                font.pixelSize: 22
            }
            Text {
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Please check your connections...")
                font.pixelSize: 18
            }
            LargInput{
              id: connection_ip
              Layout.alignment: Qt.AlignHCenter
              text: BackEnd.getIpAddress()
            }
            Button {
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Connect")
                highlighted: true
                Material.background: Material.Green
                onClicked: {
                    if(BackEnd.connectToThis(connection_ip.text, "7002")) { // "192.168.1.134"
                        MaterialConfigModel.refreshData();
                        MotionConfigModel.refreshData();
                        JobModel.refreshData();
                        MachineConfigModel.refreshData();
                        route.checkServerState();
                        route.connected = true;
                        disconnectMessage.close();
                        console.log("connect to server successfully") ;
                    } else {
                        console.log("Could not connect to server");
                        canNotConnect.visible = true;
                        route.connected = false;
                    }
                }
            }
            Text {
                id: canNotConnect
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Can not connect")
                font.pixelSize: 18
                visible: false
                color: "red"
            }
        }
    }

    InputPanel {
        id: inputPanel
        y: route.height
        anchors.left: parent.left
        anchors.right: parent.right
        visible: window.isLcd
        z: 1
        parent: Overlay.overlay
        focus: true

        onYChanged: {
            if(inputPanel.y > 450) {
                route.y = 0;
            }
        }

        states: [
            State {
              name: "visible"
              when: Qt.inputMethod.visible
              PropertyChanges {
                target: inputPanel
                y: route.height - inputPanel.height
              }

            }
        ]

    }

    InfoMessage {
        id: notify
    }

    Timer {
        id: checkServerState
        interval: 1500// ms
        running: true
        repeat: true
        onTriggered: {
            if(route.connected) {
//                route.checkServerState();
            }
        }
    }
}
