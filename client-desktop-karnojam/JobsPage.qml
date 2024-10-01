import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.FreeVirtualKeyboard 1.0
import QtGraphicalEffects 1.12

//page root start
Page{
    id: root
    width: parent.width
    property int textLeftMargin: 40
    property int slideNum: 1
    property string jobName: ""
    property bool isLcd: BackEnd.isLcd();
    property bool isTrueFile: true;

    Connections {
        target: JobModel
        onSendPrecentageToQml: {
//            console.log("precent: " + precentage)
            if(precentage == 1){
                progressFile.visible = true;
                progressFileText.visible = true;
                progressValidText.visible = false;
            }
            else if(precentage == 100){
                progressFileText.visible = false;
                progressValidText.visible = true;
                progressValidText.text = qsTr("               ") +  qsTr("File Validation");
            }
            progressFile.value = precentage;
            progressFileText.text = qsTr("             ") + precentage + qsTr(" % Complete");
        }

        onNewJobName: {
            name_form.inputText = NewName;
            root.isTrueFile = JobModel.getTrueFile();
        }
    }

    //ColumnLayout .. start
    ColumnLayout{
        width: parent.width

        //RowLayout .. start
        RowLayout{
            width: parent.width
            Layout.alignment: Qt.AlignHCenter
            spacing: 20

            //Button .. start
            Button{
                text: qsTr("Browse")
                highlighted: true
                Material.background: Material.Blue
                onClicked:{
                    root.isTrueFile = true;
                    if(BackEnd.getOsType() === 1 || !root.isLcd){
                        busyIndicatorUpload.visible = false;
                        dialogJobUpload.open();
                    }
                    else{
                        if(FileItemsModel.isUSBDrive()){
                            FileItemsModel.refreshDirectory();
                            fileDialogPopup.open();
                        }
                        else{
                            notify.message = "No USB";
                            notify.open();
                            notify.trigerTime();
                        }
                    }
                }
            }
            //Button .. end

            //NameForm name_form start
            NameFormJob{
                id: name_form
                label: "Job Name"
                placeHolder: "Job Name"
                btnLabel: "Upload"
                onAccept:{
                    busyIndicatorUpload.visible = false;
                    root.jobName = inputText;

                    progressFile.visible = true;
                    busyIndicatorUpload.visible = false;

                    progressBusy.open();
                    console.log("root.jobName : " + root.jobName)
                    JobModel.addNewJob(root.jobName);
                    delayRefresh.running = true;
                    delayRefresh.jobToDo = 2;
                    delayRefresh.start();
                }
            }
            //NameForm name_form end

        }
        //RowLayout .. end

        //ToolSeparator .. start
        ToolSeparator{
            orientation: Qt.Horizontal
            implicitWidth: parent.width*0.9
            Layout.alignment: Qt.AlignHCenter
        }
        //ToolSeparator .. end

        //RowLayout .. start
        RowLayout{
            width: parent.width*0.95
            Layout.alignment: Qt.AlignHCenter
            spacing: 10

            //ColumnLayout .. start
            ColumnLayout{
                width: parent.width*7/24
                Text{
                    text: qsTr("Jobs List")
                    font.pointSize: 14
                }

                Component.onCompleted:{
                    console.log("Job page onCompleted");
                    JobModel.refreshData();
                    console.log(JobModel.size());
                }

                //Rectangle .. start
                Rectangle{
                    width: parent.width
                    height: window.height*5.5/8
                    border.width: 2
                    border.color: "black"
                    radius: 10

                    //ListView materialList start
                    ListView{
                        id: materialList
                        Layout.topMargin: 10
                        width: parent.width*0.95;
                        height: window.height*5/8
                        spacing: 10
                        Layout.alignment: Qt.AlignHCenter
                        x: 10
                        y:5
                        model: JobModel
                        delegate: JobItem{
                            jobId: model.index+1
                            name: model.Name
                            onJobDelete:{
                               deleteDialog.jobId = jobId;
                               deleteDialog.open();
                            }
                        }

                        ScrollBar.vertical: ScrollBar{
                        }

                    }
                    //ListView materialList end

                }
                //Rectangle .. end

            }
            //ColumnLayout .. end

            //ColumnLayout .. start
            ColumnLayout{
                width: parent.width*17/24

                //Text .. start
                Text{
                    text: qsTr("Preview")
                    font.pointSize: 14
                }
                //Text .. end

                //Image .. start
                Image{
                    id: previewImg
                    sourceSize.width:  window.width*9/16
                    source: "images/preview.png"
                    cache: false
                }
                //Image .. start

                //Slider sliderVolumePosition start
                Slider{
                    id: sliderVolumePosition
                    implicitWidth: window.width*9/16
                    from: 1
                    value: 1
                    to: root.slideNum
                    enabled: false
                    onMoved:{
                        previewImg.source = JobModel.getFrameImage(value);
                    }
                }
                //Slider sliderVolumePosition end

            }
            //ColumnLayout .. end
        }
        //RowLayout .. end

    }
    //ColumnLayout .. end

    //FileDialog dialogJobUpload start
    FileDialog{
        id: dialogJobUpload
        modality: Qt.WindowModal
        title: "Choose a file"
        selectExisting: true
        nameFilters: ["Slc File (*.slc)"]
        sidebarVisible: true
        onAccepted:{
            dialogJobUpload.close();

            busyIndicatorUpload.visible = true;
            progressFile.visible = false;


            delayRefresh.filePath = dialogJobUpload.fileUrl;
            delayRefresh.copyStarted = false;

            progressFile.visible = false;
            busyIndicatorUpload.visible = true;

            progressBusy.open();
            delayRefresh.running = true;
            delayRefresh.jobToDo = 1;
            delayRefresh.start();
        }
        onRejected:{
            console.log("Rejected")
        }
    }
    //FileDialog dialogJobUpload end

    //Popup fileDialogPopup start
    Popup{
        id: fileDialogPopup
        padding: 0
        width: 600
        height: 400
        x: Math.round((parent.width - width) / 2)
        y: 30
        z: 10
        focus: true
        closePolicy: Popup.CloseOnEscape

        //ColumnLayout .. start
        ColumnLayout{
            anchors.fill: parent

            //ListView .. start
            ListView{
                width: 500;
                height: 250
                Layout.alignment: Qt.AlignHCenter
                property bool auth: false
                function setAuth(temp) {root.auth = temp;}
                model: FileItemsModel
                delegate: FileItem{
                    name: model.Name
                    isDirectory: model.isDirectory
                    path: model.Path
                    onSelected:{

                        fileDialogPopup.close();
                        delayRefresh.filePath = "file://"+filePath;
                        delayRefresh.copyStarted = false;

                        progressFile.visible = false;
                        busyIndicatorUpload.visible = true;

                        progressBusy.open();
                        delayRefresh.running = true;
                        delayRefresh.jobToDo = 1;
                        delayRefresh.start();
                    }
                }

                ScrollBar.vertical: ScrollBar{
                }

            }
            //ListView .. end

            //RowLayout .. start
            RowLayout{
                width: parent.width
                Layout.alignment: Qt.AlignHCenter
                spacing: 25

                //Botton .. start
                Button{
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Close")
                    highlighted: true
                    Material.background: Material.Red
                    onClicked:{
                        fileDialogPopup.close();
                    }
                }
                //Botton .. end

                //Botton .. start
                Button{
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Back")
                    highlighted: true
                    Material.background: Material.Blue
                    onClicked:{
                         FileItemsModel.backDirectory();
                    }
                }
                //Botton .. end

            }
            //RowLayout .. end

        }
        //ColumnLayout .. end

    }
    //Popup fileDialogPopup end

    //Timer delayRefresh start
    Timer{
        id: delayRefresh
        interval: 1500//30 // 60 Hz
        running: false
        repeat: true
        property string filePath: ""
        property bool copyStarted: false
        property int state: 0
        property int jobToDo: 0   // 0:nothing 1:copying 2:uploading
        onTriggered:{
            if (jobToDo === 2)
            {
                if(!JobModel.getUploadingState()) {
                    if(root.isTrueFile){
                        JobModel.refreshData();
                    }
                    delayRefresh.running = false;
                    delayRefresh.state = 0;
                    delayRefresh.jobToDo = 0;

                    progressFile.visible = false;
                    busyIndicatorUpload.visible = true;

                    progressBusy.close();
                }
            }else if (jobToDo === 1){
                if (!delayRefresh.copyStarted )
                {
                    console.log("delayRefresh.filePath : " + delayRefresh.filePath)
                    JobModel.setTemporaryJob(delayRefresh.filePath);
                    delayRefresh.copyStarted = true;
                }
                root.slideNum = JobModel.getNumSlices();
                root.isTrueFile = JobModel.getTrueFile();
                console.log("JobModel.getNumSlices() : "+ JobModel.getNumSlices())
                console.log("JobModel.getTrueFile() : " + JobModel.getTrueFile())
                if(root.slideNum !== 0 && root.isTrueFile) {
                    delayRefresh.running = false;
                    delayRefresh.state = 0;
                    delayRefresh.jobToDo = 0;

                    progressFile.visible = false;
                    busyIndicatorUpload.visible = true;

                    progressBusy.close();

                    name_form.inputText = JobModel.getFileName();
                    sliderVolumePosition.enabled = true;
                    previewImg.source = JobModel.getFrameImage(1);
                }
                else if(!root.isTrueFile){
                    delayRefresh.running = false;
                    delayRefresh.state = 0;
                    delayRefresh.jobToDo = 0;

                    progressFile.visible = false;
                    busyIndicatorUpload.visible = true;

                    progressBusy.close();
                    name_form.inputText = "_error";

                    previewImg.source = "images/preview.png"
                }
            }
        }
    }
    //Timer delayRefresh end

    //Popup deleteDialog start
    Popup{
        id: deleteDialog
//        anchors.centerIn: parent
        x: (parent.width - width)/2
        y: 50
        width: 400
        height: 200
        modal: true
        focus: true
        property int jobId: 1

        contentItem: ColumnLayout{
            width: parent.width*0.9
            Layout.alignment: Qt.AlignHCenter
            spacing: 5

            //Text .. start
            Text {
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Are you sure?")
                font.pixelSize: 22
            }
            //Text .. end

            //RowLayout .. start
            RowLayout {
                width: parent.width
                Layout.alignment: Qt.AlignHCenter
                spacing: 30

                //Button .. start
                Button{
                    text: qsTr("No")
                    highlighted: true
                    Material.background: Material.Red
                    onClicked: {
                       deleteDialog.close();
                    }
                }
                //Button .. end

                //Button .. start
                Button{
                    text: qsTr("Yes")
                    highlighted: true
                    Material.background: Material.Green
                    onClicked: {
                        JobModel.removeJob(deleteDialog.jobId);
                        deleteDialog.close();
                    }
                }
                //Button .. end

            }
            //RowLayout .. end

        }
    }
    //Popup deleteDialog end


    //Popup progressBusy start
    Popup{
        id: progressBusy
//        anchors.centerIn: parent
        closePolicy: Popup.NoAutoClose
        x: (parent.width - width)/2
        y: 50
        width: 600
        height: 400
        modal: true
        focus: true
//        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        contentItem: ColumnLayout{
            width: parent.width*0.9
            Layout.alignment: Qt.AlignHCenter
            spacing: 5

            //Text .. start
            Text{
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Please Wait...")
                font.pixelSize: 18
            }
            //Text .. end

            //BusyIndicator .. start
            BusyIndicator {
                id: busyIndicatorUpload
                Layout.alignment: Qt.AlignHCenter
                running: true
                width: 200
                height: 200
                implicitWidth: 200
                implicitHeight: 200
            }
            //BusyIndicator .. end

            ProgressBar{
                id: progressFile
                Layout.alignment: Qt.AlignHCenter
                width: 200
                height: 20

                implicitWidth: 200
                implicitHeight: 20
                indeterminate: false
                from: 0
                to: 100
                value: 0
                visible: false

                Text {
                    id: progressFileText
                    text: qsTr("")
                    Layout.alignment: Qt.AlignCenter
                    visible: false
                }

                Text {
                    id: progressValidText
                    text: qsTr("")
                    Layout.alignment: Qt.AlignCenter
                    visible: false
                }

                clip: true
                background: Rectangle {
//                    implicitWidth: 200
//                    implicitHeight: 6
                    border.color: "#999999"
                    radius: 5
                }
                contentItem: Item {
//                    implicitWidth: 200
//                    implicitHeight: 4

                    Rectangle {
                        id: bar
                        width: progressFile.visualPosition * parent.width
                        height: parent.height
                        radius: 5
                    }

                    LinearGradient {
                        anchors.fill: bar
                        start: Qt.point(0, 0)
                        end: Qt.point(bar.width, 0)
                        source: bar
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "#17a81a" }
                            GradientStop { id: grad; position: 0.5; color: Qt.lighter("#17a81a", 2) }
                            GradientStop { position: 1.0; color: "#17a81a" }
                        }
                        PropertyAnimation {
                            target: grad
                            property: "position"
                            from: 0.1
                            to: 0.9
                            duration: 1000
                            running: true
                            loops: Animation.Infinite
                        }
                    }
                    LinearGradient {
                        anchors.fill: bar
                        start: Qt.point(0, 0)
                        end: Qt.point(0, bar.height)
                        source: bar
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: Qt.rgba(0,0,0,0) }
                            GradientStop { position: 0.5; color: Qt.rgba(1,1,1,0.3) }
                            GradientStop { position: 1.0; color: Qt.rgba(0,0,0,0.05) }
                        }
                    }
                }
//                PropertyAnimation {
//                    target: progressFile
//                    property: "value"
//                    from: 0
//                    to: 1
//                    duration: 5000
//                    running: true
//                    loops: Animation.Infinite
//                }
            }
        }
    }
    //Popup progressBusy end

}
//page root end
