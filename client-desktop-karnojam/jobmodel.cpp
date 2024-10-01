#include "jobmodel.h"
#include "joblist.h"

JobModel::JobModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{

    serverCmdMesg = new network_messages::NetServerCommands();
    serverResMesg = new network_messages::NetClientRes();
    jobCmd = new network_messages::Job3D();

    if(!QDir("Jobs").exists()) {
        QDir().mkdir("Jobs");
    } else {
        cout<<"Folder Jobs exists"<<endl;
    }

     mList = new JobList();
     iSelcetedBkgCol = 3 ;
//     imgView.Create(3, 3, rect.right-7,(rect.right - 7)/1.77777777);
//     imgView.Create(3, 3, 400-7,(400 - 7)/1.77777777);
}

int JobModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
            return 0;

        return mList->items().size();
}

QVariant JobModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
          return QVariant();


      const __Job3D item = mList->items().at(index.row());
      switch (role) {
       case Name:
          return QVariant( QString::fromStdString(item.name));
       case Size:
          return QVariant(item.size);
      }

      return QVariant();
}

bool JobModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // ************ we do not need this
    return true;
}

QHash<int, QByteArray> JobModel::roleNames() const
{
    QHash<int, QByteArray> names;
        names[Name] = "Name";
        names[Size] = "Size" ;
        return names;
}

Qt::ItemFlags JobModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
            return Qt::NoItemFlags;

        return Qt::ItemIsEditable;
}

JobList *JobModel::list() const
{
     return mList;
}

void JobModel::setList(JobList *list)
{
    beginResetModel();
       if(mList)
           mList->disconnect(this);

       mList = list;

       endResetModel();
}

bool JobModel::addElement(__Job3D item)
{
    clearMessages();
    int txByteCount = 1;
    ifstream jobfile ("./Jobs/"+item.name+".slc", ios::binary);
    if (!jobfile.is_open())
    {
       qDebug() << "JobModel addElement can not open file  name:"<< QString::fromStdString(item.name);
       uiMessages->enqueue("File can not opened");
       return false;
    }
//     QFile file(QString::fromStdString("./Jobs/"+item.name+".slc"));
//     if(!file.open(QIODevice::ReadOnly)) {
//        qDebug() << "JobModel addElement can not open file  name:"<< QString::fromStdString(item.name);
//        uiMessages->enqueue("File can not opened");
//        return false;
//     }

    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Job);
    jobCmd->set_packetcode(network_messages::Job3D::Add);
    jobCmd->set_name(item.name);
    uint64_t fileSize = Assistant::getFileSizeToByte("./Jobs/"+item.name+".slc");
    qDebug() << "fileSize:"<<fileSize;
    jobCmd->set_size( fileSize ); //file.size()
    char *mBuf = new char[2048];
    serverCmdMesg->set_allocated_job3d(jobCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    serverCmdMesg->SerializeToArray(mBuf, size);

    if(connectToServer() < 0) {
       qDebug() << "JobModel addElement socket does not connect ";
       delete [] mBuf;
       uploding = false;
       return false;
    } else {
        socket->write(mBuf,size);
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(3000);
        QByteArray bRes = socket->readAll();
        serverResMesg->Clear();
        serverResMesg->ParseFromArray(bRes.data(), bRes.size());
        // start sending dile
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

                Assistant::sleepMiliSecond(1);
            }
            jobfile.close();
            beginResetModel();
            mList->job3DItems.append(item);
            endResetModel();
        } else {
            qDebug()<< "JobModel::addElement error"<< QString::fromStdString(serverResMesg->errormesg()) ;
            delete [] mBuf;
            uploding = false;
            return false;
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
    uploding = false;
    return true;
}

bool JobModel::fileCopy(string src, string dest)
{
//    cout<<"filecopy src"<<src<< ", dest:" << dest<<endl;
    std::ifstream  fileSrc(src, std::ios::binary);
    std::ofstream  fileDst(dest,   std::ios::binary);
   fileDst << fileSrc.rdbuf();
   fileSrc.close();
   fileDst.close();
   return true;
}

int JobModel::getId(int index)
{
    if( (0 > index) || (index >= size())) {
        qDebug()<< "JobModel::getId index is wrong index:"<< index<< ", size:"<<size();
        return -1;
    }

    return mList->items().at(index).id;
}

int JobModel::size()
{
    return mList->items().size();
}

