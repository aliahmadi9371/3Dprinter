#ifndef MACHINECONFIGMODEL_H
#define MACHINECONFIGMODEL_H

#include <QAbstractListModel>
#include <QTcpSocket>
#include "machineconfig.h"
#include "message.pb.h"
#include "uimessages.h"

class MachineConfigList;

class MachineConfigModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(MachineConfigList *list READ list WRITE setList )
public:
    explicit MachineConfigModel(QObject *parent = nullptr);
    enum {
           ModelCode, gProjectWidth, gProjectHeight, MachineNo, Version, SubVersion, NeedLicense,
         HasDoor, HasErm, BUpTDownConfig, PrinterUnit, ZUpperLimit, ProjectorProtocol, NoOfMaskPoints,
        MaxIntensity, MinIntensity,MaxIntensitySensor,MinIntensitySensor, id, HasPlunger,TDownZHomePos, vacuumTimer,SensorSetPointVacuum,
        SensorSetPoint,SensorThreshold, XShift,YShift
       };

       // Basic functionality:
       int rowCount(const QModelIndex &parent = QModelIndex()) const override;

       QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

       // Editable:
       bool setData(const QModelIndex &index, const QVariant &value,
                    int role = Qt::EditRole) override;

       virtual QHash<int, QByteArray> roleNames() const override;

       Qt::ItemFlags flags(const QModelIndex& index) const override;

       MachineConfigList *list() const;
       void setList(MachineConfigList *list);
       void addElement(MachineConfig item);
       int size();


       Q_INVOKABLE void makeNewConfig(int ModelCode, int gProjectWidth, int gProjectHeight,
                                      QString MachineNo, int  Version, int  SubVersion,
                                      bool  NeedLicense, bool  HasDoor, bool  HasErm, bool  BUpTDownConfig,
                                      float PrinterUnit, int ZUpperLimit, int ProjectorProtocol,
                                      int NoOfMaskPoints, int MaxIntensity, int MinIntensity,int MaxIntensitySensor, int MinIntensitySensor,
                                      bool HasPlunger,int TDownZHomePos,float vacuumTimer ,float SensorSetPointVacuum ,
                                      float SensorSetPoint ,float SensorThreshold ,float XShift = 0,float YShift = 0);
       Q_INVOKABLE void removeConfig(int index);
       Q_INVOKABLE void setConfig(int index,int ModelCode, int gProjectWidth, int gProjectHeight,
                                  QString MachineNo, int  Version, int  SubVersion,
                                  bool  NeedLicense, bool  HasDoor, bool  HasErm, bool  BUpTDownConfig,
                                  float PrinterUnit, int ZUpperLimit, int ProjectorProtocol,
                                  int NoOfMaskPoints, int MaxIntensity, int MinIntensity,int MaxIntensitySensor, int MinIntensitySensor,
                                  bool HasPlunger,int TDownZHomePos,float vacuumTimer ,float SensorSetPointVacuum ,
                                  float SensorSetPoint ,float SensorThreshold ,float XShift,float YShift);
       Q_INVOKABLE void refreshData();
       Q_INVOKABLE void setMachineModel(int index);
       QString MachineAddress;
       QString MachinePort;
       void setMachineIpPort(QString mAddress, QString mPort);
       int connectToServer();
       int disconnetFromServer();
       int clearMessages();
       MachineConfigList *mList;
       network_messages::NetServerCommands *serverCmdMesg;
       network_messages::NetClientRes *serverResMesg;
       network_messages::MachineConfig *machineCmd;
       UIMessages *uiMessages;
       void setUIMessages(UIMessages *uiMsg);
private:
    QTcpSocket *socket;
};

#endif // MACHINECONFIGMODEL_H
