#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include <QFile>
#include <QStorageInfo>
#include "spdlog/spdlog.h"
#include "assistant.h"
#include "Configs/Configs.h"
#include "message.pb.h"
#include "database.h"
#include "loginstance.h"
#include "materialschema.h"
#include "motionschema.h"
#include "jobschema.h"
#include "machineconfigschema.h"
#include <QCryptographicHash>

#define CONNMAX 10
#define BYTES 1024
#define WrongPacketCode -1001
#define WrongSubPacketCode -1002
#define HoldConnection 1001

using namespace std;

struct NetCommands {
      unsigned int iMachineConfig;
      unsigned int iCalibrState;
      unsigned int iGoPos;
      unsigned int iPrintState;
      unsigned int iMachineStatus;   // idle = 0   printing = 1  Calibrating = 2
      unsigned int getstatus;
      unsigned int iMaterial;
      unsigned int iMotion;
      unsigned int iJobFile;
      unsigned int iManualMV;
      unsigned int iMatPat;
      unsigned int iLicenseStatus;  // 1 = ok    2 = Wrong Name   3 = License Expired
      unsigned int iRenewLicense;
      unsigned int iVacuumTimer;
      unsigned int iMaterialLevel;
      float fmateriallevelmm;
      float ffillvacuumsec;
      float sensorVal;
      char iRequestedCode[8];
      char iLicenseKey[8];
      __Job3D job;
      MotionConfig motionConfig;
      MaterialConfig materialConfig;
};


struct SystemStatus {
      unsigned short iTotalLayers;
      unsigned short iCurentLayer;
      // unsigned short TotalTime;
      // unsigned short ReminedTime;
      unsigned short iPrintState;
      unsigned short iDoorState;
      long TotalTime;
      long RemainedTime;
      long RemainedLicense;
};



class NetWork {

public:      
    NetWork();
    spdlog::logger *logger;
    void setLogger(spdlog::logger *log);
    DataBase *db;
    void setDataBase(DataBase *dataBase);
    NetCommands    *net_cmds;
    SystemStatus   sys_status;
    mutex *mutexProtection;
    void setMutex(mutex *m);
    vector<int>  *clientsfd;
    void setBackEndfd(vector<int> *cfd);
    MaterialConfigFile *matrial_cfg;
    MachineConfig *machine_cfg;
    MotionConfigFile  *motion_cfg;
    bool listening = true;

    int listenfd, clients[CONNMAX];


    FILE *file;

    int netInit(NetCommands *lcmds);
    void pynetMain();
    int netClose();
    void startServer(char *port);
    int CalculateKey(char RequestedCode[8]);
    int Activate();
    void respond(int n);
    int networkMessage(int n, int rcvd, char mesg[], spdlog::logger *logger2);

    //packet handlers
    void request_handler(int clientfd);
    int materialCMDPacket(int clientfdIndex, network_messages::MaterialConfig materialCmd);
    void sendMaterial(MaterialConfig *mConf, int clientfd);
    void sendAllMaterial(vector<MaterialConfig> *mConfV, int clientfd);
    int motionCMDPacket(int clientfd, network_messages::MotionConfig motionCmd);
    void sendMotion(MotionConfig *mConf, int clientfd);
    void sendAllMotion(vector<MotionConfig> *mConfV, int clientfd);
    int jobCMDPacket(int clientfdIndex, network_messages::Job3D jobCmd);
    void sendJob(__Job3D *mConf, int clientfd);
    void sendAllJob(vector<__Job3D> *jobV, int clientfd);
    int printCMDPacket(int clientfd, network_messages::NetServerCommands printCmd);
    int getStateCMDPacket(int clientfd, network_messages::NetServerCommands stateCmd);




    int calibrateCMDPacket(int clientfd, network_messages::NetServerCommands calibCmd);
    int machineConfigCMDPacket(int clientfd, network_messages::MachineConfig mCmd);
    void sendMachineConf(MachineConfig *mConf, int clientfd);
    void sendAllMachineConf(vector<MachineConfig> *mConfV, int clientfd);
    int mMVCMDPacket(int clientfd, network_messages::NetServerCommands MVCmd);
    void sendNotFound(int clientfd);
    void sendDoneMsg(int clientfd);
    void sendSensorVal(int clientfd,float val);
    void sendErrorMsg(int clientfd, string err);
    void sendStateMsg(int clientfd, google::protobuf::uint32 state );
    int writeSocket(int clientfd, char *mBuf, int size);

    QByteArray fileChecksum(QString fileName, QCryptographicHash::Algorithm hashAlgorithm);
    void sendMd5(int clientfd, QByteArray Md5);
    JobSchema jSchemaCurrent;
    QString currentJobName;

//    void changeMachineConfig(MachineConfig mConfig, int ModelCode);
};

