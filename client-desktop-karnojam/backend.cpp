#include "backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
    serverCmdMesg = new network_messages::NetServerCommands();
    serverResMesg = new network_messages::NetClientRes();

    gData = jStoring.getGeneralData();
    qDebug()<< "gData.ipAddress : " << gData.ipAddress;
//    cout<<"getFreeMemorySpaceSizeToMB:"<<Assistant::getFreeMemorySpaceSizeToMB("./")<<endl;;
//    cout<<"getFileSize:"<<Assistant::getFileSizeToMB("./previewImage1.svg")<<endl;;
//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    //    timer->start(1000);
}

QString BackEnd::getIpAddress()
{
    return gData.ipAddress;
}

int BackEnd::getOsType()
{
    return osType;
}

bool BackEnd::connectToThis(QString Address, QString Port)
{
    socket->connectToHost(Address, Port.toUShort());
    if(socket->waitForConnected(3000))
    {
        MachineAddress = Address;
        MachinePort = Port;
        if(machineConfigModel != NULL) {
            machineConfigModel->setMachineIpPort(MachineAddress, MachinePort);
        }
        if(materialConfigModel) {
            materialConfigModel->setMachineIpPort(MachineAddress, MachinePort);
        }
        if(jobModel != NULL) {
            jobModel->setMachineIpPort(MachineAddress, MachinePort);
        }
        if(motionConfigModel != NULL) {
            motionConfigModel->setMachineIpPort(MachineAddress, MachinePort);
        }
        if(sendFile != NULL) {
            sendFile->setMachineIpPort(MachineAddress, MachinePort);
        }
        gData.ipAddress = MachineAddress;
        jStoring.storeGeneralData(gData);
        socket->disconnectFromHost();
        return true;
    }
    return false;
}

int BackEnd::connectToServer()
{
    socket = new QTcpSocket();
    int result = 1;
    if(socket->state() != QTcpSocket::ConnectedState) {
        socket->connectToHost(MachineAddress, MachinePort.toUShort());
        result = socket->waitForConnected(3000);
    }
    if(result<0) {
        uiMessages->enqueue("Connection Error");
    }
    return result;
}

int BackEnd::disconnetFromServer()
{
    socket->disconnectFromHost();
    return 0;
}

int BackEnd::clearMessages()
{
    serverResMesg->Clear();
    serverCmdMesg->Clear();
    return 1;
}

bool BackEnd::manualMV(int mvDevice, int moveStep)
{
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_ManualMV);
    if(mvDevice == 1) {
        switch (moveStep) {
        case 1: {
            serverCmdMesg->set_imanualmv(network_messages::NetServerCommands::ManualMVStep::NetServerCommands_ManualMVStep_BuidlOneUp);
            break;
        }
        case -1: {
            serverCmdMesg->set_imanualmv(network_messages::NetServerCommands::ManualMVStep::NetServerCommands_ManualMVStep_BuidlOneDown);
            break;
        }
        case 10: {
            serverCmdMesg->set_imanualmv(network_messages::NetServerCommands::ManualMVStep::NetServerCommands_ManualMVStep_BuidlTenUp);
            break;
        }
        case -10: {
            serverCmdMesg->set_imanualmv(network_messages::NetServerCommands::ManualMVStep::NetServerCommands_ManualMVStep_BuidlTenDown);
            break;
        }
        case 50: {
            serverCmdMesg->set_imanualmv(network_messages::NetServerCommands::ManualMVStep::NetServerCommands_ManualMVStep_BuidlFiftyUp);
            break;
        }
        case -50: {
            serverCmdMesg->set_imanualmv(network_messages::NetServerCommands::ManualMVStep::NetServerCommands_ManualMVStep_BuidlFiftyDown);
            break;
        }
        default: {
            qDebug() << "manualMV wrong move step:"<< moveStep;
            return false;
            break;
        }

        }
    } else if(mvDevice == 0) {
        switch (moveStep) {
        case 0: {
            serverCmdMesg->set_imanualmv(network_messages::NetServerCommands::ManualMVStep::NetServerCommands_ManualMVStep_DoorDown);
            break;
        }
        case 1: {
            serverCmdMesg->set_imanualmv(network_messages::NetServerCommands::ManualMVStep::NetServerCommands_ManualMVStep_DoorUp);
            break;
        }
        default: {
            qDebug() << "manualMV wrong move step:"<< moveStep;
            return false;
            break;
        }
        }
    } else if(mvDevice == 2) {
        switch (moveStep) {
        case 0: {
            serverCmdMesg->set_imanualmv(network_messages::NetServerCommands::ManualMVStep::NetServerCommands_ManualMVStep_TiltDown);
            break;
        }
        case 1: {
            serverCmdMesg->set_imanualmv(network_messages::NetServerCommands::ManualMVStep::NetServerCommands_ManualMVStep_TiltUp);
            break;
        }
        default: {
            qDebug() << "manualMV wrong move step:"<< moveStep;
            return false;
            break;
        }
        }
    } else {
        qDebug() << "manualMV wrong move device:"<< mvDevice;
        return false;
    }

    size_t size = serverCmdMesg->ByteSizeLong();

    if(connectToServer() < 0) {
       qDebug() << "manualMV sendReq socket does not connect ";
       return false;
    } else {
       char *mBuf = new char[size];
       serverCmdMesg->SerializeToArray(mBuf, size);
       socket->write(mBuf, size);
       socket->waitForBytesWritten(3000);
       delete [] mBuf;
       socket->waitForReadyRead(2000);
       QByteArray temp = socket->readAll();
       serverResMesg->ParseFromArray(temp.data(), temp.size());
       if(serverResMesg->packetcode() == network_messages::NetClientRes::Error ) {
          qDebug()<< "manualMV NetClientRes::Error "<< QString::fromStdString(serverResMesg->errormesg());
          uiMessages->enqueue(QString::fromStdString(serverResMesg->errormesg()));
          return false;
       } else if(serverResMesg->packetcode() == network_messages::NetClientRes::Done ) {
            qDebug() << "manualMV NetClientRes Done" ;
            uiMessages->enqueue("Done");
            return true;
       } else {
           qDebug() << "manualMV manualMV wong response packetcode:" << serverResMesg->packetcode() ;
           return false;
       }
    }

    return true;
}

