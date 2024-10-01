
#ifndef ARDUINO_H
#define ARDUINO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <sys/ioctl.h>
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <sys/time.h>
#include <pthread.h>


class Arduino
{
public:
    int tmp1;
    bool bopened;
private:
    struct termios tty;
    int fd;
    int ireta;
    pthread_t thread_aloop;

    char PortName[256];
    char SendBuff[12];
    char RcvBuff[14];
    int  iCurPos;
    int  iCurCmd;

public:
    Arduino();
    int Connect(char *PortName);
    int Disconnect(void);
    int SendMessage(char msg,int value);
    int Response(void);
    int GetWorkState(void);
    int GetZoffset(void);
    int GetDoorState(void);
    int GetErr(void);
private:
    int Available(void);
    void Read(char * buffer, int amountOfBytes);
    void Read(char * bytePtr);
	int  Write(char * bytePtr,int len);
    //static void *stLoop(void *ptr);
};

#endif
