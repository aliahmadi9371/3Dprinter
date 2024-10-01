#include "jsonstoring.h"

JsonStoring::JsonStoring()
{

}

void JsonStoring::storeGeneralData(GeneralData generalData)
{
     QJsonObject qJsonObject;
     qJsonObject.insert("modelCode", generalData.modelCode);
     QString data = jsonToString(qJsonObject);
     storeToFile(data, GeneralDataFile);
}

GeneralData JsonStoring::getGeneralData()
{
   QString jsonString = getFileString(GeneralDataFile);
   GeneralData temp;
   if(jsonString == "") {
       qDebug() << "JsonStoring: storeToFile: JsonStoring::getGeneralData() does not exist";
//       cout<< "JsonStoring::getGeneralData() does not exist"<<endl;
       return  temp;
   }
   QJsonDocument qJsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
   QJsonObject qJsonObject = qJsonDocument.object();
   temp.modelCode = qJsonObject["modelCode"].toDouble();
   return  temp;
}

QString JsonStoring::jsonToString(QJsonObject jsonObject)
{
    QJsonDocument doc(jsonObject);
    return  doc.toJson(QJsonDocument::Compact);
}

void JsonStoring::storeToFile(QString data, QString fileName)
{
    QFile file(fileName);
        if(file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )
        {
            QTextStream textStream( &file );
            QStringList stringList;
            textStream << data;
            file.close();
        } else {
            qDebug() << "JsonStoring: storeToFile: file " << fileName << " could not open";
//            cout<< " file " << fileName.data() << " could not open" << endl;
        }
}

QString JsonStoring::getFileString(QString fileName)
{
    QString temp = "";
    QFile file(fileName);
    if(! Assistant::isFileExists(fileName.toStdString()) ) { // file.exists()
        qDebug() << "JsonStoring: getFileString: Assistant::isFileExists said: " << fileName << " File not exists";
//        cout << "Assistant::isFileExists said :"<< fileName.toStdString() << " File not exists "<<endl;
        return temp;
    }
    if( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "JsonStoring: getFileString: " << fileName << " File not exists";
//        cout << fileName.toStdString() << " File not exists "<<endl;
    } else {
        qDebug() << "JsonStoring: getFileString: " << fileName << " exists";
//        cout<< fileName.toStdString() <<" exist"<<endl;
        QTextStream in(&file);
        temp = in.readLine();
        file.close();
    }

    return temp;
}