bool BackEnd::startProjectorCalib()
{
    return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_StartCalibrate, 0, 0,0);
}

bool BackEnd::finishProjectorCalib()
{
    return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_FinishCalibrate, 0, 0,0);
}

bool BackEnd::turnOffProjectorCalib()
{
    return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_ProjectorOffCalibrate, 0, 0,0);
}

bool BackEnd::goHomeProjectorCalib()
{
    return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_GoHomeCalibrate, 0, 0,0);
}

bool BackEnd::ledTurnOnProjectorCalib()
{
    return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDTurnOn, 0, 0,0);
}

bool BackEnd::ledTurnOffProjectorCalib()
{
    return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDTurnOff, 0, 0,0);
}

bool BackEnd::ejectUpProjectorCalib()
{
   return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_EjectUpCalibrate, 0, 0,0);
}

bool BackEnd::ejectDownProjectorCalib()
{
    return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_EjectDownCalibrate, 0, 0,0);
}

bool BackEnd::goPositionProjectorCalib(int position)
{
    return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_PositionCalibrate, position, 0,0);
}

bool BackEnd::materialLevelProjectorCalib(float position)
{
    return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_MaterialLevel, 0, 0,position);
}

bool BackEnd::fillVacuumProjectorCalib(float position)
{
    return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_VacuumFill, 0, 0,position);
}

float BackEnd::getSensorProjectorCalib()
{
    projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_GetSensor, 0, 0,0);
    qDebug() << "sensorVal: "<< sensorVal;
    return sensorVal;
}

bool BackEnd::ledIntensityProjectorCalib(int position)
{
    return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDIntensityCalibrate, position, 0,0);
}

bool BackEnd::materialTestProjectorCalib(int position, int matPat)
{
    return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_MaterialTestCalibrate, position, matPat,0);
}

bool BackEnd::setPattern(int matPat)
{
    return projectorCalib(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_ShowPattern, 0, matPat,0);
}

