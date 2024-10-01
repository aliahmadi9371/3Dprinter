#ifndef MATERIALCONFIGMODEL_H
#define MATERIALCONFIGMODEL_H

#include <QAbstractListModel>
#include <QTcpSocket>
#include "materialconfig.h"
#include "motionconfig.h"
#include "machineconfig.h"
#include "message.pb.h"
#include "uimessages.h"

class MaterialConfigList;


//char Name[10];
//unsigned int LayerThickness;
//unsigned int BurnInLayers;
//float BurnInCureTime;
//float NormalCureTime;
//float BurnIntensity;
//float Intensity;

class MaterialConfigModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(MaterialConfigList *list READ list WRITE setList )
public:
    explicit MaterialConfigModel(QObject *parent = nullptr);
    enum {
           Name, LayerThickness, BurnInLayers, BurnInCureTime, NormalCureTime, BurnIntensity, Intensity
       };

       // Basic functionality:
       int rowCount(const QModelIndex &parent = QModelIndex()) const override;

       QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

       // Editable:
       bool setData(const QModelIndex &index, const QVariant &value,
                    int role = Qt::EditRole) override;

       virtual QHash<int, QByteArray> roleNames() const override;

       Qt::ItemFlags flags(const QModelIndex& index) const override;

       MaterialConfigList *list() const;
       void setList(MaterialConfigList *list);
       void addElement(MaterialConfig item);
       int getId(int index);
       Q_INVOKABLE int size();
       Q_INVOKABLE void makeNewConfig(QString cName, int cLayerThickness, int cBurnInLayers,
                                      double cBurnInCureTime, double cNormalCureTime, double cBurnIntensity,
                                      double cIntensity);
       Q_INVOKABLE void removeConfig(int index);
       Q_INVOKABLE void setConfig(int index, QString cName, int cLayerThickness, int cBurnInLayers,
                                  double cBurnInCureTime, double cNormalCureTime, double cBurnIntensity,
                                  double cIntensity);
       Q_INVOKABLE void refreshData();
       Q_INVOKABLE QStringList getNameList();
       QString MachineAddress;
       QString MachinePort;
       int connectToServer();
       int disconnetFromServer();
       int clearMessages();
       network_messages::NetServerCommands *serverCmdMesg;
       network_messages::NetClientRes *serverResMesg;
       network_messages::MaterialConfig *materialCmd;
       void setMachineIpPort(QString mAddress, QString mPort);
       int sendReq(char *mBuf, int size);
        QVector<MaterialConfig> items();

        UIMessages *uiMessages;
        void setUIMessages(UIMessages *uiMsg);
private:
    MaterialConfigList *mList;
    QTcpSocket *socket;
};

#endif // MATERIALCONFIGMODEL_H