bool JobModel::addNewJob(QString name)
{
//    if (Assistant::isFileExists("./Jobs/"+name.toStdString()+".slc")) //QFile::exists("./Jobs/"+name+".slc")
//    {
//        qDebug() << "JobModel : addNewJob : delete file with the same name";
//        QFile::remove("./Jobs/"+name+".slc");
//    }
//    QString newFilePath = "./Jobs/"+name+".slc";
//    QString tempVar = tempFilePath;

//    qDebug() << "JobModel : addNewJob : newFilePath : " << newFilePath;
//    qDebug() << "JobModel : addNewJob : tempFilePath : " << tempFilePath;
//    string str;

//#ifdef linux
//    tempVar.replace("file://", "");
//    str = tempVar.toStdString();
//    if(Assistant::getFreeMemorySpaceSizeToMB("./") < (Assistant::getFileSizeToMB(str)+500)) {
//        uiMessages->enqueue("Not enough disk space");
//        return false;
//    }
//#endif

//#ifdef _WIN32
//    tempVar.replace("file:///", "");
//    str = tempVar.toStdString();
//#endif

//    if(!fileCopy(str, "./Jobs/"+name.toStdString()+".slc")) {
//        qDebug() << "JobModel : addNewJob : can not copy newFilePath:"<<newFilePath <<", tempFilePath:"<<tempFilePath;
//        uiMessages->enqueue("could not copy file");
//        return false;
//    }
//    qDebug() << "JobModel : addNewJob : copy file to ./Jobs folder : " << tempFilePath;

//    if(!QFile::copy(tempFilePath, newFilePath)) {
//        qDebug() << "addNewJob can not copy newFilePath:"<<newFilePath <<", tempFilePath:"<<tempFilePath;
//        return false;
//    }
    if(name == "")
        tempFileInfo.true_proc = false;
    if(tempFileInfo.true_proc)
    {
        tempFileInfo.name = name.toStdString();
        qDebug() << "JobModel : addNewJob : tempFileInfo.name : " << name;
        uploding = true;
    //     auto f1 = std::async(std::launch::async, &JobModel::addElement, this, tempFileInfo);
    //    thread th(&JobModel::addElement, this, tempFileInfo);
    //    th.detach();
        emit sendFile(name);
        return true;
    }
    else{
        qDebug() << "JobModel : addNewJob : tempFileInfo.name : " << name;
        qDebug() << "JobModel : addNewJob : invalid file can not be uploaded";
        uiMessages->enqueue("please choose correct file");
        uploding = false;
        return false;
    }

//    return addElement(tempFileInfo);
}

bool JobModel::getUploadingState()
{
    return uploding;
}

void JobModel::updateData(QString ipAddr, QString portAddr)
{
    MachineAddress = ipAddr;
    MachinePort = portAddr;
}

void JobModel::refreshData()
{
//    qDebug() << "JobModel refreshData:";
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Job);
    jobCmd->set_packetcode(network_messages::Job3D::GetALL);
    serverCmdMesg->set_allocated_job3d(jobCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);

    if(connectToServer() < 0) {
       qDebug() << "JobModel sendReq socket does not connect ";
    } else {
       socket->write(mBuf, size);
       socket->waitForBytesWritten(3000);
       socket->waitForReadyRead(2000);
       QByteArray temp = socket->readAll();
       serverResMesg->ParseFromArray(temp.data(), temp.size());
       if(serverResMesg->packetcode() == network_messages::NetClientRes::Founded ) {
           qDebug() << "JobModel refreshData jobs quantity:"<<serverResMesg->jobs_size();
           beginResetModel();
           mList->job3DItems.clear();
           for(int i=0; i<serverResMesg->jobs_size(); i++) {
               __Job3D job ;
               network_messages::Job3D jobMesg = serverResMesg->jobs(i);
               job.id = jobMesg.rowid();
               job.name = jobMesg.name();
               job.size = jobMesg.size();
               mList->addJob3D(job);
           }
           endResetModel();
       } else if(serverResMesg->packetcode() == network_messages::NetClientRes::NotFound ) {
            qDebug() << "JobModel refreshData NotFound" ;
           beginResetModel();
           mList->job3DItems.clear();
           endResetModel();
       } else {
           qDebug() << "JobModel refreshData can not Recieve" ;
       }
    }
    disconnetFromServer();
    delete [] mBuf;
}

bool JobModel::removeJob(int index)
{
    if(index > size()) {qDebug() << "JobModel::removeConfig wrong index:"<<index; return false;}
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Job);
    jobCmd->set_packetcode(network_messages::Job3D::Delete);
    jobCmd->set_rowid(mList->job3DItems[index-1].id);
    jobCmd->set_name(mList->job3DItems[index-1].name);
    serverCmdMesg->set_allocated_job3d(jobCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);
//    qDebug() <<"removeJob id:"<< jobCmd->rowid();
    if(connectToServer() < 0) {
       qDebug() << "JobModel removeConfig socket does not connect ";
       delete [] mBuf;
    } else {
        socket->write(mBuf, size);
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(2000);
        QByteArray temp = socket->readAll();
        serverResMesg->ParseFromArray(temp.data(), temp.size());
        if(serverResMesg->packetcode() == network_messages::NetClientRes::Done) {
            beginResetModel();
            QString jobName = QString::fromStdString(mList->job3DItems[index-1].name);
            if (Assistant::isFileExists("./Jobs/"+jobName.toStdString()+".slc")) // QFile::exists("./Jobs/"+jobName+".slc")
            {
                QFile::remove("./Jobs/"+jobName+".slc");
            }
            mList->job3DItems.remove(index-1);
            endResetModel();
        } else {
           qDebug() << "JobModel removeConfig can not delete"<< QString::fromStdString(serverResMesg->errormesg()) ;
           delete [] mBuf;return false;
        }
    }
    disconnetFromServer();
    delete [] mBuf;
    return true;
}

