#include "motionconfigmodel.h"
#include "motionconfiglist.h"

MotionConfigModel::MotionConfigModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
      mList = new MotionConfigList();
      socket = new QTcpSocket();
      serverCmdMesg = new network_messages::NetServerCommands();
      serverResMesg = new network_messages::NetClientRes();
      motionCmd = new network_messages::MotionConfig();
}

int MotionConfigModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
            return 0;

    return mList->items().size();
}

QVariant MotionConfigModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
          return QVariant();

      const MotionConfig item = mList->items().at(index.row());
      switch (role) {
       case Name:
          return QVariant( QString::fromStdString(item.Name));
       case Layer_Z_Raise1:
          return QVariant(item.Layer_Z_Raise[0]);
      case Layer_Z_Raise2:
         return QVariant( item.Layer_Z_Raise[1]);
      case Layer_Z_Lower1:
         return QVariant(item.Layer_Z_Lower[0]);
      case Layer_Z_Lower2:
         return QVariant(item.Layer_Z_Lower[1]);
      case Layer_Tilt_Raise1:
         return QVariant(item.Layer_Tilt_Raise[0]);
      case Layer_Tilt_Raise2:
         return QVariant(item.Layer_Tilt_Raise[1]);
      case Layer_Tilt_Lower1:
         return QVariant(item.Layer_Tilt_Lower[0]);
      case Layer_Tilt_Lower2:
         return QVariant(item.Layer_Tilt_Lower[1]);
      case Layer_Overlift1:
         return QVariant(item.Layer_Overlift[0]);
      case Layer_Overlift2:
         return QVariant(item.Layer_Overlift[1]);
      case Layer_Breathe1:
         return QVariant(item.Layer_Breathe[0]);
      case Layer_Breathe2:
         return QVariant(item.Layer_Breathe[1]);
      case Layer_Settle1:
         return QVariant(item.Layer_Settle[0]);
      case Layer_Settle2:
         return QVariant(item.Layer_Settle[1]);
      case Layer_Tilt_Percent1:
         return QVariant(item.Layer_Tilt_Percent[0]);
      case Layer_Tilt_Percent2:
         return QVariant(item.Layer_Tilt_Percent[1]);
      case Cut_Off_Layers:
         return QVariant(item.Cut_Off_Layers);
      case Final_OverLift:
         return QVariant(item.Final_OverLift);
      case Base_Layer_settle:
         return QVariant(item.Base_Layer_settle);
      }

      return QVariant();
}

