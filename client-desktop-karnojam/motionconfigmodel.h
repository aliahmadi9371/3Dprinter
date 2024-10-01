#ifndef MOTIONCONFIGMODEL_H
#define MOTIONCONFIGMODEL_H

#include <QAbstractListModel>
#include <QTcpSocket>
#include <QThread>
#include "materialconfig.h"
#include "motionconfig.h"
#include "machineconfig.h"
#include "message.pb.h"
#include "uimessages.h"

class MotionConfigList;

class MotionConfigModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(MotionConfigList *list READ list WRITE setList )
public:
    explicit MotionConfigModel(QObject *parent = nullptr);
    enum {
           Name, Layer_Z_Raise1, Layer_Z_Raise2, Layer_Z_Lower1, Layer_Z_Lower2, Layer_Tilt_Raise1, Layer_Tilt_Raise2,
           Layer_Tilt_Lower1, Layer_Tilt_Lower2, Layer_Overlift1, Layer_Overlift2, Layer_Breathe1, Layer_Breathe2,
           Layer_Settle1, Layer_Settle2, Layer_Tilt_Percent1, Layer_Tilt_Percent2, Cut_Off_Layers,
           Final_OverLift, Base_Layer_settle
       };

       // Basic functionality:
       int rowCount(const QModelIndex &parent = QModelIndex()) const override;

       QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

       // Editable:
       bool setData(const QModelIndex &index, const QVariant &value,
                    int role = Qt::EditRole) override;

       virtual QHash<int, QByteArray> roleNames() const override;

       Qt::ItemFlags flags(const QModelIndex& index) const override;

       MotionConfigList *list() const;
       void setList(MotionConfigList *list);
       void addElement(MotionConfig item);
       int size();
       int getId(int index);
       Q_INVOKABLE void makeNewConfig(QString mName, int mLayer_Z_Raise1, int mLayer_Z_Raise2,
                   int mLayer_Z_Lower1, int mLayer_Z_Lower2, int mLayer_Tilt_Raise1, int mLayer_Tilt_Raise2,
                   int mLayer_Tilt_Lower1, int mLayer_Tilt_Lower2, int mLayer_Overlift1, int mLayer_Overlift2,
                   int mLayer_Breathe1, int mLayer_Breathe2, int mLayer_Settle1, int  mLayer_Settle2,
                   int mLayer_Tilt_Percent1, int mLayer_Tilt_Percent2, int mCut_Off_Layers,
                   int mFinal_OverLift, int mBase_Layer_settle);
       Q_INVOKABLE void removeConfig(int index);
       Q_INVOKABLE void setConfig(int index, QString mName, int mLayer_Z_Raise1, int mLayer_Z_Raise2,
                                  int mLayer_Z_Lower1, int mLayer_Z_Lower2, int mLayer_Tilt_Raise1, int Layer_Tilt_Raise2,
                                  int Layer_Tilt_Lower1, int Layer_Tilt_Lower2, int Layer_Overlift1, int Layer_Overlift2,
                                  int mLayer_Breathe1, int mLayer_Breathe2, int mLayer_Settle1, int  mLayer_Settle2,
                                  int mLayer_Tilt_Percent1, int mLayer_Tilt_Percent2, int mCut_Off_Layers,
                                  int mFinal_OverLift, int mBase_Layer_settle);
       Q_INVOKABLE void refreshData();
       QString MachineAddress;
       QString MachinePort;
       int connectToServer();
       int disconnetFromServer();
       int clearMessages();
       network_messages::NetServerCommands *serverCmdMesg;
       network_messages::NetClientRes *serverResMesg;
       network_messages::MotionConfig *motionCmd;
       void setMachineIpPort(QString mAddress, QString mPort);
       QVector<MotionConfig> items();

       UIMessages *uiMessages;
       void setUIMessages(UIMessages *uiMsg);
private:
    MotionConfigList *mList;
    QTcpSocket *socket;
};

#endif // MOTIONCONFIGMODEL_H
