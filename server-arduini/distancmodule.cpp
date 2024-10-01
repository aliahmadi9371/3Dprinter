#include "distancmodule.h"
#include <QDebug>

DistancModule::DistancModule()
{

}

void DistancModule::Connect()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    if(connectSerialPort(DistanceModulePort)) {

//        cout<<"DistancModule connect to stm32"<<endl;
        qDebug() << "DistancModule: Connect: DistancModule connect to stm32";

        isConnected = true;
    } else {

//        cout<<"DistancModule can not connect to stm32"<<endl;
        qDebug() << "DistancModule: Connect: DistancModule can not connect to stm32";

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

float DistancModule::getDistance()
{
   return distance;
}

float DistancModule::readData()
{
   bool RS485 = true;
   distance = -1;
   if (RS485){
       char SendBuff[10];   //%01#RMD**CR
       SendBuff[0]= '%';
       SendBuff[1]= '0';
       SendBuff[2]= '1';
       SendBuff[3]= '#';
       SendBuff[4]= 'R';
       SendBuff[5]= 'M';
       SendBuff[6]= 'D';
       SendBuff[7]= '*';
       SendBuff[8]= '*';
       SendBuff[9]= '\r';

       serial->write(SendBuff);
       serial->flush();
       this_thread::sleep_for(chrono::milliseconds(10));

       if(serial->waitForReadyRead(10000))
       {
            QByteArray dataSerial = serial->readAll();
            dataSerial.remove(0,7);
            dataSerial.remove(8,10);
            distance = dataSerial.toFloat();
            distance = distance/10000;

//            qDebug()<< "dataSerial : "<<dataSerial;
//            qDebug()<< "dataSerialFloat : "<<distance;
       }
   }else{
       if(serial->waitForReadyRead(10000))
       {
           QByteArray dataSerial = serial->readAll();

            for(int i=0; i<dataSerial.length(); i++) {
                if(dataSerial[i] == '*' && state == 0) {
                    state = 1;
                } else if(state == 1) {
                    dataTemp.append(dataSerial[i]);
                    state = 2;
                } else if(state == 2) {
                    dataTemp.append(dataSerial[i]);
                    state = 3;
                } else if(state == 3) {
                    state = 0;
                    uint8_t checksum = static_cast<uint8_t>((dataTemp[0]+dataTemp[1])%256)  ;
                    uint8_t packetChecksum = static_cast<uint8_t>(dataSerial[i]);
                    if( (checksum) != packetChecksum) {

//                        cout<<"checksum:"<<unsigned(checksum)<<", "<< unsigned(packetChecksum) <<endl;
                        qDebug() << "DistancModule: readData: hecksum: " << unsigned(checksum) << ", " << unsigned(packetChecksum);

//                        cout<<"DistancModule checksum is wrong"<<endl;
                        qDebug() << "DistancModule: readData: hDistancModule checksum is wrong";

                    } else {
                        unsigned int data1 = static_cast<unsigned int>(static_cast<unsigned char>(dataTemp[0]));
                        unsigned int data2 = static_cast<unsigned int>(static_cast<unsigned char>(dataTemp[1]));
                        distance = static_cast<float>(data1 + data2 *256) / 1000 ;
    //                    emit moduleDistanceData(distance);
                    }

                    dataTemp.clear();
                }
            }
       }else {
           qDebug()<< "DistancModule: readData: Failed to read DistanceModule";
       }
   }


   this_thread::sleep_for(chrono::milliseconds(20));
   return distance;

}

////////////////////////////////
/// \brief DistancModule::readData
/// \return
///

void DistancModule::readDataThread()
{
   bool RS485 = true;
   distance = -1;
   char SendBuff[10];   //%01#RMD**CR
   SendBuff[0]= '%';
   SendBuff[1]= '0';
   SendBuff[2]= '1';
   SendBuff[3]= '#';
   SendBuff[4]= 'R';
   SendBuff[5]= 'M';
   SendBuff[6]= 'D';
   SendBuff[7]= '*';
   SendBuff[8]= '*';
   SendBuff[9]= '\r';

   QByteArray dataSerial;

   while(1)
   {
       qDebug()<< "DistancModule: readDataThread: readDataThread";
       if (RS485){

           serial->write(SendBuff);
           serial->flush();
           this_thread::sleep_for(chrono::milliseconds(10));

           if(serial->waitForReadyRead(10000))
           {
                dataSerial = serial->readAll();
                dataSerial.remove(0,7);
                dataSerial.remove(8,10);
                distance = dataSerial.toFloat();
                distance = distance/10000;

    //            qDebug()<< "dataSerial : "<<dataSerial;
                qDebug()<< "DistancModule: readDataThread: dataSerialFloat : "<<distance;
           }
       }else{
           if(serial->waitForReadyRead(10000))
           {
               QByteArray dataSerial = serial->readAll();

                for(int i=0; i<dataSerial.length(); i++) {
                    if(dataSerial[i] == '*' && state == 0) {
                        state = 1;
                    } else if(state == 1) {
                        dataTemp.append(dataSerial[i]);
                        state = 2;
                    } else if(state == 2) {
                        dataTemp.append(dataSerial[i]);
                        state = 3;
                    } else if(state == 3) {
                        state = 0;
                        uint8_t checksum = static_cast<uint8_t>((dataTemp[0]+dataTemp[1])%256)  ;
                        uint8_t packetChecksum = static_cast<uint8_t>(dataSerial[i]);
                        if( (checksum) != packetChecksum) {

//                            cout<<"checksum:"<<unsigned(checksum)<<", "<< unsigned(packetChecksum) <<endl;
                            qDebug() << "DistancModule: readDataThread: hecksum: " << unsigned(checksum) << ", " << unsigned(packetChecksum);

//                            cout<<"DistancModule checksum is wrong"<<endl;
                            qDebug() << "DistancModule: readDataThread: DistancModule checksum is wrong";

                        } else {
                            unsigned int data1 = static_cast<unsigned int>(static_cast<unsigned char>(dataTemp[0]));
                            unsigned int data2 = static_cast<unsigned int>(static_cast<unsigned char>(dataTemp[1]));
                            distance = static_cast<float>(data1 + data2 *256) / 1000 ;
        //                    emit moduleDistanceData(distance);
                        }

                        dataTemp.clear();
                    }
                }
           }else {
               qDebug()<< "DistancModule: readDataThread: Failed to read DistanceModule";
           }
       }


       this_thread::sleep_for(chrono::milliseconds(200));
   }

}

///////////////////////////////////////////////
/// \brief DistancModule::recieveSerialPort
///
void DistancModule::recieveSerialPort()
{

}
