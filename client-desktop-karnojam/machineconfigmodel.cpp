#include "machineconfigmodel.h"
#include "machineconfiglist.h"

MachineConfigModel::MachineConfigModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
    socket = new QTcpSocket();
     mList = new MachineConfigList();
     serverCmdMesg = new network_messages::NetServerCommands();
     serverResMesg = new network_messages::NetClientRes();
     machineCmd = new network_messages::MachineConfig();

}

int MachineConfigModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
            return 0;

    return mList->items().size();
}

QVariant MachineConfigModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
          return QVariant();

      const MachineConfig item = mList->items().at(index.row());
      switch (role) {
       case ModelCode:
          return QVariant( item.ModelCode);
       case gProjectWidth:
          return QVariant(item.gProjectWidth);
      case gProjectHeight:
         return QVariant(item.gProjectHeight);
      case MachineNo:
         return QVariant(QString::fromStdString(item.MachineNo) );
      case Version:
         return QVariant(item.Version);
      case SubVersion:
         return QVariant(item.SubVersion);
      case NeedLicense:
         return QVariant(item.NeedLicense);
      case HasDoor:
         return QVariant(item.HasDoor);
      case HasErm:
         return QVariant(item.HasErm);
      case BUpTDownConfig:
         return QVariant(item.BUpTDownConfig);
      case PrinterUnit:
          qDebug()<<"PrinterUnit:::::"<<item.PrinterUnit;
         return QVariant(item.PrinterUnit);
      case ZUpperLimit:
         return QVariant(item.ZUpperLimit);
      case ProjectorProtocol:
         return QVariant(item.ProjectorProtocol);
      case NoOfMaskPoints:
         return QVariant(item.NoOfMaskPoints);
      case MaxIntensity:
         return QVariant(item.MaxIntensity);
      case MinIntensity:
         return QVariant(item.MinIntensity);
      case MaxIntensitySensor:
         return QVariant(item.MaxIntensitySensor);
      case MinIntensitySensor:
         return QVariant(item.MinIntensitySensor);
      case id:
         return QVariant(item.id);
      case HasPlunger:
         return QVariant(item.HasPlunger);
      case TDownZHomePos:
          qDebug()<<"TDownZHomePos::::::::::::::::::::"<<item.TDownZHomePos;
         return QVariant(item.TDownZHomePos);
      case vacuumTimer:
         return QVariant(item.vacuumTimer);
      case SensorSetPointVacuum:
         return QVariant(item.SensorSetPointVacuum);
      case SensorSetPoint:
         return QVariant(item.SensorSetPoint);
      case SensorThreshold:
         return QVariant(item.SensorThreshold);
      case XShift:
         return QVariant(item.XShift);
      case YShift:
         return QVariant(item.YShift);
      }

      return QVariant();
}

