#include "movementboard.h"

MovementBoard::MovementBoard()
{
    serial->setBaudRate(QSerialPort::Baud9600);
    if(connectSerialPort()) {
        spdlog::info("MovementBoard connect to Arduino");
        isConnected = true;
    } else {
        spdlog::warn("MovementBoard can not connect to Arduino");
    }
}

void MovementBoard::recieveSerialPort()
{

}
