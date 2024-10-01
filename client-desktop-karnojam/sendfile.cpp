#include "sendfile.h"

#include <QApplication>


SendFile::SendFile(QObject *parent) : QObject(parent)
{
    serverCmdMesg = new network_messages::NetServerCommands();
    serverResMesg = new network_messages::NetClientRes();
    jobCmd = new network_messages::Job3D();

}

void SendFile::setMachineIpPort(QString mAddress, QString mPort)
{
    MachineAddress = mAddress;
    MachinePort = mPort;
}

int SendFile::connectToServer()
{
    socket = new QTcpSocket();
    int result = 1;
    if(socket->state() != QTcpSocket::ConnectedState) {
        socket->connectToHost(MachineAddress, MachinePort.toUShort());
        result = socket->waitForConnected(3000);
    }
    if(result<0) {
        uiMessages->enqueue("can not connect to server");
    }
    return result;
}

int SendFile::disconnetFromServer()
{
    socket->disconnectFromHost();
    return 0;
}

QByteArray SendFile::fileChecksum(QString fileName, QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile f(fileName);
//    qDebug() << "hash length of Md5 : " << QCryptographicHash::hashLength(hashAlgorithm);
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&f)) {
//            qDebug() << hash.result();
            return hash.result();
        }
    }
    qDebug() << QByteArray();
    return QByteArray();
}

int SendFile::clearMessages()
{
    jobCmd->Clear();
    serverCmdMesg->release_job3d();
    serverCmdMesg->Clear();
    return 0;
}

void SendFile::setUIMessages(UIMessages *uiMsg)
{
     uiMessages = uiMsg;
}

void SendFile::SetTcpConnectionSignalSlot(bool connect)
{
    if(connect)
        QObject::connect(socket,SIGNAL(readyRead()),this,SLOT(TcpOnReadyRead()),Qt::QueuedConnection);
    else
        QObject::disconnect(socket,SIGNAL(readyRead()),this,SLOT(TcpOnReadyRead()));
}

void SendFile::TcpOnReadyRead()
{
    QByteArray bRes = socket->readAll();
    qDebug() << "TcpOnReadyRead : SendFile : SendFile : bRes.length : " << bRes.length();

    network_messages::NetClientRes Md5Msg;
    Md5Msg.ParseFromArray(bRes.data(), bRes.size());
    if(Md5Msg.packetcode() == network_messages::NetClientRes::PacketType::NetClientRes_PacketType_CheckFile ) {
        ResMd5 = true;
        QByteArray arr(Md5Msg.md5().data());
        qDebug() << "TcpOnReadyRead : SendFile : SendFile : md5 : " <<  arr;
        if(arr == CurrentfileCheckSum)
            ResMd5Check = true;
        else
            ResMd5Check = false;
    }
    else{
        ResMd5 = false;
    }
}

void SendFile::Md5SendGet()
{
    SetTcpConnectionSignalSlot(true);
    while(!ResMd5)
        QApplication::processEvents(QEventLoop::AllEvents);
    SetTcpConnectionSignalSlot(false);
}

void SendFile::SendMd5Results()
{
    clearMessages();
    char *mmBuf = new char[2048];
    size_t size;
    if(connectToServer() < 0){
           qDebug() << "SendFile : SendFile : JobModel addElement : socket does not connect ";
    }
    else{
        serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Job);
        jobCmd->set_packetcode(network_messages::Job3D::CheckFile);
        jobCmd->set_md5(ResMd5Check);
        serverCmdMesg->set_allocated_job3d(jobCmd);
        size = serverCmdMesg->ByteSizeLong();
//        qDebug() << "SendFile : SendMd5Results : size : " <<  size;
        /*qDebug() << "SendFile : SendMd5Results : SerializeToArray : " <<*/ serverCmdMesg->SerializeToArray(mmBuf, size);
        /*qDebug() << "SendFile : sendFile : Md5 response write size: " <<*/ socket->write(mmBuf,size);
        socket->waitForBytesWritten(3000);
//        qDebug() << "SendFile : sendFile : Md5 response : BytesWritten";
        if(ResMd5Check){
            qDebug() << "SendFile : sendFile : Md5 : true";
        }
        else{
            qDebug() << "SendFile : sendFile : Md5 : false";

            emit sendFileError("file validation error");
            emit SendTrueFile(ResMd5Check);
        }
    }

    delete [] mmBuf;
}