bool MachineConfigModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
           return false;

       if(index.row() >= mList->items().size()) {
//           cout<< "setData index.row():"<< index.row()<<", role:"<< role << endl;
           return false;
       }
       MachineConfig item = mList->items().at(index.row());

       switch (role) {
        case ModelCode:
           item.ModelCode = static_cast<unsigned int>(value.toUInt());
           break;
        case gProjectWidth:
           cout<<index.row()<<" setData rainOff role "<<value.toInt()<<endl;
          item.gProjectWidth = static_cast<unsigned int>(value.toInt());
          break;
        case gProjectHeight:
           cout<<index.row()<<" setData rainOn role "<<value.toInt()<<endl;
          item.gProjectHeight = static_cast<unsigned int>(value.toInt());
          break;
        case MachineNo:
          item.MachineNo = value.toString().toStdString();
          break;
       case Version:
         item.Version = static_cast<unsigned int>(value.toInt());
         break;
       case SubVersion:
         item.SubVersion = static_cast<unsigned int>(value.toInt());
         break;
       case NeedLicense:
//         item.NeedLicense = static_cast<bool>(value.toBool());
       case HasDoor:
//         item.HasDoor = value.toBool();
       case HasErm:
//         item.HasErm = value.toBool();
       case BUpTDownConfig:
         item.BUpTDownConfig = value.toBool();
         break;
       case PrinterUnit:
         item.PrinterUnit = static_cast<float>(value.toFloat());
         break;
       case ZUpperLimit:
         item.ZUpperLimit = static_cast<unsigned int>(value.toInt());
         break;
       case ProjectorProtocol:
         item.ProjectorProtocol = static_cast<unsigned int>(value.toInt());
         break;
       case NoOfMaskPoints:
         item.NoOfMaskPoints = static_cast<unsigned int>(value.toInt());
         break;
       case MaxIntensity:
         item.MaxIntensity = static_cast<unsigned int>(value.toInt());
         break;
       case MinIntensity:
         item.MinIntensity = static_cast<unsigned int>(value.toInt());
         break;
       case MaxIntensitySensor:
         item.MaxIntensitySensor = static_cast<unsigned int>(value.toInt());
         break;
       case MinIntensitySensor:
         item.MinIntensitySensor = static_cast<unsigned int>(value.toInt());
         break;
       case id:
         item.id = static_cast<uint16_t>(value.toInt());
         break;

       case HasPlunger:
//         item.PrinterUnit = value.toFloat();
//         break;
       case TDownZHomePos:
         item.TDownZHomePos = static_cast<unsigned int>(value.toInt());
         qDebug()<<"TDownZHomePos settttt::::::::::::::::::::"<<item.TDownZHomePos;
         break;
       case vacuumTimer:
         item.vacuumTimer = value.toFloat();
         break;
       case SensorSetPointVacuum:
         item.SensorSetPointVacuum = value.toFloat();
         break;
       case SensorSetPoint:
         item.SensorSetPoint = value.toFloat();
         break;
       case SensorThreshold:
         item.SensorThreshold = value.toFloat();
         break;
       case XShift:
         item.XShift = value.toFloat();
         break;
       case YShift:
         item.YShift = value.toFloat();
         break;

       default:
           break;
       }

       if(mList->setConfigItem(index.row(), item)) {
   //        cout<< "emit data changed:"<< index.row()<< ", role:"<<role<<endl;
           emit dataChanged(index, index, QVector<int>() << role);
           return true;
       }

       return false;
}

QHash<int, QByteArray> MachineConfigModel::roleNames() const
{
    QHash<int, QByteArray> names;
        names[ModelCode] = "ModelCode";
        names[gProjectWidth] = "gProjectWidth" ;
        names[gProjectHeight] = "gProjectHeight" ;
        names[MachineNo] = "MachineNo" ;
        names[Version] = "Version" ;
        names[SubVersion] = "SubVersion" ;
        names[NeedLicense] = "NeedLicense" ;
        names[HasDoor] = "HasDoor";
        names[HasErm] = "HasErm" ;
        names[BUpTDownConfig] = "BUpTDownConfig" ;
        names[PrinterUnit] = "PrinterUnit" ;
        names[ZUpperLimit] = "ZUpperLimit" ;
        names[ProjectorProtocol] = "ProjectorProtocol" ;
        names[NoOfMaskPoints] = "NoOfMaskPoints" ;
        names[MaxIntensity] = "MaxIntensity" ;
        names[MinIntensity] = "MinIntensity" ;
        names[MaxIntensitySensor] = "MaxIntensitySensor" ;
        names[MinIntensitySensor] = "MinIntensitySensor" ;
        names[id] = "id" ;

        names[HasPlunger] = "HasPlunger";
        names[TDownZHomePos] = "TDownZHomePos";
        names[vacuumTimer] = "vacuumTimer";
        names[SensorSetPointVacuum] = "SensorSetPointVacuum";
        names[SensorSetPoint] = "SensorSetPoint";
        names[SensorThreshold] = "SensorThreshold";
        names[XShift] = "XShift";
        names[YShift] = "YShift";
        return names;
}

Qt::ItemFlags MachineConfigModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
            return Qt::NoItemFlags;

        return Qt::ItemIsEditable;
}

MachineConfigList *MachineConfigModel::list() const
{
    return mList;
}

void MachineConfigModel::setList(MachineConfigList *list)
{
    beginResetModel();
       if(mList)
           mList->disconnect(this);

       mList = list;

       endResetModel();
}