void JobModel::sendJobToServer()
{

}

void JobModel::setMachineIpPort(QString mAddress, QString mPort)
{
    MachineAddress = mAddress;
    MachinePort = mPort;
}

int JobModel::connectToServer()
{
    socket = new QTcpSocket();
    int result = 1;
    if(socket->state() != QTcpSocket::ConnectedState) {
        socket->connectToHost(MachineAddress, MachinePort.toUShort());
        result = socket->waitForConnected(3000);
    }
    if(result<0) {
        uiMessages->enqueue("can connect to server");
    }
    return result;
}

int JobModel::disconnetFromServer()
{
    socket->disconnectFromHost();
    return 0;
}

int JobModel::clearMessages()
{
    jobCmd->Clear();
    serverCmdMesg->release_job3d();
    serverCmdMesg->Clear();
    return 0;
}

int JobModel::getNumSlices()
{
    return tempFileInfo.iNumSlices;
}

bool JobModel::getTrueFile()
{
    return tempFileInfo.true_proc;
}

QString JobModel::CopyFileHere(QString name)
{
    QFileInfo file(name);
    QString src = name;
    QString dst = "./Jobs/"+file.fileName();
    qDebug() << "JobModel : CopyFileHere : src : " << src;
    qDebug() << "JobModel : CopyFileHere : dst : " << dst;

    string fsrc = src.toStdString();
    string fdst = dst.toStdString();

    if(!fileCopy(fsrc, fdst)) {
        qDebug() << "JobModel : CopyFileHere : can not copy src :" << src << " to dst: " << dst;
        uiMessages->enqueue("could not copy file");
        return "false""";
    }
    qDebug() << "JobModel : CopyFileHere : can copy src :" << src << " to dst: " << dst;
    return dst;
}

void JobModel::ClearFiles()
{
    QString path = "./Jobs";
    QDir dir(path);
    dir.setNameFilters(QStringList() << "*.*");
    dir.setFilter(QDir::Files);
    foreach(QString dirFile, dir.entryList())
    {
        dir.remove(dirFile);
    }
}

QString JobModel::FileNameFromQmlToCpp(QString filepath)
{
#ifdef linux
    filepath.replace("file://", "");
#endif

#ifdef _WIN32
    filepath.replace("file:///", "");
#endif

    return filepath;
}

void JobModel::setTemporaryJob(QString fileDir)
{
    ClearFiles(); //clear files

    qDebug() << "JobModel : setTemporaryJob : fileDir : " << fileDir;
    fileDir = FileNameFromQmlToCpp(fileDir);

    //copy file to Jobs
    QString dst = CopyFileHere(fileDir);
    if(dst == ""){
        SetFalseFile();
        return;
    }

    QFileInfo file(dst);
    fileName = file.fileName();
    QString suffix = file.completeSuffix();

//    qDebug() << "JobModel : setTemporaryJob : fileName extention : " << suffix;
    if(suffix != "slc"){
        uiMessages->enqueue("file type error");
        SetFalseFile();
        return;
    }

    fileName = fileName.replace(".slc", "");
    tempFilePath = dst;

    qDebug() << "tempFilePath : " << tempFilePath;
    string str = fileDir.toStdString();

    qDebug() << "fileName:"<<fileName;
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    ImportSlcInfo(cstr, &tempFileInfo);
    delete[] cstr;
//    return tempFileInfo.iNumSlices;
}

QString JobModel::getFileName()
{
    return fileName;
}

QString JobModel::getFrameImage(int sliceNum)
{
//        cout<< "getFrameImage:"<< tempFileInfo.iNumSlices << ", "<< sliceNum;
        QFile file1("./tempJob.svg");  file1.remove();
        QFile file2("./tempJob2.svg"); file2.remove();
        if(sliceNum <= tempFileInfo.iNumSlices) {
            string  tempFile = "./tempJob.svg";
            if(imageFileNameToggle) {
                tempFile = "./tempJob2.svg";
            }
            imageFileNameToggle = !imageFileNameToggle;
    //        cout<< QDir::currentPath().toStdString()<<endl;
//            cout<< ", imageFileNameToggle:"<<imageFileNameToggle<<endl;
            ExportFrameToSVG(&tempFileInfo, sliceNum, 3840, 2160, 0.1, tempFile.c_str());
            if(imageFileNameToggle) {
                return "file:/"+exePath+"/tempJob.svg";
            }
            return "file:/"+exePath+"/tempJob2.svg";

//            return "file:/"+exePath+"/tempJob.svg";
        }

        return QString::fromStdString("");
}

