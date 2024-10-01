#ifndef FILEITEM_H
#define FILEITEM_H

#include <iostream>
#include <QString>

using namespace std;

struct FileItem {
    QString Name = "";
    bool isDirectory = false;
    QString Path;
    FileItem() {}
    FileItem(QString name, bool isD, QString path) {
        Name = name; isDirectory = isD; Path = path;
    }
};


#endif // FILEITEM_H