void MachineConfigModel::addElement(MachineConfig item)
{
    beginResetModel(); 
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Config);
    machineCmd->set_packetcode(network_messages::MachineConfig::Add);
    machineCmd->set_haserm(item.HasErm);
    machineCmd->set_hasdoor(item.HasDoor);
    machineCmd->set_version(item.Version);
    machineCmd->set_machineno(item.MachineNo); // item.MachineNo
    machineCmd->set_modelcode(item.ModelCode);
    machineCmd->set_subversion(item.SubVersion);
    machineCmd->set_needlicense(item.NeedLicense);
    machineCmd->set_printerunit(item.PrinterUnit);
    machineCmd->set_zupperlimit(item.ZUpperLimit);
    machineCmd->set_maxintensity(item.MaxIntensity);
    machineCmd->set_minintensity(item.MinIntensity);

    machineCmd->set_maxintensitysensor(item.MaxIntensitySensor);
    machineCmd->set_minintensitysensor(item.MinIntensitySensor);

    machineCmd->set_gprojectwidth(item.gProjectWidth);
    machineCmd->set_buptdownconfig(item.BUpTDownConfig);
    machineCmd->set_noofmaskpoints(item.NoOfMaskPoints);
    machineCmd->set_gprojectheight(item.gProjectHeight);
    machineCmd->set_projectorprotocol(item.ProjectorProtocol);

    machineCmd->set_hasplunger(item.HasPlunger);
    machineCmd->set_tdownzhomepos(item.TDownZHomePos);
    machineCmd->set_vacuumtimer(item.vacuumTimer);
    machineCmd->set_sensorsetpointvacuum(item.SensorSetPointVacuum);
    machineCmd->set_sensorsetpoint(item.SensorSetPoint);
    machineCmd->set_sensorthreshold(item.SensorThreshold);
    machineCmd->set_xshift(item.XShift);
    machineCmd->set_yshift(item.YShift);

    qDebug() << "vacuumTimer:"<<machineCmd->vacuumtimer();
    qDebug() << "item.SensorThreshold 2:"<<machineCmd->sensorthreshold();


    serverCmdMesg->set_allocated_machineconf(machineCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);
    if(connectToServer() < 0) {
       qDebug() << "MachineConfModel sendReq socket does not connect ";
    } else {
        socket->write(mBuf, size);
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(3000);
        QByteArray bRes = socket->readAll();
        serverResMesg->Clear();
        serverResMesg->ParseFromArray(bRes.data(), bRes.size());
        if(serverResMesg->packetcode() == network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Done) {
            mList->configItems.append(item);
        } else {
            qDebug()<< "MachineConfigModel::addElement error"<< QString::fromStdString(serverResMesg->errormesg()) ;
        }
    }
    disconnetFromServer();
    delete [] mBuf;
    endResetModel();
}

int MachineConfigModel::size()
{
   return mList->items().size();
}

void MachineConfigModel::makeNewConfig(int ModelCode, int gProjectWidth, int gProjectHeight, QString MachineNo, int Version,
                                       int SubVersion, bool NeedLicense, bool HasDoor, bool HasErm, bool BUpTDownConfig,
                                       float PrinterUnit, int ZUpperLimit, int ProjectorProtocol, int NoOfMaskPoints, int MaxIntensity,
                                       int MinIntensity,int MaxIntensitySensor,int MinIntensitySensor,bool HasPlunger,
                                       int TDownZHomePos, float vacuumTimer, float SensorSetPointVacuum,
                                       float SensorSetPoint, float SensorThreshold, float XShift, float YShift)
{
   MachineConfig item;
   item.ModelCode = ModelCode;
   item.gProjectWidth = gProjectWidth;
   item.gProjectHeight = gProjectHeight;
   item.MachineNo =  MachineNo.toStdString();
   item.Version = Version;
   item.SubVersion = SubVersion;
   item.NeedLicense = NeedLicense;
   item.HasDoor = HasDoor;
   item.HasErm = HasErm;
   item.BUpTDownConfig = BUpTDownConfig;
   item.PrinterUnit = PrinterUnit;
   item.ZUpperLimit = ZUpperLimit;
   item.ProjectorProtocol = ProjectorProtocol;
   item.NoOfMaskPoints = NoOfMaskPoints;
   item.MaxIntensity = MaxIntensity;
   item.MinIntensity = MinIntensity;

   item.MaxIntensitySensor = MaxIntensitySensor;
   item.MinIntensitySensor = MinIntensitySensor;

   item.HasPlunger = HasPlunger;
   item.TDownZHomePos = TDownZHomePos;
   item.vacuumTimer = vacuumTimer;
   item.SensorSetPointVacuum = SensorSetPointVacuum;
   item.SensorSetPoint = SensorSetPoint;
   item.SensorThreshold = SensorThreshold;
   item.XShift = XShift;
   item.YShift = YShift;

   addElement(item);
}