int JobModel::ImportSlcInfo(char *SlcFileName, __Job3D *jobinfo)
{
    numboundries = 0;
        numslices = 0;
        try{
            jobinfo->true_proc = true;

            float x;
            float y;

            int headersize = 0;
            int len = 0;
            float readfloat;



            infile = fopen (SlcFileName, "rb");
            if(!infile){
                qDebug() << "JobModel : ImportSlcInfo : fopen : slc file can not apen";
                uiMessages->enqueue("file can not open");
                SetFalseFile();
                numslices = 0;
                return numslices;
            }
            len = fread(headertext,1, MAXHEADERSIZE, infile);
            fclose(infile);
            if( len <= 0){
                qDebug() << "JobModel : ImportSlcInfo : fread : slc file can not apen";
                uiMessages->enqueue("file can not open");
                SetFalseFile();
                numslices = 0;
                return numslices;
            }

            char* token = strtok(headertext, " ");
            if(!token){
                qDebug() << "JobModel : ImportSlcInfo : strtok : slc file is not correct";
                uiMessages->enqueue("file sector error");
                SetFalseFile();
                numslices = 0;
                return numslices;
            }
    //        qDebug() << "JobModel : ImportSlcInfo : token 0 : " << token;
            for (int i=0;i<20;i++)
            {
                token = strtok(NULL, " ");
    //            qDebug() << "JobModel : ImportSlcInfo : token 1 : " << token;
                if(!token){
                    qDebug() << "JobModel : ImportSlcInfo : strtok : slc file is not correct";
                    uiMessages->enqueue("file sector error");
                    SetFalseFile();
                    numslices = 0;
                    return numslices;
                }
                if (strcmp(token,"INCH")==0)
                {
                    scalefactor = 25.4f;
                }
                else if (strcmp(token,"-EXTENTS")==0)
                {
                    token = strtok(NULL, " ");
                    if(!token){
                        qDebug() << "JobModel : ImportSlcInfo : fslc file is not correct";
                        uiMessages->enqueue("file sector error");
                        SetFalseFile();
                        numslices = 0;
                        return numslices;
                    }
                    sprintf(XBound,"%s",token);
                    qDebug() << "XBound = " << XBound;


                    token = strtok(NULL, " ");
                    if(!token){
                        qDebug() << "JobModel : ImportSlcInfo : strtok  : slc file is not correct";
                        uiMessages->enqueue("file sector error");
                        SetFalseFile();
                        numslices = 0;
                        return numslices;
                    }
                    sprintf(YBound,"%s",token);
                    qDebug() << "YBound = " << YBound;

                    token = strtok(NULL, " ");
                    if(!token){
                        qDebug() << "JobModel : ImportSlcInfo : strtok  : slc file is not correct";
                        uiMessages->enqueue("file sector error");
                        SetFalseFile();
                        numslices = 0;
                        return numslices;
                    }
                    sprintf(ZBound,"%s",token);
                    qDebug() << "ZBound = " << ZBound;

                    token = strtok(XBound, ",");
                    if(!token){
                        qDebug() << "JobModel : ImportSlcInfo: strtok : slc file is not correct";
                        uiMessages->enqueue("file sector error");
                        SetFalseFile();
                        numslices = 0;
                        return numslices;
                    }
                    minx = atof(token);
                    qDebug() << "minx = " << minx;

                    token = strtok(NULL, ",");
                    if(!token){
                        qDebug() << "JobModel : ImportSlcInfo : strtok  : slc file is not correct";
                        uiMessages->enqueue("file sector error");
                        SetFalseFile();
                        numslices = 0;
                        return numslices;
                    }
                    maxx = atof(token);
                    qDebug() << "maxx = " << maxx;


                    token = strtok(YBound, ",");
                    if(!token){
                        qDebug() << "JobModel : ImportSlcInfo : strtok  : slc file is not correct";
                        uiMessages->enqueue("file sector error");
                        SetFalseFile();
                        numslices = 0;
                        return numslices;
                    }
                    miny = atof(token);
                    qDebug() << "miny = " << miny;

                    token = strtok(NULL, ",");
                    if(!token){
                        qDebug() << "JobModel : ImportSlcInfo : strtok : slc file is not correct";
                        uiMessages->enqueue("file sector error");
                        SetFalseFile();
                        numslices = 0;
                        return numslices;
                    }
                    maxy = atof(token);
                    qDebug() << "maxy = " << maxy;

                    token = strtok(ZBound, ",");
                    if(!token){
                        qDebug() << "JobModel : ImportSlcInfo : strtok : slc file is not correct";
                        uiMessages->enqueue("file sector error");
                        SetFalseFile();
                        numslices = 0;
                        return numslices;
                    }
                    minz = atof(token);
                    qDebug() << "minz = " << minz;

                    token = strtok(NULL, ",");
                    if(!token){
                        qDebug() << "JobModel : ImportSlcInfo : strtok : slc file is not correct";
                        uiMessages->enqueue("file sector error");
                        SetFalseFile();
                        numslices = 0;
                        return numslices;
                    }
                    maxz = atof(token);
                    qDebug() << "maxz = " << maxz;
                    break;
                }
            }
            //printf("%f - %f \r\n",minx,maxx);  printf("%f - %f \r\n",miny,maxy);  printf("%f - %f \r\n",minz,maxz);

            infile = fopen (SlcFileName, "rb");
            if(!infile){
                qDebug() << "JobModel : ImportSlcInfo : slc file is not correct";
                uiMessages->enqueue("file sector error");
                numslices = 0;
                SetFalseFile();
                return numslices;
            }
            delete jobinfo->points;
            jobinfo->points = new  __Points[MAXPOINTS];

           bool file = false;
            while (headersize <= MAXHEADERSIZE)
           {
                len = fread (inbuffer,1,1,infile);
                if(len < 1){
                    qDebug() << "JobModel : ImportSlcInfo : slc file is not correct";
                    uiMessages->enqueue("file sector error");
                    numslices = 0;
                    SetFalseFile();
                    return numslices;
                }
                headersize++;

                if (inbuffer[0] == 0x0d)
                {
                    len = fread (inbuffer,1,1,infile);
                    if(len < 1){
                        qDebug() << "JobModel : ImportSlcInfo : slc file is not correct";
                        uiMessages->enqueue("file sector error");
                        numslices = 0;
                        SetFalseFile();
                        return numslices;
                    }
                    headersize++;

                    if (inbuffer[0] == 0x0a)
                    {
                        len = fread (inbuffer,1,1,infile);
                        if(len < 1){
                            qDebug() << "JobModel : ImportSlcInfo : slc file is not correct";
                            uiMessages->enqueue("file sector error");
                            numslices = 0;
                            SetFalseFile();
                            return numslices;
                        }
                        headersize++;

                        if (inbuffer[0] == 0x1a)
                        {
                            file = true;
                            break;
                        }
                    }
                }
           }
            if(!file){
                qDebug() << "JobModel : ImportSlcInfo : slc file is not correct : header size";
                uiMessages->enqueue("file sector error");
                numslices = 0;
                SetFalseFile();
                return numslices;
            }

           qDebug() << "after while headersize = " << headersize;
           if(headersize <= 0 ){
               qDebug() << "JobModel : ImportSlcInfo : slc file is not correct";
               uiMessages->enqueue("file sector error");
               numslices = 0;
               SetFalseFile();
               return numslices;
           }


           len = fread (inbuffer,1,256,infile);    //skip 256 bytes
           qDebug() << "3D reserved = " << len;
           if(len < 256){
               qDebug() << "JobModel : ImportSlcInfo : slc file is not correct";
               uiMessages->enqueue("file sector error");
               numslices = 0;
               SetFalseFile();
               return numslices;
           }


           len = fread (inbuffer,1,1,infile);
           if(len < 1){
               qDebug() << "JobModel : ImportSlcInfo : slc file is not correct : tableentries";
               uiMessages->enqueue("file sector error");
               numslices = 0;
               SetFalseFile();
               return numslices;
           }
           int tableentries = inbuffer[0];
           qDebug() << "tableentries = " << tableentries;

            for (int t = 0; t < tableentries; t++)
            {
                len = fread (inbuffer,1,4,infile);
                if(len < 4){
                    qDebug() << "JobModel : ImportSlcInfo : slc file is not correct : Minimum Z Level";
                    uiMessages->enqueue("file sector error");
                    numslices = 0;
                    SetFalseFile();
                    return numslices;
                }
                memcpy(&readfloat,inbuffer,4);
                qDebug() << "Minimum Z Level = " << readfloat;

                len = fread (inbuffer,1,4,infile);
                if(len < 4){
                    qDebug() << "JobModel : ImportSlcInfo : slc file is not correct : Layer Thickness";
                    uiMessages->enqueue("file sector error");
                    numslices = 0;
                    SetFalseFile();
                    return numslices;
                }
                memcpy(&readfloat,inbuffer,4);
                qDebug() << "Layer Thickness = " << readfloat;

                len = fread (inbuffer,1,4,infile);
                if(len < 4){
                    qDebug() << "JobModel : ImportSlcInfo : slc file is not correct";
                    uiMessages->enqueue("file sector error");
                    numslices = 0;
                    SetFalseFile();
                    return numslices;
                }
                memcpy(&readfloat,inbuffer,4);
                qDebug() << "Line Width Compensation = " << readfloat;

                len = fread (inbuffer,1,4,infile);
                if(len < 4){
                    qDebug() << "JobModel : ImportSlcInfo : slc file is not correct : Reserved";
                    uiMessages->enqueue("file sector error");
                    numslices = 0;
                    SetFalseFile();
                    return numslices;
                }
                memcpy(&readfloat,inbuffer,4);
                qDebug() << "Reserved = " << readfloat;
            }
            minb.X=minx;  minb.Y=miny;
            maxb.X=maxx;  maxb.Y=maxy;

           int t_index = 0;

            bool boundsdetermined = 0;
            while (numboundries != 0xffffffff){
                len = fread (inbuffer,1,4,infile);
                if(len < 4){
                    qDebug() << "JobModel : ImportSlcInfo : slc file is not correct : minzlevel";
                    uiMessages->enqueue("file sector error");
                    numslices = 0;
                    SetFalseFile();
                    return numslices;
                }
                memcpy(&minzlevel,inbuffer,4);
    //            qDebug() << "minzlevel = " << minzlevel;

                len = fread (inbuffer,1,4,infile);
                if(len < 4){
                    qDebug() << "JobModel : ImportSlcInfo : slc file is not correct : numboundries";
                    uiMessages->enqueue("file sector error");
                    numslices = 0;
                    SetFalseFile();
                    return numslices;
                }
                memcpy(&numboundries,inbuffer,4);
    //            qDebug() << "numboundries = " << numboundries;

                if (numboundries == 0xffffffff)
                {
                    break;
                }
                numslices++;
//                qDebug() << "numslices = " << numslices;
                for (int b = 0; b < numboundries; b++)
                {
                    len = fread (inbuffer,1,4,infile);
                    if(len < 4){
                        qDebug() << "JobModel : ImportSlcInfo : slc file is not correct : numvertices";
                        uiMessages->enqueue("file sector error");
                        numslices = 0;
                        SetFalseFile();
                        return numslices;
                    }
                    memcpy(&numvertices,inbuffer,4);
    //                qDebug() << "numvertices = " << numvertices;

                    len = fread (inbuffer,1,4,infile);
                    if(len < 4){
                        qDebug() << "JobModel : ImportSlcInfo : slc file is not correct : numgaps";
                        uiMessages->enqueue("file sector error");
                        numslices = 0;
                        SetFalseFile();
                        return numslices;
                    }
                    memcpy(&numgaps,inbuffer,4);
    //                qDebug() << "numgaps = " << numgaps;


                    for (int v = 0; v < numvertices; v++)
                    {
                        len = fread (inbuffer,1,4,infile);
                        if(len < 4){
                            qDebug() << "JobModel : ImportSlcInfo : slc file is not correct : &x";
                            uiMessages->enqueue("file sector error");
                            numslices = 0;
                            SetFalseFile();
                            return numslices;
                        }
                        memcpy(&x,inbuffer,4);

                        len = fread (inbuffer,1,4,infile);
                        if(len < 4){
                            qDebug() << "JobModel : ImportSlcInfo : slc file is not correct : &y";
                            uiMessages->enqueue("file sector error");
                            numslices = 0;
                            SetFalseFile();
                            return numslices;
                        }
                        memcpy(&y,inbuffer,4);


                        x *= scalefactor;
                        y *= scalefactor;

                        jobinfo->points[t_index].fX = x;
                        jobinfo->points[t_index].fY = y;
                        jobinfo->points[t_index].VertNum = v;
                        jobinfo->points[t_index].Slice = numslices;
                        t_index++;

                        if (x > maxb.X)
                            maxb.X = x;
                        if (y > maxb.Y)
                            maxb.Y = y;
                        if (x < minb.X)
                            minb.X = x;
                        if (y < minb.Y)
                            minb.Y = y;
                        boundsdetermined = true;
                    }
                }

            }
            qDebug() << "numslices = " << numslices;
    //        qDebug() << "after while";
            //printf("\r\n numslices: %d \r\n",numslices);
            fclose(infile);
            jobinfo->fMaxX = maxb.X;
            jobinfo->fMaxY = maxb.Y;
            jobinfo->iNumSlices = numslices;
            jobinfo->iTotalVerts = t_index;
            return numslices;
        }
        catch(...){
            qDebug() << "JobModel : ImportSlcInfo : file sector error";
            uiMessages->enqueue("file sector error");
            SetFalseFile();
            return numslices;
        }
}

