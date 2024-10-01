import QtQuick 2.12
import QtQuick.Window 2.12
import myextension 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Karnojam")
    color: "#000000"
    visibility: "FullScreen"


    ImageItem {
      id: liveImageItem
      height: window.height
      width: window.width

      onImageChanged: {
//          console.log("image changeed")
//          width = window.width
//          implicitWidth =  window.width
//          liveImageItem.visible = false; // !liveImageItem.visible
//          liveImageItem.visible = true;
      }

      Component.onCompleted: {
//          console.log("********** qml ImageItem BackEnd.setImageItem")
          BackEnd.setImageItem(liveImageItem);
      }
    }
//    Image {
//        id: previewImg
//        width: window.width
//        height: window.height
//        sourceSize.width:  window.width
//        sourceSize.height:  window.height
//        cache: false
//        source: "images/black.png"
//        visible: true
//        z: 100
//    }
//    Image {
//        id: projectorMask
//        width: window.width
//        height: window.height
//        sourceSize.width:  window.width
//        sourceSize.height:  window.height
//        cache: false
//        source: "images/Red.png" //project_mask.png
//        visible: false
////        antialiasing: true
////        z: 1000
//    }
//    Image {
//        id: previewImg2
//        width: window.width
//        height: window.height
//        sourceSize.width:  window.width
//        sourceSize.height:  window.height
//        cache: false
//        source: "images/black.png"
//        visible: false
//        z: 100
//    }

    Connections {
        target: BackEnd
        onSendQImage: {
        }

        onChangeImageView: {
//            previewImg.source = imageSource ;
//            previewImg.visible = true;
//            previewImg2.visible = false;
        }

        onToggleImageVisiblityErm: {
//            previewImg.visible = previewImg2.visible
//            previewImg2.visible = !previewImg2.visible;
        }

        onImageInitializeErm: {
//            previewImg.visible = true;
//            previewImg2.visible = false;
        }

        onChangeImageViewErm: {
//            if(toggle) {
//                previewImg.source = imageSource;
//            } else {
//                previewImg2.source = imageSource;

//            }
        }
    }

}
