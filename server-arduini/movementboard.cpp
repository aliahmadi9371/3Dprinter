#include "movementboard.h"
#include<QDebug>

MovementBoard::MovementBoard()
{
    serial->setBaudRate(QSerialPort::Baud9600);
    if(connectSerialPort()) {
        qDebug() << "ovementBoard: MovementBoard: MovementBoard connect to Arduino";
//        spdlog::info("MovementBoard connect to Arduino");

        isConnected = true;
    } else {
        qDebug() << "MovementBoard: MovementBoard:MovementBoard can not connect to Arduino";
//        spdlog::warn("MovementBoard can not connect to Arduino");

    }
}

void MovementBoard::recieveSerialPort()
{

}