bool MotionConfigModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
           return false;

       if(index.row() >= mList->items().size()) {
//           cout<< "setData index.row():"<< index.row()<<", role:"<< role << endl;
           return false;
       }
       MotionConfig item = mList->items().at(index.row());
       switch (role) {
        case Name:
           item.Name = value.toString().toStdString();
           break;
        case Layer_Z_Raise1:
//           cout<<index.row()<<" setData rainOff role "<<value.toInt()<<endl;
          item.Layer_Z_Raise[0] = static_cast<unsigned int>(value.toInt());
          break;
        case Layer_Z_Raise2:
//           cout<<index.row()<<" setData rainOn role "<<value.toInt()<<endl;
          item.Layer_Z_Raise[1] = static_cast<unsigned int>(value.toInt());
          break;
        case Layer_Z_Lower1:
//           cout<<index.row()<<" setData temperature role :"<<value.toFloat()<<endl;
          item.Layer_Z_Lower[0] = static_cast<unsigned int>(value.toInt());
          break;
       case Layer_Z_Lower2:
//          cout<<index.row()<<" setData standardId role :"<<value.toInt()<<endl;
         item.Layer_Z_Lower[1] = static_cast<unsigned int>(value.toInt());
         break;
       case Layer_Tilt_Raise1:
//          cout<<index.row()<<" setData humidity role :"<<value.toInt()<<endl;
         item.Layer_Tilt_Raise[0] = static_cast<unsigned int>(value.toInt());
         break;
       case Layer_Tilt_Raise2:
//          cout<<index.row()<<" setData turningMode role :"<<value.toBool()<<endl;
          item.Layer_Tilt_Raise[1] = static_cast<unsigned int>(value.toInt());
         break;
       case Layer_Tilt_Lower1:
//          cout<<index.row()<<" setData humidity role :"<<value.toInt()<<endl;
         item.Layer_Tilt_Lower[0] = static_cast<unsigned int>(value.toInt());
         break;
       case Layer_Tilt_Lower2:
//          cout<<index.row()<<" setData turningMode role :"<<value.toBool()<<endl;
          item.Layer_Tilt_Lower[1] = static_cast<unsigned int>(value.toInt());
         break;
       case Layer_Overlift1:
//          cout<<index.row()<<" setData humidity role :"<<value.toInt()<<endl;
         item.Layer_Overlift[0] = static_cast<unsigned int>(value.toInt());
         break;
       case Layer_Overlift2:
//          cout<<index.row()<<" setData turningMode role :"<<value.toBool()<<endl;
          item.Layer_Overlift[1] = static_cast<unsigned int>(value.toInt());
         break;
       case Layer_Breathe1:
//          cout<<index.row()<<" setData humidity role :"<<value.toInt()<<endl;
         item.Layer_Breathe[0] = static_cast<unsigned int>(value.toInt());
         break;
       case Layer_Breathe2:
//          cout<<index.row()<<" setData turningMode role :"<<value.toBool()<<endl;
          item.Layer_Breathe[1] = static_cast<unsigned int>(value.toInt());
         break;
       case Layer_Settle1:
//          cout<<index.row()<<" setData humidity role :"<<value.toInt()<<endl;
         item.Layer_Settle[0] = static_cast<unsigned int>(value.toInt());
         break;
       case Layer_Settle2:
//          cout<<index.row()<<" setData turningMode role :"<<value.toBool()<<endl;
          item.Layer_Settle[1] = static_cast<unsigned int>(value.toInt());
         break;
       case Layer_Tilt_Percent1:
//          cout<<index.row()<<" setData humidity role :"<<value.toInt()<<endl;
         item.Layer_Tilt_Percent[0] = static_cast<unsigned int>(value.toInt());
         break;
       case Layer_Tilt_Percent2:
//          cout<<index.row()<<" setData turningMode role :"<<value.toBool()<<endl;
          item.Layer_Tilt_Percent[1] = static_cast<unsigned int>(value.toInt());
         break;
       case Cut_Off_Layers:
//          cout<<index.row()<<" setData humidity role :"<<value.toInt()<<endl;
         item.Cut_Off_Layers = static_cast<unsigned int>(value.toInt());
         break;
       case Final_OverLift:
//          cout<<index.row()<<" setData turningMode role :"<<value.toBool()<<endl;
          item.Final_OverLift = static_cast<unsigned int>(value.toInt());
         break;
       case Base_Layer_settle:
//          cout<<index.row()<<" setData turningMode role :"<<value.toBool()<<endl;
          item.Base_Layer_settle = static_cast<unsigned int>(value.toInt());
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

QHash<int, QByteArray> MotionConfigModel::roleNames() const
{
    QHash<int, QByteArray> names;
        names[Name] = "Name";
        names[Layer_Z_Raise1] = "Layer_Z_Raise1" ;
        names[Layer_Z_Raise2] = "Layer_Z_Raise2" ;
        names[Layer_Z_Lower1] = "Layer_Z_Lower1" ;
        names[Layer_Z_Lower2] = "Layer_Z_Lower2" ;
        names[Layer_Tilt_Raise1] = "Layer_Tilt_Raise1" ;
        names[Layer_Tilt_Raise2] = "Layer_Tilt_Raise2" ;
        names[Layer_Tilt_Lower1] = "Layer_Tilt_Lower1" ;
        names[Layer_Tilt_Lower2] = "Layer_Tilt_Lower2" ;
        names[Layer_Overlift1] = "Layer_Overlift1" ;
        names[Layer_Overlift2] = "Layer_Overlift2" ;
        names[Layer_Settle1] = "Layer_Settle1" ;
        names[Layer_Settle2] = "Layer_Settle2" ;
        names[Layer_Tilt_Percent1] = "Layer_Tilt_Percent1" ;
        names[Layer_Tilt_Percent2] = "Layer_Tilt_Percent2" ;
        names[Layer_Breathe1] = "Layer_Breathe1" ;
        names[Layer_Breathe2] = "Layer_Breathe2" ;
        names[Cut_Off_Layers] = "Cut_Off_Layers" ;
        names[Layer_Z_Lower2] = "Layer_Z_Lower2" ;
        names[Final_OverLift] = "Final_OverLift" ;
        names[Base_Layer_settle] = "Base_Layer_settle" ;
        return names;
}

Qt::ItemFlags MotionConfigModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
            return Qt::NoItemFlags;

        return Qt::ItemIsEditable;
}