void JobModel::SetFalseFile()
{
    tempFileInfo.true_proc = false;
    numslices = 0;
    tempFileInfo.iNumSlices = numslices;
}

int JobModel::ExportPatternToMem(int index, int ImageCX, int ImageCY, float fPixelSize, unsigned int BkgColor, char *OutBuffer)
{
    int aa = 0;
    int jj = 0;
    int size = 0;
    int zz = 0;

    zz = sprintf(OutBuffer+size, "<svg width='%d' height='%d'>\r\n", ImageCX, ImageCY);
    size += zz;
    zz = sprintf(OutBuffer+size, "<rect x='0' y='0' width='%d' height='%d' style='fill:#%x;stroke-width:0;' />\r\n", ImageCX, ImageCY, BkgColor);
    size += zz;


    int xx = ImageCX/30;
    int yy = ImageCY/30;

    int tmpv = 0;
    if (index == 1)
    {
        for (int i=0;i<31;i++)
        {
            tmpv = i*xx;
            if (i==30) tmpv-=1;
            zz = sprintf(OutBuffer+size, "<rect x='%d' y='%d' width='%d' height='%d' style='fill:white;stroke-width:0;' />\r\n", tmpv,0,1,ImageCY);
            size += zz;
        }
        for (int i=0;i<31;i++)
        {
            tmpv = i*yy;
            if (i==30) tmpv-=1;
            zz = sprintf(OutBuffer+size, "<rect x='%d' y='%d' width='%d' height='%d' style='fill:white;stroke-width:0;' />\r\n", 0,tmpv,ImageCX,1);
            size += zz;
        }
    }
    else if (index == 2)
    {
        zz = sprintf(OutBuffer+size, "<rect x='%d' y='%d' width='%d' height='%d' style='fill:white;stroke-width:0;' />\r\n", 200,200,600,500);
        size += zz;
    }
    else if (index == 3)
    {
        zz = sprintf(OutBuffer+size, "<circle cx='%d' cy='%d' r='%d' style='fill:white;stroke-width:0;' />\r\n", 200,200,100);
        size += zz;
    }
    else if (index == 4)
    {
        zz = sprintf(OutBuffer+size, "<circle cx='%d' cy='%d' r='%d' fill'white' />\r\n", ImageCX/2,ImageCY/2,ImageCY/2);
        size += zz;
    }
    zz = sprintf(OutBuffer + size, "</svg>\r\n");
    size += zz;
    return size;
}