void MachineConfigModel::removeConfig(int index)
{
    if(index > size()) {qDebug() << "MachineConfigModel::removeConfig wrong index:"<<index; return;}
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Config);
    machineCmd->set_packetcode(network_messages::MachineConfig::Delete);
    machineCmd->set_rowid(mList->configItems[index-1].id);
    serverCmdMesg->set_allocated_machineconf(machineCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);

    if(connectToServer() < 0) {
       qDebug() << "MachineConfModel removeConfig socket does not connect ";
    } else {
        socket->write(mBuf, size);
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(2000);
        QByteArray temp = socket->readAll();
        serverResMesg->ParseFromArray(temp.data(), temp.size());
        if(serverResMesg->packetcode() == network_messages::NetClientRes::Done) {
            beginResetModel();
            mList->configItems.remove(index-1);
            endResetModel();
        } else {
           qDebug() << "MachineConfModel removeConfig can not delete"<< QString::fromStdString(serverResMesg->errormesg()) ;
        }
    }
    disconnetFromServer();
    delete [] mBuf;

}

void MachineConfigModel::setConfig(int index,int ModelCode, int gProjectWidth, int gProjectHeight, QString MachineNo,
                                   int Version, int SubVersion, bool NeedLicense, bool HasDoor, bool HasErm,
                                   bool BUpTDownConfig, float PrinterUnit, int ZUpperLimit, int ProjectorProtocol,
                                   int NoOfMaskPoints, int MaxIntensity, int MinIntensity, int MaxIntensitySensor, int MinIntensitySensor, bool HasPlunger, int TDownZHomePos,
                                   float vacuumTimer, float SensorSetPointVacuum, float SensorSetPoint, float SensorThreshold,
                                   float XShift, float YShift)