MotionConfigList *MotionConfigModel::list() const
{
     return mList;
}

void MotionConfigModel::setList(MotionConfigList *list)
{
    beginResetModel();
       if(mList)
           mList->disconnect(this);

       mList = list;

       endResetModel();
}

void MotionConfigModel::addElement(MotionConfig item)
{
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Motion);
    motionCmd->set_packetcode(network_messages::MotionConfig::Add);
    motionCmd->set_name(item.Name);
    motionCmd->add_layer_settle(item.Layer_Settle[0]);
    motionCmd->add_layer_settle(item.Layer_Settle[1]);
    motionCmd->add_layer_breathe(item.Layer_Breathe[0]);
    motionCmd->add_layer_breathe(item.Layer_Breathe[1]);
    motionCmd->add_layer_z_lower(item.Layer_Z_Lower[0]);
    motionCmd->add_layer_z_lower(item.Layer_Z_Lower[1]);
    motionCmd->add_layer_z_raise(item.Layer_Z_Raise[0]);
    motionCmd->add_layer_z_raise(item.Layer_Z_Raise[1]);
    motionCmd->add_layer_overlift(item.Layer_Overlift[0]);
    motionCmd->add_layer_overlift(item.Layer_Overlift[1]);
    motionCmd->add_layer_tilt_lower(item.Layer_Tilt_Lower[0]);
    motionCmd->add_layer_tilt_lower(item.Layer_Tilt_Lower[1]);
    motionCmd->add_layer_tilt_raise(item.Layer_Tilt_Raise[0]);
    motionCmd->add_layer_tilt_raise(item.Layer_Tilt_Raise[1]);
    motionCmd->add_layer_tilt_percent(item.Layer_Tilt_Percent[0]);
    motionCmd->add_layer_tilt_percent(item.Layer_Tilt_Percent[1]);
    motionCmd->set_base_layer_settle(item.Base_Layer_settle);
    motionCmd->set_cut_off_layers(item.Cut_Off_Layers);
    motionCmd->set_final_overlift(item.Final_OverLift);
    serverCmdMesg->set_allocated_motionconfig(motionCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);
    if(connectToServer() < 0) {
       qDebug() << "MotionConfigModel sendReq socket does not connect ";
    } else {
        socket->write(mBuf, size);
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(3000);
        QByteArray bRes = socket->readAll();
        serverResMesg->Clear();
        serverResMesg->ParseFromArray(bRes.data(), bRes.size());
        if(serverResMesg->packetcode() == network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Done) {
            beginResetModel();
            mList->motionItems.append(item);
            endResetModel();
        } else {
            qDebug()<< "MotionConfigModel::addElement error"<< QString::fromStdString(serverResMesg->errormesg()) ;
        }
    }
    disconnetFromServer();
    delete [] mBuf;
    refreshData();
}

int MotionConfigModel::size()
{
    return mList->items().size();
}

int MotionConfigModel::getId(int index)
{
    if( (0 > index) || (index >= size())) {
        qDebug()<< "MotionConfigModel::getId index is wrong index:"<< index<< ", size:"<<size();
        return -1;
    }

    return mList->items().at(index).id;
}

