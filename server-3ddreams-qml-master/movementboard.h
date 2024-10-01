#ifndef MOVEMENTBOARD_H
#define MOVEMENTBOARD_H
#include "serialport.h"
#include "spdlog/spdlog.h"

class MovementBoard : public SerialPort
{
public:
    MovementBoard();
    bool isConnected = false;


public slots:
   void recieveSerialPort();
};

#endif // MOVEMENTBOARD_H