{
    if(index > size()) {qDebug() << "MachineConfigModel::setConfig wrong index:"<<index; return;}
    MachineConfig item;
    item.id = mList->configItems[index-1].id;
    item.ModelCode = static_cast<unsigned int>(ModelCode);
    item.gProjectWidth = static_cast<unsigned int>(gProjectWidth);
    item.gProjectHeight = static_cast<unsigned int>(gProjectHeight);
    item.MachineNo = MachineNo.toStdString();
    item.Version = static_cast<unsigned int>(Version);
    item.SubVersion = static_cast<unsigned int>(SubVersion);
    item.NeedLicense = NeedLicense;
    item.HasDoor = HasDoor;
    item.HasErm = HasErm;
    item.BUpTDownConfig = BUpTDownConfig;
    item.PrinterUnit = static_cast<float>(PrinterUnit);
    item.ZUpperLimit = static_cast<unsigned int>(ZUpperLimit);
    item.ProjectorProtocol = static_cast<unsigned int>(ProjectorProtocol);
    item.NoOfMaskPoints = static_cast<unsigned int>(NoOfMaskPoints);
    item.MaxIntensity = static_cast<unsigned int>(MaxIntensity);
    item.MinIntensity = static_cast<unsigned int>(MinIntensity);

    item.MaxIntensitySensor = static_cast<unsigned int>(MaxIntensitySensor);
    item.MinIntensitySensor = static_cast<unsigned int>(MinIntensitySensor);

    qDebug()<< "Setting TDownZHomePos ::::::" << TDownZHomePos;

    item.HasPlunger = HasPlunger;
    item.TDownZHomePos = static_cast<unsigned int>(TDownZHomePos);
    item.vacuumTimer = static_cast<float>(vacuumTimer);
    item.SensorSetPointVacuum = static_cast<float>(SensorSetPointVacuum);
    item.SensorSetPoint = static_cast<float>(SensorSetPoint);
    item.SensorThreshold = static_cast<float>(SensorThreshold);
    item.XShift = static_cast<float>(XShift);
    item.YShift = static_cast<float>(YShift);

    clearMessages();

    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Config);
    machineCmd->set_packetcode(network_messages::MachineConfig::Edit);
    machineCmd->set_rowid(item.id);
    machineCmd->set_haserm(item.HasErm);
    machineCmd->set_hasdoor(item.HasDoor);
    machineCmd->set_version(item.Version);
    machineCmd->set_machineno(item.MachineNo); // item.MachineNo
    machineCmd->set_modelcode(item.ModelCode);
    machineCmd->set_subversion(item.SubVersion);
    machineCmd->set_needlicense(item.NeedLicense);
    machineCmd->set_printerunit(item.PrinterUnit);
    machineCmd->set_zupperlimit(item.ZUpperLimit);
    machineCmd->set_maxintensity(item.MaxIntensity);
    machineCmd->set_minintensity(item.MinIntensity);

    machineCmd->set_maxintensitysensor(item.MaxIntensitySensor);
    machineCmd->set_minintensitysensor(item.MinIntensitySensor);

    machineCmd->set_gprojectwidth(item.gProjectWidth);
    machineCmd->set_gprojectheight(item.gProjectHeight);
    machineCmd->set_buptdownconfig(item.BUpTDownConfig);
    machineCmd->set_noofmaskpoints(item.NoOfMaskPoints);
    machineCmd->set_projectorprotocol(item.ProjectorProtocol);

    machineCmd->set_hasplunger(item.HasPlunger);
    machineCmd->set_tdownzhomepos(item.TDownZHomePos);
    machineCmd->set_vacuumtimer(item.vacuumTimer);
    machineCmd->set_sensorsetpointvacuum(item.SensorSetPointVacuum);
    machineCmd->set_sensorsetpoint(item.SensorSetPoint);
    machineCmd->set_sensorthreshold(item.SensorThreshold);
    machineCmd->set_xshift(item.XShift);
    machineCmd->set_yshift(item.YShift);


    serverCmdMesg->set_allocated_machineconf(machineCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);
    if(connectToServer() < 0) {
       qDebug() << "MachineConfModel setConfig socket does not connect ";
    } else {
        socket->write(mBuf, size);
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(2000);
        QByteArray temp = socket->readAll();
        serverResMesg->ParseFromArray(temp.data(), temp.size());
        if(serverResMesg->packetcode() == network_messages::NetClientRes::Done) {
            beginResetModel();
            mList->configItems[index-1] = item;
            endResetModel();
            uiMessages->enqueue("Done");
        } else {
           qDebug() << "MachineConfModel setConfig can not delete"<< QString::fromStdString(serverResMesg->errormesg()) ;
        }
    }

    disconnetFromServer();
    delete [] mBuf;
}