void MotionConfigModel::makeNewConfig(QString mName, int mLayer_Z_Raise1, int mLayer_Z_Raise2,
                                      int mLayer_Z_Lower1, int mLayer_Z_Lower2, int mLayer_Tilt_Raise1,
                                      int mLayer_Tilt_Raise2, int mLayer_Tilt_Lower1, int mLayer_Tilt_Lower2,
                                      int mLayer_Overlift1, int mLayer_Overlift2, int mLayer_Breathe1,
                                      int mLayer_Breathe2, int mLayer_Settle1, int mLayer_Settle2,
                                      int mLayer_Tilt_Percent1, int mLayer_Tilt_Percent2, int mCut_Off_Layers,
                                      int mFinal_OverLift, int mBase_Layer_settle)
{
    MotionConfig mc;
    mc.Name = mName.toStdString();
    mc.Layer_Z_Raise[0] = static_cast<unsigned int>(mLayer_Z_Raise1);
    mc.Layer_Z_Raise[1] = static_cast<unsigned int>(mLayer_Z_Raise2);
    mc.Layer_Z_Lower[0] = static_cast<unsigned int>(mLayer_Z_Lower1);
    mc.Layer_Z_Lower[1] = static_cast<unsigned int>(mLayer_Z_Lower2);
    mc.Layer_Tilt_Raise[0] = static_cast<unsigned int>(mLayer_Tilt_Raise1);
    mc.Layer_Tilt_Raise[1] = static_cast<unsigned int>(mLayer_Tilt_Raise2);
    mc.Layer_Tilt_Lower[0] = static_cast<unsigned int>(mLayer_Tilt_Lower1);
    mc.Layer_Tilt_Lower[1] = static_cast<unsigned int>(mLayer_Tilt_Lower2);
    mc.Layer_Overlift[0] = static_cast<unsigned int>(mLayer_Overlift1);
    mc.Layer_Overlift[1] = static_cast<unsigned int>(mLayer_Overlift2);
    mc.Layer_Breathe[0] = static_cast<unsigned int>(mLayer_Breathe1);
    mc.Layer_Breathe[1] = static_cast<unsigned int>(mLayer_Breathe2);
    mc.Layer_Settle[0] = static_cast<unsigned int>(mLayer_Settle1);
    mc.Layer_Settle[1] = static_cast<unsigned int>(mLayer_Settle2);
    mc.Layer_Tilt_Percent[0] = static_cast<unsigned int>(mLayer_Tilt_Percent1);
    mc.Layer_Tilt_Percent[1] = static_cast<unsigned int>(mLayer_Tilt_Percent2);
    mc.Cut_Off_Layers = static_cast<unsigned int>(mCut_Off_Layers);
    mc.Final_OverLift = static_cast<unsigned int>(mFinal_OverLift);
    mc.Base_Layer_settle = static_cast<unsigned int>(mBase_Layer_settle);
    addElement(mc);
}



void MotionConfigModel::removeConfig(int index)
{

    if(index > size()) {qDebug() << "MotionConfigModel::removeConfig wrong index:"<<index; return;}
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Motion);
    motionCmd->set_packetcode(network_messages::MotionConfig::Delete);
    motionCmd->set_rowid(mList->motionItems[index-1].id);
    qDebug() << "MotionConfigModel::removeConfig id:"<< mList->motionItems[index-1].id;
    serverCmdMesg->set_allocated_motionconfig(motionCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);

    if(connectToServer() < 0) {
       qDebug() << "MotionConfigModel removeConfig socket does not connect ";
    } else {
        socket->write(mBuf, size);
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(2000);
        QByteArray temp = socket->readAll();
        serverResMesg->ParseFromArray(temp.data(), temp.size());
        if(serverResMesg->packetcode() == network_messages::NetClientRes::Done) {
            beginResetModel();
            mList->motionItems.remove(index-1);
            endResetModel();
        } else {
           qDebug() << "MotionConfigModel removeConfig can not delete"<< QString::fromStdString(serverResMesg->errormesg()) ;
        }
    }
    disconnetFromServer();
    delete [] mBuf;
}

