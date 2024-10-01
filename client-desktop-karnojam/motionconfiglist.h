#ifndef MOTIONCONFIGLIST_H
#define MOTIONCONFIGLIST_H

#include <QObject>
#include <QVector>
#include "motionconfig.h"

class MotionConfigList : public QObject
{
    Q_OBJECT
public:
    explicit MotionConfigList(QObject *parent = nullptr);
    bool setConfigItem(int index, MotionConfig &configItem);
//       bool isNewId(uint8_t id);
    QVector<MotionConfig> items();
    QVector<MotionConfig> motionItems;
    void addConfig(MotionConfig config);

signals:
   void preItemAppended();
   void postItemAppended();
   void setData(const QModelIndex &index, const QVariant &value, int role);

   void preItemRemoved(int index);
   void postItemRemoved();
   void notifyInfoDataChanged();

public slots:

};

#endif // MOTIONCONFIGLIST_H
