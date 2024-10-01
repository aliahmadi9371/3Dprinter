
#include "Arduino.h"
#include <QDebug>

Arduino::Arduino()
{

}

int Arduino::Connect(char *PortName)
{
    struct termios config;
    sprintf(this->PortName,"%s",PortName);

    qDebug() << "Arduino: Connect: PortName: " << PortName;

    // Open port
    fd = open(PortName, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0)
    {
        qDebug() << "Arduino: Connect: Failed to open port!";
//        printf("Failed to open port!\n");
    }
    else
        qDebug() << "Arduino: Connect: open arduino port";

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
        qDebug() << "Arduino: Connect: Failed to configure port!";
//        printf("Failed to configure port!");
    }

    // Flush RX Buffer
    if (tcflush(fd, TCIFLUSH) < 0)
    {
        close(fd);
        qDebug() << "Arduino: Connect: Failed to flush buffer!";
//        printf("Failed to flush buffer!");
    }
    usleep(2000*1000);
    bopened = 1;
    return 0;
}

int Arduino::Disconnect(void)
{
    close(fd);
    return 0;
}

//int Arduino::SendMessage(char msg,int value)
//{
//    bool Success = false;
//    while(!Success)
//    {
//        char buff[10];
//        int rcvindex = 0;
//        int len = 0;
//        int cnt = 0;

//        memset(RcvBuff,0,8);

//        SendBuff[0] = 0xfa;
//        SendBuff[1] = 0x55;
//        SendBuff[2] = msg;
//        SendBuff[3] = 0;
//        SendBuff[4] = 0;
//        SendBuff[5] = 0;
//        SendBuff[6] = 0;
//        SendBuff[7] = 0;
//        SendBuff[8] = 0;
//        SendBuff[9] = 0;
//        SendBuff[10] = 0;
//        SendBuff[11] = 0x7a;

//        len = sprintf(buff,"%d",value);
//        memcpy(SendBuff+3,buff,7);
//        Write(SendBuff,12);
//        //printf("::::=> %s\n",SendBuff+2);

//        while ((rcvindex<14)&&(cnt<50))
//        {
//            usleep(10*1000);
//            if (Available() > 0)
//            {
//                Read(buff,1);
//                RcvBuff[rcvindex] = buff[0];
//                rcvindex++;
//            }
//            cnt++;
//        }
//        //memcpy(&iCurPos,RcvBuff+3,4);
//    //    iCurPos = atoi(RcvBuff+3);
//        iCurCmd = atoi(RcvBuff+3);

//        if (RcvBuff[2] == msg && iCurCmd == value)
//        {
//            Success = true;
//            qDebug()<< "::::::::::::::::::Arduino Checked Successfully::::::::::::::::::";
//            qDebug()<< "received cmd ::::::::::::::::::" << RcvBuff[2];
//            qDebug()<< "received val ::::::::::::::::::" << iCurCmd;
//        }else {
//            usleep(500*1000);
//            qDebug()<< "::::::::::::::::::Arduino Check failed::::::::::::::::::";
//            qDebug()<< "received cmd ::::::::::::::::::" << RcvBuff[2];
//            qDebug()<< "received val ::::::::::::::::::" << iCurCmd;
//        }
//    }

//    return RcvBuff[12];
//}

int Arduino::SendMessage(char msg,int value)
{
    char buff[10];
    int rcvindex = 0;
    int len = 0;
    int cnt = 0;

    memset(RcvBuff,0,8);

    SendBuff[0] = 0xfa;
    SendBuff[1] = 0x55;
    SendBuff[2] = msg;
    SendBuff[3] = 0;
    SendBuff[4] = 0;
    SendBuff[5] = 0;
    SendBuff[6] = 0;
    SendBuff[7] = 0;
    SendBuff[8] = 0;
    SendBuff[9] = 0;
    SendBuff[10] = 0;
    SendBuff[11] = 0x7a;

    len = sprintf(buff,"%d",value);
    memcpy(SendBuff+3,buff,7);
    Write(SendBuff,12);
    //printf("::::=> %s\n",SendBuff+2);

    while ((rcvindex<26)&&(cnt<50))
    {
        usleep(10*1000);
        int r = Available();
//        qDebug() << "r = " << r;
        if (r > 0)
        {
            Read(buff,1);
            RcvBuff[rcvindex] = buff[0];
//            qDebug() << "RcvBuff[ " << rcvindex << "] = " << (int)RcvBuff[rcvindex];
            rcvindex++;
        }
        cnt++;
    }
//    qDebug() << "RcvBuff[2] = " << (int)RcvBuff[2];
    //memcpy(&iCurPos,RcvBuff+3,4);
    iCurPos = atoi(RcvBuff+3);

    char r[12];
    for(int i=0; i<12; i++){
        r[i] = RcvBuff[i+14];
    }
    QString tmp(r);
    int free_mem = tmp.toInt();
    qDebug() << "Arduino: SendMessage: free memory = " << tmp;
    if(free_mem < 0)
        qDebug() << "Arduino: SendMessage: !!!!!!!!!!!!!!!free_mem = " << free_mem;
    return RcvBuff[12];
}