void MotionConfigModel::setConfig(int index, QString mName, int mLayer_Z_Raise1, int mLayer_Z_Raise2,
                                  int mLayer_Z_Lower1, int mLayer_Z_Lower2, int mLayer_Tilt_Raise1,
                                  int mLayer_Tilt_Raise2, int mLayer_Tilt_Lower1, int mLayer_Tilt_Lower2,
                                  int mLayer_Overlift1, int mLayer_Overlift2, int mLayer_Breathe1,
                                  int mLayer_Breathe2, int mLayer_Settle1, int mLayer_Settle2,
                                  int mLayer_Tilt_Percent1, int mLayer_Tilt_Percent2, int mCut_Off_Layers,
                                  int mFinal_OverLift, int mBase_Layer_settle)
{


    if(index > size()) {qDebug() << "MaterialConfigModel::setConfig wrong index:"<<index; return;}
//    cout<< "MotionConfigModel setConfig id:"<<mList->motionItems[index-1].id<< ", index:"<<index  <<endl;
    MotionConfig item;
    item.id = mList->motionItems[index-1].id;
    item.Name = mName.toStdString();
    item.Layer_Z_Raise[0] = static_cast<unsigned int>(mLayer_Z_Raise1);
    item.Layer_Z_Raise[1] = static_cast<unsigned int>(mLayer_Z_Raise2);
    item.Layer_Z_Lower[0] = static_cast<unsigned int>(mLayer_Z_Lower1);
    item.Layer_Z_Lower[1] = static_cast<unsigned int>(mLayer_Z_Lower2);
    item.Layer_Tilt_Raise[0] = static_cast<unsigned int>(mLayer_Tilt_Raise1);
    item.Layer_Tilt_Raise[1] = static_cast<unsigned int>(mLayer_Tilt_Raise2);
    item.Layer_Tilt_Lower[0] = static_cast<unsigned int>(mLayer_Tilt_Lower1);
    item.Layer_Tilt_Lower[1] = static_cast<unsigned int>(mLayer_Tilt_Lower2);
    item.Layer_Overlift[0] = static_cast<unsigned int>(mLayer_Overlift1);
    item.Layer_Overlift[1] = static_cast<unsigned int>(mLayer_Overlift2);
    item.Layer_Breathe[0] = static_cast<unsigned int>(mLayer_Breathe1);
    item.Layer_Breathe[1] = static_cast<unsigned int>(mLayer_Breathe2);
    item.Layer_Settle[0] = static_cast<unsigned int>(mLayer_Settle1);
    item.Layer_Settle[1] = static_cast<unsigned int>(mLayer_Settle2);
    item.Layer_Tilt_Percent[0] = static_cast<unsigned int>(mLayer_Tilt_Percent1);
    item.Layer_Tilt_Percent[1] = static_cast<unsigned int>(mLayer_Tilt_Percent2);
    item.Cut_Off_Layers = static_cast<unsigned int>(mCut_Off_Layers);
    item.Final_OverLift = static_cast<unsigned int>(mFinal_OverLift);
    item.Base_Layer_settle = static_cast<unsigned int>(mBase_Layer_settle);

    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Motion);
    motionCmd->set_packetcode(network_messages::MotionConfig::Edit);
    motionCmd->set_name(item.Name);
    motionCmd->add_layer_settle(item.Layer_Settle[0]);
    motionCmd->add_layer_settle(item.Layer_Settle[1]);
    motionCmd->add_layer_breathe(item.Layer_Breathe[0]);
    motionCmd->add_layer_breathe(item.Layer_Breathe[1]);
    motionCmd->add_layer_z_lower(item.Layer_Z_Lower[0]);
    motionCmd->add_layer_z_lower(item.Layer_Z_Lower[1]);
    motionCmd->add_layer_z_raise(item.Layer_Z_Raise[0]);
    motionCmd->add_layer_z_raise(item.Layer_Z_Raise[1]);
    motionCmd->add_layer_overlift(item.Layer_Overlift[0]);
    motionCmd->add_layer_overlift(item.Layer_Overlift[1]);
    motionCmd->add_layer_tilt_lower(item.Layer_Tilt_Lower[0]);
    motionCmd->add_layer_tilt_lower(item.Layer_Tilt_Lower[1]);
    motionCmd->add_layer_tilt_raise(item.Layer_Tilt_Raise[0]);
    motionCmd->add_layer_tilt_raise(item.Layer_Tilt_Raise[1]);
    motionCmd->add_layer_tilt_percent(item.Layer_Tilt_Percent[0]);
    motionCmd->add_layer_tilt_percent(item.Layer_Tilt_Percent[1]);
    motionCmd->set_base_layer_settle(item.Base_Layer_settle);
    motionCmd->set_cut_off_layers(item.Cut_Off_Layers);
    motionCmd->set_final_overlift(item.Final_OverLift);
    motionCmd->set_rowid(mList->motionItems[index-1].id);
    serverCmdMesg->set_allocated_motionconfig(motionCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);
    if(connectToServer() < 0) {
       qDebug() << "MotionConfigModel setConfig socket does not connect ";
    } else {
        socket->write(mBuf, size);
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(2000);
        QByteArray temp = socket->readAll();
        serverResMesg->ParseFromArray(temp.data(), temp.size());
        if(serverResMesg->packetcode() == network_messages::NetClientRes::Done) {
            beginResetModel();
            mList->motionItems[index-1] = item;
            endResetModel();
        } else {
           qDebug() << "MotionConfigModel setConfig can not happen"<< QString::fromStdString(serverResMesg->errormesg()) ;
        }
    }

    disconnetFromServer();
    delete [] mBuf;
}

