#ifndef DISTANCMODULE_H
#define DISTANCMODULE_H
#include "serialport.h"
#include "spdlog/spdlog.h"
#include <QDebug>

class DistancModule : public SerialPort
{
public:
    DistancModule();
    void Connect();
    bool isConnected = false;
    float getDistance();
    int state = 0;
    QByteArray data;
    QByteArray dataTemp;
    float distance = 0;
    float readData();
    void readDataThread();
    QString DistanceModulePort;


public slots:
   void recieveSerialPort();
};

#endif // DISTANCMODULE_H
