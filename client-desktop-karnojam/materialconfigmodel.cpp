#include "materialconfigmodel.h"
#include "materialconfiglist.h"

MaterialConfigModel::MaterialConfigModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
     mList = new MaterialConfigList();
     serverCmdMesg = new network_messages::NetServerCommands();
     serverResMesg = new network_messages::NetClientRes();
     materialCmd = new network_messages::MaterialConfig();
//     MaterialConfig temp;
//     memcpy( temp.Name, "test" ,4);
//     temp.Intensity = 14;
//     temp.BurnInLayers = 20;
//     temp.BurnIntensity = 16;
//     temp.BurnInCureTime = 32;
//     temp.LayerThickness = 5;
//     temp.NormalCureTime = 16;
//     mList->addConfig(temp);
}

int MaterialConfigModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
            return 0;

        return mList->items().size();
}

QVariant MaterialConfigModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
          return QVariant();

      const MaterialConfig item = mList->items().at(index.row());
      switch (role) {
       case Name:
          return QVariant( QString::fromStdString(item.Name));
       case LayerThickness:
          return QVariant(item.LayerThickness);
      case BurnInLayers:
         return QVariant(item.BurnInLayers);
      case BurnInCureTime:
         return QVariant(item.BurnInCureTime);
      case NormalCureTime:
         return QVariant(item.NormalCureTime);
      case BurnIntensity:
         return QVariant(item.BurnIntensity);
      case Intensity:
         return QVariant(item.Intensity);
      }

      return QVariant();
}

bool MaterialConfigModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
           return false;

       if(index.row() >= mList->items().size()) {
//           cout<< "setData index.row():"<< index.row()<<", role:"<< role << endl;
           return false;
       }
       MaterialConfig item = mList->items().at(index.row());
       switch (role) {
        case Name:
           item.Name  = value.toString().toStdString();
           break;
        case LayerThickness:
          item.LayerThickness = static_cast<unsigned int>(value.toInt());
          break;
        case BurnInLayers:
          item.BurnInLayers = static_cast<unsigned int>(value.toInt());
          break;
        case BurnInCureTime:
           cout<<index.row()<<" setData temperature role :"<<value.toFloat()<<endl;
          item.BurnInCureTime = value.toFloat();
          break;
       case NormalCureTime:
          cout<<index.row()<<" setData standardId role :"<<value.toInt()<<endl;
         item.NormalCureTime = value.toInt();
         break;
       case BurnIntensity:
          cout<<index.row()<<" setData humidity role :"<<value.toInt()<<endl;
         item.BurnIntensity = value.toInt();
         break;
       case Intensity:
          cout<<index.row()<<" setData turningMode role :"<<value.toBool()<<endl;
         item.Intensity = value.toBool();
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

QHash<int, QByteArray> MaterialConfigModel::roleNames() const
{
    QHash<int, QByteArray> names;
        names[Name] = "Name";
        names[LayerThickness] = "LayerThickness" ;
        names[BurnInLayers] = "BurnInLayers" ;
        names[BurnInCureTime] = "BurnInCureTime" ;
        names[NormalCureTime] = "NormalCureTime" ;
        names[BurnIntensity] = "BurnIntensity" ;
        names[Intensity] = "Intensity" ;
        return names;
}

Qt::ItemFlags MaterialConfigModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
            return Qt::NoItemFlags;

        return Qt::ItemIsEditable;
}

MaterialConfigList *MaterialConfigModel::list() const
{
    return mList;
}

void MaterialConfigModel::setList(MaterialConfigList *list)
{
    beginResetModel();
       if(mList)
           mList->disconnect(this);

       mList = list;

       endResetModel();
}

