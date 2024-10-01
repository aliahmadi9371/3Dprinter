#include "serialport.h"

SerialPort::SerialPort(QObject *parent) : QObject(parent)
{
    bool RS485 = true;
    serial = new QSerialPort(this);
    serial->close();
    if (RS485){
        serial->setBaudRate(QSerialPort::Baud38400);
    }else {
        serial->setBaudRate(QSerialPort::Baud115200);
    }
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
}

QStringList SerialPort::availablePorts()
{
    QStringList ports;

    for (QSerialPortInfo port : QSerialPortInfo::availablePorts())
    {

        //Their is some sorting to do for just list the port I want, with vendor Id & product Id
//        cout << port.portName().toStdString() << port.vendorIdentifier() << port.productIdentifier()
//                 << port.hasProductIdentifier() << port.hasVendorIdentifier() << port.isBusy()<<endl;
        qDebug() << "SerialPort: availablePorts: port.portName(): " << port.portName();
        qDebug() << "SerialPort: availablePorts: port.vendorIdentifier(): " <<port.vendorIdentifier();
//        cout << port.portName().toStdString() << port.vendorIdentifier()<<endl;
        ports += port.portName();
    }
    return ports;
}

QString SerialPort::availablePortByVID(quint16 VID)
{

    for (QSerialPortInfo port : QSerialPortInfo::availablePorts())
    {
        qDebug() << "SerialPort: availablePortByVID: port.portName(): " << port.portName();
        qDebug() << "SerialPort: availablePortByVID: port.vendorIdentifier(): " <<port.vendorIdentifier();
        if (port.vendorIdentifier()== VID){

//            cout << port.portName().toStdString()<<endl;
            return  port.portName();
        }
    }

    qDebug() << "SerialPort: availablePortByVID: FAILED TO FIND PORT";
//    cout << "FAILED TO FIND PORT"<<endl;
    return "";


}

bool SerialPort::connectSerialPort()
{
    if(QSerialPortInfo::availablePorts().size()>0) {
     if(!serial->isOpen()) {
         Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
//              serial->setPortName(port.portName());
              serial->setPortName("ttyACM1");
              qDebug() << "SerialPort: connectSerialPort: portName: " << port.portName();
//              cout<< " portName : " << port.portName().toStdString()<<endl;
              if(serial->open(QIODevice::ReadWrite)) {
                  qDebug() << "SerialPort: connectSerialPort: conndected ";
//                     cout << " conndected : "<<endl;
//                     connect(serial, SIGNAL(readyRead()), this, SLOT(recieveSerialPort()));
                     return true;
                   break;
               } else {
                  qDebug() << "SerialPort: connectSerialPort: Not conndected";
//                     cout<< "Not conndected : ";
                     serial->close();
               }
         }
         qDebug() << "SerialPort: connectSerialPort: serial can not connect";
//         cout<< "serial can not connect"<<endl;
         return false;
     } else {
         qDebug() << "SerialPort: connectSerialPort: serial port connected before, please disconnect then connet";
//         cout<< "serial port connected before, please disconnect then connet"<< endl;
         return false;
     }
    } else {
        qDebug() << "SerialPort: connectSerialPort: there is no serial port info";
//        cout<< "there is no serial port info"<< endl;
        serial->close();
        return false;
    }
}

bool SerialPort::connectSerialPort(QString comePort)
{
    if(QSerialPortInfo::availablePorts().size()>0) {
     if(!serial->isOpen()) {
              serial->setPortName(comePort);
              if(serial->open(QIODevice::ReadWrite)) {
                  qDebug() << "SerialPort: connectSerialPort: conndected";
//                     cout << " conndected : "<<endl;
//                     connect(serial, SIGNAL(readyRead()), this, SLOT(recieveSerialPort()));
                     return true;
               }
         qDebug() << "SerialPort: connectSerialPort: serial can not connect to " << comePort;
//         cout<< "serial can not connect to "<< comePort.toStdString() <<endl;
         return false;
     } else {
         qDebug() << "SerialPort: connectSerialPort: serial port connected before, please disconnect then connect";
//         cout<< "serial port connected before, please disconnect then connect"<< endl;
         return false;
     }
    } else {
        qDebug() << "SerialPort: connectSerialPort: there is no serial port info";
        cout<< "there is no serial port info"<< endl;
        serial->close();
        return false;
    }
}

// index from zero
bool SerialPort::connectSerialPort(int i)
{
    if(QSerialPortInfo::availablePorts().size()>i) {
         if(!serial->isOpen()) {
                  QSerialPortInfo port = QSerialPortInfo::availablePorts()[i];
                  serial->setPortName(port.portName());
                  qDebug() << "SerialPort: connectSerialPort: portName " << port.portName();
//                  cout<< " portName : " << port.portName().toStdString()<<endl;
                  if(serial->open(QIODevice::ReadWrite)) {
                       qDebug() << "SerialPort: connectSerialPort: conndected";
//                         cout << " conndected : "<<endl;
//                         connect(serial, SIGNAL(readyRead()), this, SLOT(recieveSerialPort()));
                         return true;
                   } else {
                      qDebug() << "SerialPort: connectSerialPort: Not conndected";
//                         cout<< "Not conndected : ";
                         serial->close();
                   }
                  qDebug() << "SerialPort: connectSerialPort: serial can not connect";
//             cout<< "serial can not connect"<<endl;
             return false;
         } else {
             qDebug() << "SerialPort: connectSerialPort: serial port connected before, please disconnect then connect";
//             cout<< "serial port connected before, please disconnect then connet"<< endl;
             return false;
         }
        } else {
        qDebug() << "SerialPort: connectSerialPort: there is no serial port info";
//            cout<< "there is not "<<i<<" serial port info: "<< QSerialPortInfo::availablePorts().size()<< endl;
            serial->close();
            return false;
        }
}

void SerialPort::disconnectSerialPort()
{
    serial->close();
}
