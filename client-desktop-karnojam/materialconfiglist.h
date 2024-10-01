#ifndef MATERIALCONFIGLIST_H
#define MATERIALCONFIGLIST_H

#include <QObject>
#include <QVector>
#include "materialconfig.h"

class MaterialConfigList : public QObject
{
    Q_OBJECT
public:
    MaterialConfigList();
    bool setConfigItem(int index, MaterialConfig &configItem);
//       bool isNewId(uint8_t id);
    QVector<MaterialConfig> items();
    QVector<MaterialConfig> configItems;
    void addConfig(MaterialConfig config);

signals:
   void preItemAppended();
   void postItemAppended();
   void setData(const QModelIndex &index, const QVariant &value, int role);

   void preItemRemoved(int index);
   void postItemRemoved();
   void notifyInfoDataChanged();

public slots:
};

#endif // MATERIALCONFIGLIST_H