bool BackEnd::projectorCalib(int packetCode, int value1, int value2,float value3)
{
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Projector);
    switch (packetCode) {
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_StartCalibrate : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_StartCalibrate);
        break;
    }
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDTurnOn : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDTurnOn);
        break;
    }
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDTurnOff : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDTurnOff);
        break;
    }
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_EjectUpCalibrate : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_EjectUpCalibrate);
        break;
    }
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_EjectDownCalibrate : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_EjectDownCalibrate);
        break;
    }
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_FinishCalibrate : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_FinishCalibrate);
        break;
    }
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_GoHomeCalibrate : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_GoHomeCalibrate);
        break;
    }
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_PositionCalibrate : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_PositionCalibrate);
        serverCmdMesg->set_igopos(value1);
        break;
    }
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_MaterialLevel : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_MaterialLevel);
        qDebug() << "set_fmateriallevelmm: "<< value3;
        serverCmdMesg->set_fmateriallevelmm(value3);
        break;
    }
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_VacuumFill : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_VacuumFill);
        qDebug() << "set_ffillvacuumsec: "<< value3;
        serverCmdMesg->set_ffillvacuumsec(value3);
        break;
    }

    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_GetSensor : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_GetSensor);
        break;
    }
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDIntensityCalibrate : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDIntensityCalibrate);
        serverCmdMesg->set_igopos(value1);
        break;
    }
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_ShowPattern : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_ShowPattern);
        serverCmdMesg->set_imatpat(value2);
        break;
    }
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_MaterialTestCalibrate : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_MaterialTestCalibrate);
        serverCmdMesg->set_igopos(value1);
        serverCmdMesg->set_imatpat(value2);
        break;
    }
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_ProjectorOffCalibrate : {
        serverCmdMesg->set_icalibrstate(network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_ProjectorOffCalibrate);
        break;
    }
    default: {
        qDebug() << "projectorCalib wrong packetCode:"<< packetCode;
        return false;
        break;
    }
    }
    size_t size = serverCmdMesg->ByteSizeLong();

    if(connectToServer() < 0) {
       qDebug() << "projectorCalib sendReq socket does not connect ";
       return false;
    } else {
       char *mBuf = new char[size];
       serverCmdMesg->SerializeToArray(mBuf, size);
       socket->write(mBuf, size);
       socket->waitForBytesWritten(3000);
       delete [] mBuf;
       socket->waitForReadyRead(2000);
       QByteArray temp = socket->readAll();
       serverResMesg->ParseFromArray(temp.data(), temp.size());
       if(serverResMesg->packetcode() == network_messages::NetClientRes::Error ) {
          qDebug()<< "projectorCalib NetClientRes::Error "<< QString::fromStdString(serverResMesg->errormesg());
          uiMessages->enqueue(QString::fromStdString(serverResMesg->errormesg()));
          return false;
       } else if(serverResMesg->packetcode() == network_messages::NetClientRes::Done ) {
            qDebug() << "projectorCalib NetClientRes Done" ;
            uiMessages->enqueue("Done");
            return true;
       } else if(serverResMesg->packetcode() == network_messages::NetClientRes::ReadVal ) {
            qDebug() << "projectorCalib Received Val" ;
            sensorVal = serverResMesg->sensorval();
            if(sensorVal!=-1)
            {
                uiMessages->enqueue("Done");
                return true;
            }else {
                uiMessages->enqueue("Failed");
                return false;
            }

       } else {
           qDebug() << "projectorCalib wong response packetcode:" << serverResMesg->packetcode() ;
           return false;
       }
    }

    return true;
}

bool BackEnd::printCMD(int packetCode, int materialId, int motionId, int jobFileId)
{
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Print);
    switch (packetCode) {
    case network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_StopPrint : {
        serverCmdMesg->set_iprintstate(network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_StopPrint);
        break;
    }
    case network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_StartPrint : {
        serverCmdMesg->set_iprintstate(network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_StartPrint);
        serverCmdMesg->set_materialid(materialId);
        serverCmdMesg->set_motionid(motionId);
        serverCmdMesg->set_jobid(jobFileId);
        break;
    }
    case network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_PausePrint : {
        serverCmdMesg->set_iprintstate(network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_PausePrint);
        break;
    }
    default: {
        qDebug() << "printCMD wrong packetCode:"<< packetCode;
        return false;
        break;
    }
    }
    size_t size = serverCmdMesg->ByteSizeLong();

    if(connectToServer() < 0) {
       qDebug() << "printCMD sendReq socket does not connect ";
       return false;
    } else {
       char *mBuf = new char[size];
       serverCmdMesg->SerializeToArray(mBuf, size);
       socket->write(mBuf, size);
       socket->waitForBytesWritten(3000);
       delete [] mBuf;
       socket->waitForReadyRead(2000);
       QByteArray temp = socket->readAll();
       serverResMesg->ParseFromArray(temp.data(), temp.size());
       if(serverResMesg->packetcode() == network_messages::NetClientRes::Error ) {
          qDebug()<< "printCMD NetClientRes::Error "<< QString::fromStdString(serverResMesg->errormesg());
          uiMessages->enqueue(QString::fromStdString(serverResMesg->errormesg()));
          return false;
       } else if(serverResMesg->packetcode() == network_messages::NetClientRes::Done ) {
            qDebug() << "printCMD NetClientRes Done" ;

            if(packetCode == network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_StartPrint ) {

                if (QFile::exists(QString::fromStdString("./previewImage.svg") ) )
                {
                    QFile::remove(QString::fromStdString("./previewImage.svg"));
                }
//                file = new QFile("./previewImage.svg");
//                if (! file->open(QIODevice::WriteOnly)) {
//                    qDebug() << "printCMD can not open file";
//                    return false;
//                } else {
                    qDebug() << "connect slot to socket signal";
                    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
                    isPrinting = true;
                    isLastPrintingImage = false;
                    printingProgress = 0;
                    isGettingFile = false;
                    remainingTime = 0;
                    printImage = "";
                    mesgBuf.clear();
                    messageSize = 0;
//                }
            }
            return true;
       } else {
           qDebug() << "printCMD wong response packetcode:" << serverResMesg->packetcode() ;
           return false;
       }
    }

    return true;
}

