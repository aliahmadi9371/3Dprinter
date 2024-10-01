import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4


Rectangle {
    id: navBarRectangle
    width: window.width/8
    height: window.height
    color: "#314455"

    property bool showConfig: BackEnd.showConfig()

    Component.onCompleted: {

        if(showConfig){
            configPage.visible = true
        }
    }


    Column {
        width: window.width/8
        height: window.height
        NavBarItem {
            id: printPage
           imageSource: "images/logo2.png"
           activeImageSource: "images/logo2.png"
           name: "Print"
//           imageHeight: navBarRectangle.showConfig ? (window.height/7)*0.5 : (window.height/6)*0.5
//           imageHeight: (window.height/6)*0.5
           pageIndex: 0
           MouseArea {
              anchors.fill: parent;
              onPressed: {
                 route.currentIndex = printPage.pageIndex;
              }
           }
        }
        NavBarItem {
            id: movePage
            imageSource: "images/move_white.png"
            activeImageSource: "images/move_red.png"
            name: "Move"
            pageIndex: 1
            MouseArea {
               anchors.fill: parent;
               onPressed: {
                  route.currentIndex = movePage.pageIndex;
               }
            }
        }
        NavBarItem {
            id: jobPage
            imageSource: "images/upload_white.png"
            activeImageSource: "images/upload_red.png"
            name: "Upload Files"
            pageIndex: 2
            MouseArea {
               anchors.fill: parent;
               onPressed: {
                  route.currentIndex = jobPage.pageIndex;
                  JobModel.refreshData();
               }
            }
        }
        NavBarItem {
            id: materialPage
            imageSource: "images/cup_white.png"
            activeImageSource: "images/cup_red.png"
            name: "Material"
            pageIndex: 3
            MouseArea {
               anchors.fill: parent;
               onPressed: {
                  route.currentIndex = materialPage.pageIndex;
                   MaterialConfigModel.refreshData();
               }
            }
        }
        NavBarItem {
            id: motionPage
            imageSource: "images/motion_white.png"
            activeImageSource: "images/motion_red.png"
            name: "Motion"
            pageIndex: 4
            MouseArea {
               anchors.fill: parent;
               onPressed: {
                  route.currentIndex = motionPage.pageIndex;
                   MotionConfigModel.refreshData();
               }
            }
        }
        NavBarItem {
            id: calibrationPage
            imageSource: "images/calibration_white.png"
            activeImageSource: "images/calibration_red.png"
            name: "Calibration"
            pageIndex: 5
            MouseArea {
               anchors.fill: parent;
               onPressed: {
                  route.currentIndex = calibrationPage.pageIndex;
               }
            }
        }

        NavBarItem {
            id: configPage
            visible: false
            imageSource: "images/config_white.png"
            activeImageSource: "images/config_red.png"
            name: "Config"
            pageIndex: 6
            MouseArea {
               anchors.fill: parent;
               onPressed: {
                  route.currentIndex = configPage.pageIndex;
                   MachineConfigModel.refreshData();
               }
            }
        }
    }
}