void MaterialConfigModel::addElement(MaterialConfig item)
{
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Material);
    materialCmd->set_packetcode(network_messages::MaterialConfig::Add);
    materialCmd->set_name(item.Name);
    materialCmd->set_intensity(item.Intensity);
    materialCmd->set_burninlayers(item.BurnInLayers);
    materialCmd->set_burnintensity(item.BurnIntensity); // item.MachineNo
    materialCmd->set_burnincuretime(item.BurnInCureTime);
    materialCmd->set_layerthickness(item.LayerThickness);
    materialCmd->set_normalcuretime(item.NormalCureTime);;
    serverCmdMesg->set_allocated_materialconfig(materialCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);
    if(connectToServer() < 0) {
       qDebug() << "MaterialConfigModel sendReq socket does not connect ";
    } else {
        socket->write(mBuf, size);
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(3000);
        QByteArray bRes = socket->readAll();
        serverResMesg->Clear();
        serverResMesg->ParseFromArray(bRes.data(), bRes.size());
        if(serverResMesg->packetcode() == network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Done) {
            beginResetModel();
            mList->configItems.append(item);
            endResetModel();
        } else {
            qDebug()<< "MaterialConfigModel::addElement error"<< QString::fromStdString(serverResMesg->errormesg()) ;
        }
    }
    disconnetFromServer();
    delete [] mBuf;
    refreshData();
}

int MaterialConfigModel::getId(int index)
{
    if( (0 > index) || (index >= size())) {
        qDebug()<< "MaterialConfigModel::getId index is wrong index:"<< index<< ", size:"<<size();
        return -1;
    }

    return mList->items().at(index).id;
}

int MaterialConfigModel::size()
{
   return mList->items().size();
}

void MaterialConfigModel::makeNewConfig(QString cName, int cLayerThickness, int cBurnInLayers,
                                        double cBurnInCureTime, double cNormalCureTime, double cBurnIntensity,
                                        double cIntensity)
{
    MaterialConfig mc;
    mc.Name = cName.toStdString();
    mc.LayerThickness = static_cast<unsigned int>(cLayerThickness);
    mc.BurnInLayers = static_cast<unsigned int>(cBurnInLayers);
    mc.BurnInCureTime = static_cast<float>(cBurnInCureTime);
    mc.NormalCureTime = static_cast<float>(cNormalCureTime);
    mc.BurnIntensity = static_cast<float>(cBurnIntensity);
    mc.Intensity = static_cast<float>(cIntensity);
    addElement(mc);
}

void MaterialConfigModel::removeConfig(int index)
{
    if(index > size()) {qDebug() << "MaterialConfigModel::removeConfig wrong index:"<<index; return;}
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Material);
    materialCmd->set_packetcode(network_messages::MachineConfig::Delete);
    materialCmd->set_rowid(mList->configItems[index-1].id);
    serverCmdMesg->set_allocated_materialconfig(materialCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);
    qDebug() << "MaterialConfigModel removeConfig index:"<<index<<", "<<", id:"<<mList->configItems[index-1].id;
    if(connectToServer() < 0) {
       qDebug() << "MaterialConfigModel removeConfig socket does not connect ";
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
           qDebug() << "MaterialConfigModel removeConfig can not delete"<< QString::fromStdString(serverResMesg->errormesg()) ;
        }
    }
    disconnetFromServer();
    delete [] mBuf;
}

void MaterialConfigModel::setConfig(int index, QString cName, int cLayerThickness, int cBurnInLayers,
                                    double cBurnInCureTime, double cNormalCureTime, double cBurnIntensity,
                                    double cIntensity)
{
    if(index > size()) {qDebug() << "MaterialConfigModel::setConfig wrong index:"<<index; return;}
    MaterialConfig item;
    item.id = mList->configItems[index-1].id;
    item.Name = cName.toStdString();
    item.LayerThickness = static_cast<unsigned int>(cLayerThickness);
    item.BurnInLayers = static_cast<unsigned int>(cBurnInLayers);
    item.BurnInCureTime = static_cast<float>(cBurnInCureTime);
    item.NormalCureTime = static_cast<float>(cNormalCureTime);
    item.BurnIntensity = static_cast<float>(cBurnIntensity);
    item.Intensity = static_cast<float>(cIntensity);
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Material);
    materialCmd->set_packetcode(network_messages::MaterialConfig::Edit);
    materialCmd->set_layerthickness(item.LayerThickness);
    materialCmd->set_rowid(item.id);
    materialCmd->set_name(item.Name);
    materialCmd->set_burninlayers(item.BurnInLayers);
    materialCmd->set_burnincuretime(item.BurnInCureTime);
    materialCmd->set_normalcuretime(item.NormalCureTime);
    materialCmd->set_burnintensity(item.BurnIntensity);
    materialCmd->set_intensity(item.Intensity);
    serverCmdMesg->set_allocated_materialconfig(materialCmd);
    qDebug() << "MaterialConfigModel id:" << item.id;
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);
    if(connectToServer() < 0) {
       qDebug() << "MaterialConfigModel setConfig socket does not connect ";
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
        } else {
           qDebug() << "MaterialConfigModel setConfig can not happen"<< QString::fromStdString(serverResMesg->errormesg()) ;
        }
    }

    disconnetFromServer();
    delete [] mBuf;
}