void SendFile::sendFile(QString jobName)
{
    qDebug() << "SendFile sendFile:"<< jobName;
    clearMessages();
    CurrentfileCheckSum = fileChecksum("./Jobs/"+jobName+".slc", QCryptographicHash::Algorithm::Md5);
    qDebug() << "SendFile : sendFile : CurrentfileCheckSum : " << CurrentfileCheckSum;

    int txByteCount = 1;
    ifstream jobfile ("./Jobs/"+jobName.toStdString()+".slc", ios::binary);
    if (!jobfile.is_open())
    {
       qDebug() << "SendFile : sendFile : can not open file name:" << QString::fromStdString(jobName.toStdString()); 
       emit sendFileError("File can not opened");
    }

    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Job);
    jobCmd->set_packetcode(network_messages::Job3D::Add);
    jobCmd->set_name(jobName.toStdString());
    uint64_t fileSize = Assistant::getFileSizeToByte("./Jobs/"+jobName.toStdString()+".slc");
    qDebug() << "SendFile : sendFile :fileSize :" << fileSize;
    jobCmd->set_size( fileSize ); //file.size()
    char *mBuf = new char[2048];
    serverCmdMesg->set_allocated_job3d(jobCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    serverCmdMesg->SerializeToArray(mBuf, size);

    unsigned int File_Size = fileSize - 2048;
    unsigned int File_Sector = File_Size / 1024;
    unsigned int File_LeftOver = File_Size % 1024;

    unsigned int File_Precet = File_Sector / 100;
    unsigned int File_PrecetLeftOver = File_Sector % 100;

    unsigned int precent = 0;


//    qDebug() << "sendFile : sendFile : File_Size : " << File_Size;
//    qDebug() << "sendFile : sendFile : File_Sector : " << File_Sector;
//    qDebug() << "sendFile : sendFile : File_LeftOver : " << File_LeftOver;
//    qDebug() << "sendFile : sendFile : File_Precet : " << File_Precet;
//    qDebug() << "sendFile : sendFile : File_PrecetLeftOver : " << File_PrecetLeftOver;

    ResMd5 = false;
    ResMd5Check = false;

    int j = 0;
    if(connectToServer() < 0) {
       qDebug() << "SendFile : SendFile : JobModel addElement : socket does not connect ";
       delete [] mBuf;
       emit sendFileError("connection error");
//       return false;
    } else {
        socket->write(mBuf,size);
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(3000);
        QByteArray bRes = socket->readAll();

        qDebug() << "SendFile : SendFile : bRes.length : " << bRes.length();
        serverResMesg->Clear();
        serverResMesg->ParseFromArray(bRes.data(), bRes.size());
        // start sending file
        if(serverResMesg->packetcode() == network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Done) {
             qDebug()<< "JobModel::addElement file name sended successfully;" ;
             char tx_buf[1024];
            while(txByteCount > 0 )
            {
                jobfile.read(tx_buf, 1024);
                txByteCount = jobfile.gcount();
//                txByteCount =  (int)file.read(filebuff,1024);
                if (txByteCount>0){
                    socket->write(tx_buf, txByteCount); // socket->write(filebuff, txByteCount);
                    socket->waitForBytesWritten(5000);
                } else {
                    socket->waitForBytesWritten(120000);
                }
                j++;
                if(j == File_Precet){
                    precent++;
//                    qDebug() << "sendFile : sendFile : precent : " << precent;
                    j = 0;
                    emit SendPrecentage(precent);
                }
                Assistant::sleepMiliSecond(1);

            }
            jobfile.close();


            Md5SendGet();

            disconnetFromServer();
            SendMd5Results();






        } else {
            qDebug()<< "JobModel::addElement error"<< QString::fromStdString(serverResMesg->errormesg()) ;
            delete [] mBuf;
            qDebug()<<"JobModel::sendFileError";
            emit sendFileError("sendfile error");
//            uploding = false;
//            return false;
        }
//        // wait for ack
//        socket->waitForReadyRead(10000);
//        bRes = socket->readAll();
//        serverResMesg->Clear();
//        serverResMesg->ParseFromArray(bRes.data(), bRes.size());
//        if(serverResMesg->packetcode() == network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Done) {
//            beginResetModel();
//            mList->job3DItems.append(item);
//            endResetModel();
//        } else {
//            qDebug()<< "JobModel::addElement ack error"<< QString::fromStdString(serverResMesg->errormesg()) << ", bRes.size():"<<bRes.size() ;
//        }

    }
    disconnetFromServer();
    delete [] mBuf;
//    refreshData();
    emit sendFileCompleted();
//    uploding = false;
//    return true;
}
