#include "fileitemslist.h"

FileItemsList::FileItemsList()
{

}

bool FileItemsList::setConfigItem(int index, FileItem &file_item)
{
    if(index <0 || index >= fileItems.size())
            return false;

        fileItems[index] = file_item ;
        return true;
}

QVector<FileItem> FileItemsList::items()
{
    return fileItems;;
}

void FileItemsList::addFileItem(FileItem file_item)
{
    emit preItemAppended();
    fileItems.append(file_item);
    emit postItemAppended();
}