int JobModel::ExportFrameToSVG(__Job3D *jobinfo, int iSlice, int ImageCX, int ImageCY, float fPixelSize, const char *OutFileName)
{
    int aa = 0;
    int jj = 0;
    while (aa < MAXPOINTS)
    {
        if (jobinfo->points[aa].Slice == iSlice)
            break;
        aa++;
    }

    outfile = fopen(OutFileName, "w+");
    fprintf(outfile, "<svg xmlns='http://www.w3.org/2000/svg' version='1.0' width='%d' height='%d'>\r\n", ImageCX, ImageCY);
    fprintf(outfile, "<rect x='0' y='0' width='%d' height='%d' style='fill:black;stroke:blue;stroke-width:0;' />\r\n", ImageCX, ImageCY);
    fprintf(outfile, "<path d='");

    jj = 0;
    while (jobinfo->points[aa].Slice == iSlice)
    {
        if (jobinfo->points[aa].VertNum == 0)
            fprintf(outfile, "M%.3f %.3f ", (jobinfo->points[aa].fX*(1.0 / fPixelSize)), (jobinfo->points[aa].fY*(1.0 / fPixelSize)));
        else
            fprintf(outfile, "L%.3f %.3f ", (jobinfo->points[aa].fX*(1.0 / fPixelSize)), (jobinfo->points[aa].fY*(1.0 / fPixelSize)));
        aa++;
    }

    fprintf(outfile, "Z' fill='white' />\r\n");
    fprintf(outfile, "</svg>\r\n");
    fclose(outfile);
    return 0;
}

