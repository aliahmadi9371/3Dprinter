#include "ProjectorRS232.h"
#include <QDebug>

ProjectorRS232::ProjectorRS232()
{
}


////////////////////////////

int ProjectorRS232::Connect(char *PortName)
{
    struct termios config;
    sprintf(this->PortName,"%s",PortName);

    // Open port
    fd = open(PortName, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0)
    {
//        printf("Failed to open port!\n");
        qDebug() << "ProjectorRS232: Connect: Failed to open port!" ;
    }

    // Config
    tcgetattr(fd, &config);
    // Set baudrate
    cfsetispeed(&config, B9600);
    cfsetospeed(&config, B9600);

    // 9600 8N1
    config.c_cflag &= ~PARENB;
    config.c_cflag &= ~CSTOPB;
    config.c_cflag &= ~CSIZE;
    config.c_cflag |=  CS8;
    // Disable hardware based flow control
    config.c_cflag &= ~CRTSCTS;

    // Enable receiver
    config.c_cflag |= CREAD | CLOCAL;                               
    // Disable software based flow control
    config.c_iflag &= ~(IXON | IXOFF | IXANY);

    // Termois Non Cannoincal Mode 
    config.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 

    // Minimum number of characters for non cannoincal read
    config.c_cc[VMIN]  = 1;
    // Timeout in deciseconds for read
    config.c_cc[VTIME] = 0; 

    // Save config
    if (tcsetattr(fd, TCSANOW, &config) < 0)                        
    {
        close(fd);

//        printf("Failed to configure port!");
        qDebug() << "ProjectorRS232: Connect: Failed to configure port!" ;

    }

    // Flush RX Buffer
    if (tcflush(fd, TCIFLUSH) < 0)
    {
        close(fd);

//        printf("Failed to flush buffer!");
        qDebug() << "ProjectorRS232: Connect: Failed to flush buffer!" ;

    }
    usleep(2000*1000);
    bopened = 1;
    return 0;
}

////////////////////////////

int ProjectorRS232::Disconnect(void)
{
    close(fd);
    return 0;
}


////////////////////////////

void ProjectorRS232::PONOF(int Status)
{
    char buff[1];
    int rcvindex = 0;
    int cnt = 0;   // For loop timer

    memset(RcvBuff,0,10);

    SendBuff[0] = 0x02;
    SendBuff[1] = 'A';
    SendBuff[2] = 'D';
    SendBuff[3] = 'Z';
    SendBuff[4] = 'Z';
    SendBuff[5] = ';';
    SendBuff[6] = 'P';
    SendBuff[7] = 'O';
    SendBuff[8] = 'F';
    SendBuff[9] = 0x03;

    if (Status){
        SendBuff[8] = 'N';
    }

    Write(SendBuff,10);

    while ((rcvindex<10)&&(cnt<50))
    {
        usleep(10*1000);
        if (Available() > 0)
        {
            Read(buff,1);
            RcvBuff[rcvindex] = buff[0];
            // printf("%c\n",RcvBuff[rcvindex]);
            rcvindex++;
        }
        cnt++;
    }
}


////////////////////////////

void ProjectorRS232::Shutter(int Status)
{
    char buff[1];
    int rcvindex = 0;
    int cnt = 0;   // For loop timer

    memset(RcvBuff,0,12);

    SendBuff[0] = 0x02;
    SendBuff[1] = 'A';
    SendBuff[2] = 'D';
    SendBuff[3] = 'Z';
    SendBuff[4] = 'Z';
    SendBuff[5] = ';';
    SendBuff[6] = 'O';
    SendBuff[7] = 'S';
    SendBuff[8] = 'H';
    SendBuff[9] = ':';
    SendBuff[10] = '1';
    SendBuff[11] = 0x03;

    if (Status){
        SendBuff[10] = '0';
    }

    Write(SendBuff,12);

    while ((rcvindex<12)&&(cnt<50))
    {
        usleep(10*1000);
        if (Available() > 0)
        {
            Read(buff,1);
            RcvBuff[rcvindex] = buff[0];
            // printf("%c\n",RcvBuff[rcvindex]);
            rcvindex++;
        }
        cnt++;
    }
}

////////////////////////////

int ProjectorRS232::POW()
{
    char buff[1];
    int rcvindex = 0;
    int cnt = 0;   // For loop timer

    memset(RcvBuff,0,12);

    SendBuff[0] = 0x02;
    SendBuff[1] = 'A';
    SendBuff[2] = 'D';
    SendBuff[3] = 'Z';
    SendBuff[4] = 'Z';
    SendBuff[5] = ';';
    SendBuff[6] = 'Q';
    SendBuff[7] = 'P';
    SendBuff[8] = 'W';
    SendBuff[9] = 0x03;

    Write(SendBuff,10);

    while ((rcvindex<12)&&(cnt<50))
    {
        usleep(10*1000);
        if (Available() > 0)
        {
            Read(buff,1);
            RcvBuff[rcvindex] = buff[0];
            // printf("%c\n",RcvBuff[rcvindex]);
            rcvindex++;
        }
        cnt++;
    }

    usleep(10*1000);
    if (RcvBuff[3] == '1'){

//        printf("ON\n");
        qDebug() << "ProjectorRS232: POW: ON" ;

        return 1;
    }else{

//        printf("OFF\n");
        qDebug() << "ProjectorRS232: POW: OFF" ;

        return 0;
    }
}

////////////////////////////

int ProjectorRS232::Available()
{
    int bytes = 0;
    if (ioctl(fd, TIOCINQ, &bytes) < 0)
    {
        close(fd);

//        printf("Failed to check buffer!");
        qDebug() << "ProjectorRS232: Available: Failed to check buffer!" ;

    }
    return bytes;
}

////////////////////////////

void ProjectorRS232::Read(char * buffer, int amountOfBytes)
{
    if (read(fd, buffer, amountOfBytes) < 0)
    {
        close(fd);

//        printf("Failed to read bytes!");
        qDebug() << "ProjectorRS232: Read: Failed to read bytes!" ;

    }
}

////////////////////////////

void ProjectorRS232::Read(char * bytePtr)
{
    ProjectorRS232::Read(bytePtr, 1);
}

////////////////////////////

int ProjectorRS232::Write(char * bytePtr,int len)
{
    int bytesWritten = write(fd, bytePtr, len);

    if (bytesWritten < 0)
    {
        close(fd);

//        printf("Failed to write bytes!");
        qDebug() << "ProjectorRS232: Write: Failed to write bytes!" ;

    }

    return bytesWritten;
}