void MachineConfigModel::refreshData()
{
   clearMessages();
   serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Config);
   machineCmd->set_packetcode(network_messages::MachineConfig::GetALL);
   serverCmdMesg->set_allocated_machineconf(machineCmd);
   size_t size = serverCmdMesg->ByteSizeLong();
   char *mBuf = new char[size];
   serverCmdMesg->SerializeToArray(mBuf, size);

   if(connectToServer() < 0) {
      qDebug() << "MachineConfModel sendReq socket does not connect ";
   } else {
      socket->write(mBuf, size);
      socket->waitForBytesWritten(3000);
      socket->waitForReadyRead(2000);
      QByteArray temp = socket->readAll();
      serverResMesg->ParseFromArray(temp.data(), temp.size());
      if(serverResMesg->packetcode() == network_messages::NetClientRes::Founded ) {
          beginResetModel();
          mList->configItems.clear();
          for(int i=0; i<serverResMesg->confs_size(); i++) {
              MachineConfig mConf ;
              network_messages::MachineConfig confMesg = serverResMesg->confs(i);
              mConf.id = confMesg.rowid();
              mConf.HasErm = confMesg.haserm();
              mConf.HasDoor = confMesg.hasdoor();
              mConf.Version = confMesg.version();
              mConf.MachineNo = confMesg.machineno();
              mConf.ModelCode = confMesg.modelcode();
              mConf.SubVersion = confMesg.subversion();
              mConf.NeedLicense = confMesg.needlicense();
              mConf.PrinterUnit = confMesg.printerunit();
              mConf.ZUpperLimit = confMesg.zupperlimit();
              mConf.MaxIntensity = confMesg.maxintensity();
              mConf.MinIntensity = confMesg.minintensity();

              mConf.MaxIntensitySensor = confMesg.maxintensitysensor();
              mConf.MinIntensitySensor = confMesg.minintensitysensor();

              mConf.gProjectWidth = confMesg.gprojectwidth();
              mConf.BUpTDownConfig = confMesg.buptdownconfig();
              mConf.NoOfMaskPoints = confMesg.noofmaskpoints();
              mConf.gProjectHeight = confMesg.gprojectheight();
              mConf.ProjectorProtocol = confMesg.projectorprotocol();


              mConf.HasPlunger = confMesg.hasplunger();
              mConf.TDownZHomePos = confMesg.tdownzhomepos();
              mConf.vacuumTimer = confMesg.vacuumtimer();
              mConf.SensorSetPointVacuum = confMesg.sensorsetpointvacuum();
              mConf.SensorSetPoint = confMesg.sensorsetpoint();
              mConf.SensorThreshold = confMesg.sensorthreshold();
              mConf.XShift = confMesg.xshift();
              mConf.YShift = confMesg.yshift();


              qDebug()<< "Setting TDownZHomePos ::::::" << mConf.TDownZHomePos;




              mList->addConfig(mConf);
          }
          endResetModel();
      } else if(serverResMesg->packetcode() == network_messages::NetClientRes::NotFound ) {
          beginResetModel();
          mList->configItems.clear();
          endResetModel();
      } else {
          qDebug() << "MachineConfigModel refreshData can not Recieve" ;
      }
   }
   disconnetFromServer();
   delete [] mBuf;
}

void MachineConfigModel::setMachineModel(int index)
{
    if(index > size()) {qDebug() << "MachineConfigModel::setMachineModel wrong index:"<<index; return;}
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Config);
    machineCmd->set_packetcode(network_messages::MachineConfig::SET);
    machineCmd->set_modelcode(mList->configItems[index].ModelCode);
    serverCmdMesg->set_allocated_machineconf(machineCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);

    if(connectToServer() < 0) {
       qDebug() << "MachineConfModel removeConfig socket does not connect ";
    } else {
        socket->write(mBuf, size);
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(2000);
        QByteArray temp = socket->readAll();
        serverResMesg->ParseFromArray(temp.data(), temp.size());
        if(serverResMesg->packetcode() == network_messages::NetClientRes::Done) {

        } else {
           qDebug() << "MachineConfModel setMachineModel can not set:"<< QString::fromStdString(serverResMesg->errormesg()) ;
           uiMessages->enqueue( QString::fromStdString(serverResMesg->errormesg()) );
        }
    }
    disconnetFromServer();
    delete [] mBuf;
}

void MachineConfigModel::setMachineIpPort(QString mAddress, QString mPort)
{
    MachineAddress = mAddress;
    MachinePort = mPort;
}

int MachineConfigModel::connectToServer()
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

int MachineConfigModel::disconnetFromServer()
{
    //   if(socket->state() == QTcpSocket::ConnectedState) {
           socket->disconnectFromHost();
    //       serverSocket.waitForDisconnected(3000);
    //   }
           return 0;
}

int MachineConfigModel::clearMessages()
{
    machineCmd->Clear();
    serverCmdMesg->release_machineconf();
    serverCmdMesg->Clear();
    return 0;;
}

void MachineConfigModel::setUIMessages(UIMessages *uiMsg)
{
    uiMessages = uiMsg;
}