int Arduino::Response(void)
{
    char buff[8];
    int rcvindex = 0;
    int cnt = 0;

    memset(RcvBuff,0,10);

    SendBuff[0] = 0xfa;
    SendBuff[1] = 0x55;
    SendBuff[2] = 0x1;
    SendBuff[3] = 0;
    SendBuff[4] = 0;
    SendBuff[5] = 0;
    SendBuff[6] = 0;
    SendBuff[7] = 0;
    SendBuff[8] = 0;
    SendBuff[9] = 0;
    SendBuff[10] = 0;
    SendBuff[11] = 0x7a;
    Write(SendBuff,12);

    while ((rcvindex<26)&&(cnt<50))
    {

        //printf("::::=> %d <=",rcvindex);
        usleep(10*1000);
        int r = Available();
//        qDebug() << "r = " << r;
        if (r > 0)
        {
            Read(buff,1);
            RcvBuff[rcvindex] = buff[0];
//            qDebug() << "RcvBuff[ " << rcvindex << "] = " << (int)RcvBuff[rcvindex];
            rcvindex++;
        }
        cnt++;
    }
//    qDebug() << "RcvBuff[2] = " << (int)RcvBuff[2];
    //memcpy(&iCurPos,RcvBuff+3,4);
    iCurPos = atoi(RcvBuff+3);

    char r[12];
    for(int i=0; i<12; i++){
        r[i] = RcvBuff[i+14];
    }
    QString tmp(r);
    int free_mem = tmp.toInt();
    qDebug() << "free memory = " << tmp;
    if(free_mem < 0)
        qDebug() << "free_mem = " << free_mem;
    printf(buff,"=============%d",RcvBuff+3);
    return RcvBuff[12];
}

int Arduino::GetWorkState(void)
{
    return RcvBuff[2];
}

int Arduino::GetZoffset(void)
{
    return iCurPos;
}

int Arduino::GetDoorState(void)
{
    return RcvBuff[11];
}

int Arduino::GetErr(void)
{
    return RcvBuff[12];
}

int Arduino::Available()
{
    int bytes = 0;
    if (ioctl(fd, TIOCINQ, &bytes) < 0)
    {
        close(fd);
        qDebug() << "Arduino: Available: Failed to check buffer!";
//        printf("Failed to check buffer!");
    }
    return bytes;
}

void Arduino::Read(char * buffer, int amountOfBytes)
{
    if (read(fd, buffer, amountOfBytes) < 0)
    {
        close(fd);
        qDebug() << "Arduino: Available: Failed to read bytes!";
//        printf("Failed to read bytes!");
    }
}

void Arduino::Read(char * bytePtr)
{
    Arduino::Read(bytePtr, 1);
}

int Arduino::Write(char * bytePtr,int len)
{
    int bytesWritten = write(fd, bytePtr, len);

    if (bytesWritten < 0)
    {
        close(fd);
        qDebug() << "Arduino: Available: Failed to write bytes!";
//        printf("Failed to write bytes!");
    }

    return bytesWritten;
}



/*int Arduino::Run(void)
{
    ireta = pthread_create( &thread_aloop, NULL, this->stLoop, (void*) this);
}*/

/*void *Arduino::stLoop(void *ptr)
{
    Arduino *ard = ptr;
    char tempbuf[16];
    while(1)
    {
         usleep(400000);
        ard->ReadData();
        //printf("%s \n",RcvBuff);
    }
} */
