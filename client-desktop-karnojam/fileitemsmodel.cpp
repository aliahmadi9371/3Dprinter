#include "fileitemsmodel.h"
#include "fileitemslist.h"

FileItemsModel::FileItemsModel()
{
    mList = new FileItemsList();
}

int FileItemsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
            return 0;

    return mList->items().size();
}

QVariant FileItemsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
          return QVariant();

      const FileItem item = mList->items().at(index.row());
      switch (role) {
       case Name:
          return QVariant( item.Name);
       case isDirectory:
          return QVariant(item.isDirectory);
      case Path:
         return QVariant(item.Path);

      }

      return QVariant();
}

bool FileItemsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
           return false;

       if(index.row() >= mList->items().size()) {
//           cout<< "setData index.row():"<< index.row()<<", role:"<< role << endl;
           return false;
       }
       FileItem item = mList->items().at(index.row());
       switch (role) {
        case Name:
           item.Name = value.toString();
           break;
        case isDirectory:
//           cout<<index.row()<<" setData rainOff role "<<value.toInt()<<endl;
          item.isDirectory = value.toBool();
          break;
        case Path:
//           cout<<index.row()<<" setData rainOn role "<<value.toInt()<<endl;
          item.Path = value.toString();
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

QHash<int, QByteArray> FileItemsModel::roleNames() const
{
    QHash<int, QByteArray> names;
        names[Name] = "Name";
        names[isDirectory] = "isDirectory" ;
        names[Path] = "Path" ;

        return names;
}

Qt::ItemFlags FileItemsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
            return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

FileItemsList *FileItemsModel::list() const
{
    return mList;
}

void FileItemsModel::setList(FileItemsList *list)
{
    beginResetModel();
       if(mList)
           mList->disconnect(this);

       mList = list;

       endResetModel();
}

int FileItemsModel::size()
{
    return mList->items().size();
}

void FileItemsModel::makeNewItem(QString name, bool isDirectory, QString path)
{
    FileItem item(name, isDirectory, path);
    beginResetModel();
    mList->fileItems.append(item);
    endResetModel();
}

void FileItemsModel::clear()
{
    beginResetModel();
    mList->fileItems.clear();
    endResetModel();
}

bool FileItemsModel::isUSBDrive()
{
   userName = QString::fromStdString( Assistant::exec("ls /media") );
   userName = userName.replace("\n","");
   qDebug() << "isUSBDrive userName :"<< userName;
   string command = "ls /media/"+userName.toStdString();
   QString usbDrives = QString::fromStdString( Assistant::exec(command.c_str()) );
   if(usbDrives.size() == 0) {
       qDebug() <<"There is not usb drive connected to board";
       return false;
   }
   currentPath = "/media/"+userName;
   return true;
}

void FileItemsModel::refreshDirectory()
{
    string command = "ls "+currentPath.toStdString();
    qDebug()<<"refreshDirectory command:"<<QString::fromStdString(command);
    QString response =  QString::fromStdString( Assistant::exec(command.c_str()) );
    qDebug() << "refreshDirectory response:"<<response;
    if(response.size() == 0) {
        qDebug() << "refreshDirectory there is no fileItem";
        return;
    }

    QStringList found_items =  getItemsList(response);
    clear();
    qDebug() <<" refreshDirectory " << found_items.size();
    for(int i=0; i<found_items.size();i++) {
//        qDebug() << found_items[i];
        makeNewItem(found_items[i], Assistant::isDirectory(currentPath.toStdString()+"/"+found_items[i].toStdString()),
                    currentPath+"/"+found_items[i]);
    }
}

void FileItemsModel::goToDirectory(QString path)
{

    currentPath = path;
    string command = "ls "+currentPath.toStdString();
    qDebug()<<"goToDirectory command:"<<QString::fromStdString(command);
    QString response =  QString::fromStdString( Assistant::exec(command.c_str()) );
    qDebug() << "goToDirectory response:"<<response;
    if(response.size() == 0) {
        qDebug() << "refreshDirectory there is no fileItem";
        return;
    }
    QStringList found_items =  getItemsList(response);
    clear();
//    qDebug() <<" refreshDirectory " << found_items.size();
    for(int i=0; i<found_items.size();i++) {
//        qDebug() << found_items[i];
        makeNewItem(found_items[i], Assistant::isDirectory(currentPath.toStdString()+"/"+found_items[i].toStdString()),
                    currentPath+"/"+found_items[i]);
    }
}

void FileItemsModel::selectFile(QString path)
{
    emit fileSelected(path);
}

void FileItemsModel::backDirectory()
{
   if(currentPath.size() > 1) {
    qDebug() << "backDirectory :"<<currentPath;
    QStringList path_items =  currentPath.split("/");
    currentPath = "";
    for(int i=1; i< path_items.size()-1; i++) {
        qDebug() << "path_items[i] :"<<path_items[i];
        currentPath = currentPath+"/"+path_items[i];
    }
    qDebug() << "backDirectory last:"<<currentPath;
    refreshDirectory();
   } else {
       qDebug()<< "backDirectory current path is root path:"<< currentPath;
   }
}

QStringList FileItemsModel::getItemsList(QString response)
{
    QStringList path_items =  response.split("\n");
    QStringList found_items;
    for(int i=0; i< path_items.size(); i++) {
//        qDebug()<< "path_items[i]:" << path_items[i];
            if(path_items[i] != "" ) {
               found_items.append(path_items[i]);
            }
    }

    return found_items;
}

