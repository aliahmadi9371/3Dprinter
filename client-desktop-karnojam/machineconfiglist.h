#ifndef MACHINECONFIGLIST_H
#define MACHINECONFIGLIST_H

#include <QObject>
#include <QVector>
#include "machineconfig.h"

class MachineConfigList : public QObject
{
    Q_OBJECT
public:
    MachineConfigList();
    bool setConfigItem(int index, MachineConfig &configItem);
    QVector<MachineConfig> items();
    QVector<MachineConfig> configItems;
    void addConfig(MachineConfig config);
signals:
   void preItemAppended();
   void postItemAppended();
   void setData(const QModelIndex &index, const QVariant &value, int role);

   void preItemRemoved(int index);
   void postItemRemoved();
   void notifyInfoDataChanged();
};

#endif // MACHINECONFIGLIST_H