int JobModel::ExportFrameToMem(__Job3D *jobinfo, int iSlice, int ImageCX, int ImageCY, float fPixelSize, unsigned int BkgColor, char *OutBuffer, float X_Shift, float Y_Shift)
{
    int aa = 0;
    int jj = 0;
    int size = 0;
    int zz = 0;
    while (aa < MAXPOINTS)
    {
        if (jobinfo->points[aa].Slice == iSlice)
            break;
        aa++;
    }

    zz = sprintf(OutBuffer+size, "<svg width='%d' height='%d'>\r\n", ImageCX, ImageCY);
    size += zz;
    zz = sprintf(OutBuffer+size, "<rect x='0' y='0' width='%d' height='%d' style='fill:#%x;stroke-width:0;' />\r\n", ImageCX, ImageCY, BkgColor);
    size += zz;
    zz = sprintf(OutBuffer+size, "<path d='");
    size += zz;


    jj = 0;
    while (jobinfo->points[aa].Slice == iSlice)
    {
        if (jobinfo->points[aa].VertNum == 0)
            zz = sprintf(OutBuffer + size, "M%.3f %.3f ", (jobinfo->points[aa].fX*(1.0 / fPixelSize))+X_Shift, (jobinfo->points[aa].fY*(1.0 / fPixelSize))+Y_Shift);
        else
            zz = sprintf(OutBuffer + size, "L%.3f %.3f ", (jobinfo->points[aa].fX*(1.0 / fPixelSize))+X_Shift, (jobinfo->points[aa].fY*(1.0 / fPixelSize))+Y_Shift);
        size += zz;
        aa++;
    }


    zz = sprintf(OutBuffer + size, "Z' fill='white' />\r\n");
    size += zz;


    zz = sprintf(OutBuffer + size, "</svg>\r\n");
    size += zz;
    return size;
}