bool BackEnd::stopPrint()
{
    return printCMD(network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_StopPrint,0,0,0);
}

bool BackEnd::pausePrint()
{
    return printCMD(network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_PausePrint,0,0,0);
}

bool BackEnd::startPrint(int materialIndex, int motionIndex, int jobFileIndex)
{
    qDebug()<<"startPrint index:"<<materialIndex<<", "<<motionIndex << ", "<< jobFileIndex;
    int materialId = materialConfigModel->getId(materialIndex);
    int motionId = motionConfigModel->getId(motionIndex);
    int jobId = jobModel->getId(jobFileIndex);
    qDebug()<<"startPrint id:"<<materialId<<", "<<motionId << ", "<< jobId;
    return printCMD(network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_StartPrint, materialId, motionId, jobId);
}

QString BackEnd::getImagePreview()
{
    return imagePriview;
}

int BackEnd::getPrintProgress()
{
    return printingProgress*100;
}

int BackEnd::getPrintCurrentSlice()
{
    return currentSlice;
}

int BackEnd::getPrintTotalSlice()
{
    return totalSlice;
}

bool BackEnd::isLastPrintFile()
{
    return isLastPrintingImage;
}

int BackEnd::getServerState()
{
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_GetState);
    size_t size = serverCmdMesg->ByteSizeLong();

    if(connectToServer() < 0) {
       qDebug() << "printCMD sendReq socket does not connect ";
       return false;
    } else {
       char *mBuf = new char[size];
       serverCmdMesg->SerializeToArray(mBuf, size);
       socket->write(mBuf, size);
       socket->waitForBytesWritten(3000);
       delete [] mBuf;
       socket->waitForReadyRead(2000);
       QByteArray temp = socket->readAll();
       serverResMesg->ParseFromArray(temp.data(), temp.size());
       if(serverResMesg->packetcode() == network_messages::NetClientRes::Ready ) {
          qDebug()<< "getServerState server ready ";
          return 0;
       } else if(serverResMesg->packetcode() == network_messages::NetClientRes::Progress ) {
            qDebug() << "getServerState network_messages::NetClientRes::Progress" ;
            if (QFile::exists(QString::fromStdString("./previewImage.svg") ) )
            {
                QFile::remove(QString::fromStdString("./previewImage.svg"));
            }
            qDebug() << "connect slot to socket signal";
            connect( socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()) );
            connect( socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()) );
            isPrinting = true;
            isLastPrintingImage = false;
            printingProgress = 0;
            isGettingFile = false;
            printImage = "";
            mesgBuf.clear();
            messageSize = 0;
            return 1;

       }
    }
    return  0;
}

void BackEnd::prinitngMessageHandler()
{

}

int BackEnd::getZoonQuantity()
{
    return 54;
}

bool BackEnd::setZoonValue(int zoonNum, int zoonValue)
{
    return true;
}

int BackEnd::getZoonValue(int zoonNum)
{
    return 5;
}

QString BackEnd::getMessage()
{
    if(messages.size() > 0) {
        return messages.dequeue();
    }
    return "";
}

void BackEnd::setUIMessages(UIMessages *uiMsg)
{
    uiMessages = uiMsg;
}

int BackEnd::getRemainingTime()
{
    return remainingTime;
}

bool BackEnd::isLcd()
{
    return lcd;
}

bool BackEnd::showConfig()
{
    return bShowConfig;
}


bool BackEnd::isTopDown()
{
    return topDown;
}



