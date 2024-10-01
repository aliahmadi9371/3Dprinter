#ifndef JOBLIST_H
#define JOBLIST_H

#include <QObject>
#include <QVector>
#include "Job.h"

class JobList : public QObject
{
    Q_OBJECT
public:
    JobList();
    bool setConfigItem(int index, __Job3D &job3D);
//       bool isNewId(uint8_t id);
    QVector<__Job3D> items();
    QVector<__Job3D> job3DItems;
    void addJob3D(__Job3D job3D);

signals:
   void preItemAppended();
   void postItemAppended();
   void setData(const QModelIndex &index, const QVariant &value, int role);

   void preItemRemoved(int index);
   void postItemRemoved();
   void notifyInfoDataChanged();

public slots:
};

#endif // JOBLIST_H