void MaterialConfigModel::refreshData()
{
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Material);
    materialCmd->set_packetcode(network_messages::MaterialConfig::GetALL);
    serverCmdMesg->set_allocated_materialconfig(materialCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);

    if(connectToServer() < 0) {
       qDebug() << "MaterialConfigModel refreshData socket does not connect ";
    } else {
       socket->write(mBuf, size);
       socket->waitForBytesWritten(3000);
       socket->waitForReadyRead(2000);
       QByteArray temp = socket->readAll();
       serverResMesg->ParseFromArray(temp.data(), temp.size());
       if(serverResMesg->packetcode() == network_messages::NetClientRes::Founded ) {
           beginResetModel();
           mList->configItems.clear();
           for(int i=0; i<serverResMesg->materials_size(); i++) {
               MaterialConfig mConf ;
               network_messages::MaterialConfig confMesg = serverResMesg->materials(i);
               mConf.id = confMesg.rowid();
               mConf.Name = confMesg.name();
               mConf.Intensity = confMesg.intensity();
               mConf.BurnInLayers = confMesg.burninlayers();
               mConf.BurnIntensity = confMesg.burnintensity();
               mConf.BurnInCureTime = confMesg.burnincuretime();
               mConf.LayerThickness = confMesg.layerthickness();
               mConf.NormalCureTime = confMesg.normalcuretime();
               mList->addConfig(mConf);
               cout<< "mConf.id:"<<mConf.id<<endl;
           }
           endResetModel();
       } else if(serverResMesg->packetcode() == network_messages::NetClientRes::NotFound ) {
           beginResetModel();
           mList->configItems.clear();
           endResetModel();
       } else {
           qDebug() << "MaterialConfigModel refreshData can not Recieve" ;
       }
    }
    disconnetFromServer();
    delete [] mBuf;
}

QStringList MaterialConfigModel::getNameList()
{
    QStringList temp;
    cout<< "getNameList"<<endl;
    for(QVector<MaterialConfig>::iterator it = mList->items().begin(); it != mList->items().end() ; it++ ) {

//        temp.append( QString::fromStdString(it->Name) );
        temp.append("test");
        cout<< it->Name <<endl;
    }
    return temp;
}

int MaterialConfigModel::connectToServer()
{
    socket = new QTcpSocket();
    int result = 1;
    if(socket->state() != QTcpSocket::ConnectedState) {
        socket->connectToHost(MachineAddress, MachinePort.toUShort());
        result = socket->waitForConnected(3000);
    }
    return result;
}

int MaterialConfigModel::disconnetFromServer()
{
    //   if(socket->state() == QTcpSocket::ConnectedState) {
           socket->disconnectFromHost();
    //       serverSocket.waitForDisconnected(3000);
    //   }
           return 0;
}

int MaterialConfigModel::clearMessages()
{
    materialCmd->Clear();
    serverCmdMesg->release_materialconfig();
    serverCmdMesg->Clear();
    return 0;
}

void MaterialConfigModel::setMachineIpPort(QString mAddress, QString mPort)
{
    MachineAddress = mAddress;
    MachinePort = mPort;
}

QVector<MaterialConfig> MaterialConfigModel::items()
{
    return mList->items();
}

void MaterialConfigModel::setUIMessages(UIMessages *uiMsg)
{
    uiMessages = uiMsg;
}