void BackEnd::socketReadyRead()
{
    QByteArray temp = socket->readAll();

    if(temp.size() == 0 ) {
        isLastPrintingImage = true;
        socket->close();
        disconnect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()) );
        disconnect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
    }

    for(int i=0; i< temp.size(); i++ ) {
        switch (messageState) {
        case 0: {
            mesgBuf.clear();
            messageSize = static_cast<uint16_t>(temp[i]);
//            qDebug() << "socketReadyRead messageSize :" << messageSize << ", i:"<< i;
            messageState = 1;
            break;
        }
        case 1: {
           clearMessages();
           size_t mesgBufSize = mesgBuf.size();
//           qDebug() << "socketReadyRead temp.size() - i "<< temp.size() - i  <<" , " << messageSize
//                    << ", messageSize- mesgBufSize : " << messageSize- mesgBufSize;
           if( (temp.size() - i) >= (messageSize - mesgBufSize)  ) {
             mesgBuf.append(temp.data()+i, messageSize - mesgBufSize);
              i = i + messageSize - mesgBufSize-1;
             serverResMesg->ParseFromArray(mesgBuf.data(), mesgBuf.size() );
             if(serverResMesg->packetcode() == network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Progress) {
                 fileSize = serverResMesg->size();
                 fileSizeCounter = 0;
                 printingProgress = static_cast<float>(serverResMesg->currentslice())  / static_cast<float>(serverResMesg->totalslice())  ;
                 currentSlice = serverResMesg->currentslice();
                 totalSlice = serverResMesg->totalslice();
                 remainingTime = serverResMesg->remaining_time();
//                 qDebug() << "socketReadyRead printingProgress:"<< printingProgress<< ", fileSize:"<<fileSize ;
                 messageState = 2;
                 if( serverResMesg->totalslice() == (serverResMesg->currentslice()+1) ) {
                     qDebug()<<"socketReadyRead is last file";
                     isLastPrintingImage = true;
                 }
                 if(imageFileNameToggle) {
                     remove("./previewImage1.svg");
                     preImgFile.setFileName("./previewImage1.svg"); //svg
                 } else {
                     remove("./previewImage2.svg");
                     preImgFile.setFileName("./previewImage2.svg"); //svg
                 }
                 if(! preImgFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
                      qDebug() << "socketReadyRead can not open file imageFileNameToggle:"<<imageFileNameToggle;
                 }
                 messageState = 2;
             } else {
                 qDebug() << "socketReadyRead mesgbuf completed packetcode:" << serverResMesg->packetcode();
             }
           } else {
             mesgBuf.append(temp.data()+i, temp.size()-i);
//             qDebug() << "socketReadyRead mesgbuf not completed mesgBuf.size():" <<mesgBuf.size() << ", i:"<<i << ", temp.size()-i : "<< temp.size()-i  ;
             i = temp.size();
           }
           break;
        }
        case 2: {
//            qDebug() << "socketReadyRead temp.size() - i "<< temp.size() - i
//                     << ", fileSize- fileSizeCounter" << fileSize- fileSizeCounter
//                     <<" , fileSize:" << fileSize<< ", fileSizeCounter:"<<fileSizeCounter <<", i:"<<i;
            if( (temp.size() - i ) >= (fileSize- fileSizeCounter)  ) {
                printImage.append(temp.data()+i);
                preImgFile.write(temp.data()+i, fileSize -fileSizeCounter );

                i = i + fileSize -fileSizeCounter - 1;
                fileSizeCounter = fileSize;
//                preImgFile.write(printImage.toStdString().c_str(), printImage.size());
                preImgFile.close();
                if(imageFileNameToggle) {
                    imagePriview = "file:/"+exePath+"/previewImage1.svg"; //"./previewImage.svg";
                } else {
                    imagePriview = "file:/"+exePath+"/previewImage2.svg"; //"./previewImage.svg";
                }

                emit changeImageView(imagePriview); //printImage
                messageState = 0;
                imageFileNameToggle = !imageFileNameToggle;
                if(isLastPrintingImage) {
                    socket->close();
                    disconnect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
                }
            } else {
                printImage.append(temp.data()+i);
                preImgFile.write(temp.data()+i, temp.size()-i);
                fileSizeCounter = fileSizeCounter + temp.size()-i;
                i = temp.size();
//                qDebug() << "recieving file not finished fileSizeCounter:"<<fileSizeCounter;
            }
           break;
        }
        default: {
            qDebug() << "socketReadyRead default :" << messageSize;
            break;
        }
        }
    }

}

void BackEnd::socketDisconnected()
{
    cout<< "*** socketDisconnected ***"<<endl;
   isLastPrintingImage = true;
   disconnect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()) );
}

void BackEnd::selectedFile(QString path)
{
    if(path.contains(".slc")) {

    } else {
        uiMessages->enqueue("Wrong, must be .slc file");
    }
}