void JobModel::ExportSlcFileToSVG(char *SlcFileName, char *OutFileName, float fPixelSize, int img_cx, int img_cy)
{
    float x;
    float y;


    int headersize = 0;
    int len = 0;
    float readfloat;

    int nSlices = 0;

    char svgName[256];

    numboundries = 0;


    infile = fopen (SlcFileName, "rb");


   while (headersize <= MAXHEADERSIZE)
   {
        len = fread (inbuffer,1,1,infile);
        headersize++;
        if (inbuffer[0] == 0x0d)
        {
            len = fread (inbuffer,1,1,infile);
            headersize++;
            if (inbuffer[0] == 0x0a)
            {
                len = fread (inbuffer,1,1,infile);
                headersize++;
                if (inbuffer[0] == 0x1a)
                {
                    break;
                }
            }
        }
   }
   len = fread (inbuffer,1,256,infile);    //skip 256 bytes


   len = fread (inbuffer,1,1,infile);
   int tableentries = inbuffer[0];

    for (int t = 0; t < tableentries; t++)
    {
        len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);
        len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);
        len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);
        len = fread (inbuffer,1,4,infile);  memcpy(&readfloat,inbuffer,4);
    }

   minb.X=minx;  minb.Y=miny;
   maxb.X=maxx;  maxb.Y=maxy;

    bool boundsdetermined = 0;
    while (numboundries != 0xffffffff)
    {
        len = fread (inbuffer,1,4,infile);  memcpy(&minzlevel,inbuffer,4);
        len = fread (inbuffer,1,4,infile);  memcpy(&numboundries,inbuffer,4);

        if (numboundries == 0xffffffff)
        {
            break;
        }
        nSlices++;

        sprintf(svgName, "%s%d.svg", OutFileName,nSlices);
        outfile = fopen (svgName, "w+");

        fprintf(outfile, "<svg xmlns='http://www.w3.org/2000/svg' version='1.0' width='%d' height='%d'>\r\n", img_cx,img_cy);
        fprintf(outfile, "<rect x='0' y='0' width='%d' height='%d' style='fill:black;stroke:blue;stroke-width:0;' />\r\n",img_cx,img_cy);
        fprintf(outfile, "<path d='");
        for (int b = 0; b < numboundries; b++)
        {
            len = fread (inbuffer,1,4,infile);  memcpy(&numvertices,inbuffer,4);
            len = fread (inbuffer,1,4,infile);  memcpy(&numgaps,inbuffer,4);

            for (int v = 0; v < numvertices; v++)
            {
                len = fread (inbuffer,1,4,infile);  memcpy(&x,inbuffer,4);
                len = fread (inbuffer,1,4,infile);  memcpy(&y,inbuffer,4);

                x *= scalefactor;
                y *= scalefactor;

                if (v==0)
                    fprintf(outfile, "M%.3f %.3f ",(x*(1.0/fPixelSize)),(y*(1.0/fPixelSize)));
                else
                    fprintf(outfile, "L%.3f %.3f ",(x*(1.0/fPixelSize)),(y*(1.0/fPixelSize)));

                if (x > maxb.X)
                    maxb.X = x;
                if (y > maxb.Y)
                    maxb.Y = y;
                if (x < minb.X)
                    minb.X = x;
                if (y < minb.Y)
                    minb.Y = y;
                boundsdetermined = true;
            }
        }
        fprintf(outfile, "Z' fill='white' />\r\n");
        fprintf(outfile, "</svg>\r\n");
        fclose(outfile);
    }

    fclose(infile);
}

void JobModel::ExportJobFile(__Job3D *jobinfo, char *OutFileName)
{
    FILE * outfile;
    outfile = fopen (OutFileName, "wb");

    fwrite (jobinfo,1,sizeof(jobinfo),outfile);
    fwrite (jobinfo->points,1,jobinfo->iTotalVerts*sizeof(__Points),outfile);

    fclose(outfile);
}

void JobModel::OpenJobFile(char *JobFileName, __Job3D *jobinfo)
{
    FILE * file;
    file = fopen (JobFileName, "rb");
    fread (jobinfo,1,sizeof(jobinfo),file);
    fread (jobinfo->points,1,jobinfo->iTotalVerts*sizeof(__Points),outfile);
    fclose(file);
}

void JobModel::setUIMessages(UIMessages *uiMsg)
{
    uiMessages = uiMsg;
}

void JobModel::sendFileDone()
{
    qDebug()<<"JobModel::sendFileDone";
    uploding = false;

    if(tempFileInfo.true_proc){

        beginResetModel();
        mList->job3DItems.append(tempFileInfo);
        endResetModel();
    }
    else
        emit newJobName(QString::fromStdString(tempFileInfo.name));

}

void JobModel::sendFileError(QString message)
{
    qDebug()<<"JobModel::sendFileError";
    uiMessages->enqueue(message);
}

void JobModel::GetPrecentage(int precentage)
{
    emit sendPrecentageToQml(precentage);
}

void JobModel::onSendTrueFile(bool ckeck)
{
    tempFileInfo.true_proc = ckeck;
    if(!ckeck){
        tempFileInfo.name = tempFileInfo.name + "_err";

    }
}
