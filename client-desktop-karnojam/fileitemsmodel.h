#ifndef FILEITEMSMODEL_H
#define FILEITEMSMODEL_H

#include <QObject>
#include <QDebug>
#include <QAbstractListModel>
#include "FileItem.h"
#include "assistant.h"

class FileItemsList;

class FileItemsModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(FileItemsList *list READ list WRITE setList )
public:
    FileItemsModel();
    enum {
           Name, isDirectory, Path
       };

       // Basic functionality:
       int rowCount(const QModelIndex &parent = QModelIndex()) const override;

       QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

       // Editable:
       bool setData(const QModelIndex &index, const QVariant &value,
                    int role = Qt::EditRole) override;

       virtual QHash<int, QByteArray> roleNames() const override;

       Qt::ItemFlags flags(const QModelIndex& index) const override;

       FileItemsList *list() const;
       void setList(FileItemsList *list);
//       void addElement(FileItem item);
//       int getId(int index);
       Q_INVOKABLE int size();
       Q_INVOKABLE void makeNewItem(QString name, bool isDirectory, QString path);
       Q_INVOKABLE void clear();
       Q_INVOKABLE bool isUSBDrive();
       Q_INVOKABLE void refreshDirectory();
       Q_INVOKABLE void goToDirectory(QString path);
       Q_INVOKABLE void selectFile(QString path);
       Q_INVOKABLE void backDirectory();
       QStringList getItemsList(QString response);
//       Q_INVOKABLE void setConfig(int index, QString cName, int cLayerThickness, int cBurnInLayers,
//                                  double cBurnInCureTime, double cNormalCureTime, double cBurnIntensity,
//                                  double cIntensity);


       QString userName;
       QString currentPath;

private:
    FileItemsList *mList;

signals:
   void fileSelected(QString path);
};

#endif // FILEITEMSMODEL_H
