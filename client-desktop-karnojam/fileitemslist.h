#ifndef FILEITEMSLIST_H
#define FILEITEMSLIST_H

#include <QObject>
#include <QVector>
#include "FileItem.h"

class FileItemsList : public QObject
{
    Q_OBJECT
public:
    FileItemsList();
    bool setConfigItem(int index, FileItem &file_item);
    QVector<FileItem> items();
    QVector<FileItem> fileItems;
    void addFileItem(FileItem file_item);
signals:
   void preItemAppended();
   void postItemAppended();
   void setData(const QModelIndex &index, const QVariant &value, int role);

   void preItemRemoved(int index);
   void postItemRemoved();
   void notifyInfoDataChanged();

};

#endif // FILEITEMSLIST_H