void MotionConfigModel::refreshData()
{
    clearMessages();
    serverCmdMesg->set_packetcode(network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Motion);
    motionCmd->set_packetcode(network_messages::MotionConfig::GetALL);
    serverCmdMesg->set_allocated_motionconfig(motionCmd);
    size_t size = serverCmdMesg->ByteSizeLong();
    char *mBuf = new char[size];
    serverCmdMesg->SerializeToArray(mBuf, size);

    if(connectToServer() < 0) {
       qDebug() << "MotionConfigModel refreshData socket does not connect ";
    } else {
       socket->write(mBuf, size);
       socket->waitForBytesWritten(3000);
       socket->waitForReadyRead(2000);
       QByteArray temp = socket->readAll();
       serverResMesg->ParseFromArray(temp.data(), temp.size());
       if(serverResMesg->packetcode() == network_messages::NetClientRes::Founded ) {
           beginResetModel();
           mList->motionItems.clear();
           for(int i=0; i<serverResMesg->motions_size(); i++) {
               MotionConfig mConf ;
               network_messages::MotionConfig confMesg = serverResMesg->motions(i);
               mConf.id = confMesg.rowid();
               mConf.Name = confMesg.name();
               if(confMesg.layer_settle_size() == 2) {
                 mConf.Layer_Settle[0] = confMesg.layer_settle(0);
                 mConf.Layer_Settle[1] = confMesg.layer_settle(1);
               }
               if(confMesg.layer_breathe_size() == 2) {
                 mConf.Layer_Breathe[0] = confMesg.layer_breathe(0);
                 mConf.Layer_Breathe[1] = confMesg.layer_breathe(1);
               }
               if(confMesg.layer_z_lower_size() == 2) {
                 mConf.Layer_Z_Lower[0] = confMesg.layer_z_lower(0);
                 mConf.Layer_Z_Lower[1] = confMesg.layer_z_lower(1);
               }
               if(confMesg.layer_z_raise_size() == 2) {
                 mConf.Layer_Z_Raise[0] = confMesg.layer_z_raise(0);
                 mConf.Layer_Z_Raise[1] = confMesg.layer_z_raise(1);
               }
               if(confMesg.layer_overlift_size() == 2) {
                 mConf.Layer_Overlift[0] = confMesg.layer_overlift(0);
                 mConf.Layer_Overlift[1] = confMesg.layer_overlift(1);
               }
               if(confMesg.layer_tilt_lower_size() == 2) {
                 mConf.Layer_Tilt_Lower[0] = confMesg.layer_tilt_lower(0);
                 mConf.Layer_Tilt_Lower[1] = confMesg.layer_tilt_lower(1);
               }
               if(confMesg.layer_tilt_raise_size() == 2) {
                 mConf.Layer_Tilt_Raise[0] = confMesg.layer_tilt_raise(0);
                 mConf.Layer_Tilt_Raise[1] = confMesg.layer_tilt_raise(1);
               }
               if(confMesg.layer_tilt_percent_size() == 2) {
                 mConf.Layer_Tilt_Percent[0] = confMesg.layer_tilt_percent(0);
                 mConf.Layer_Tilt_Percent[1] = confMesg.layer_tilt_percent(1);
               }
               mConf.Cut_Off_Layers = confMesg.cut_off_layers();
               mConf.Final_OverLift = confMesg.final_overlift();
               mConf.Base_Layer_settle = confMesg.base_layer_settle();
               cout<< "MotionConfigModel::refreshData() id:"<< mConf.id<<endl;
               mList->addConfig(mConf);
           }
           endResetModel();
       } else if(serverResMesg->packetcode() == network_messages::NetClientRes::NotFound ) {
           beginResetModel();
           mList->motionItems.clear();
           endResetModel();
       } else {
           qDebug() << "MotionConfigModel refreshData can not Recieve" ;
       }
    }
    disconnetFromServer();
    delete [] mBuf;
}

int MotionConfigModel::connectToServer()
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

int MotionConfigModel::disconnetFromServer()
{
    socket->flush();
    socket->disconnectFromHost();
    socket->close();
    delete socket;
    QThread::msleep(50);
    return 0;
}

int MotionConfigModel::clearMessages()
{
    motionCmd->Clear();
    serverCmdMesg->release_motionconfig();
    serverCmdMesg->Clear();

    return 0;
}

void MotionConfigModel::setMachineIpPort(QString mAddress, QString mPort)
{
    MachineAddress = mAddress;
    MachinePort = mPort;
}

QVector<MotionConfig> MotionConfigModel::items()
{
    return mList->items();
}

void MotionConfigModel::setUIMessages(UIMessages *uiMsg)
{
    uiMessages = uiMsg;
}



