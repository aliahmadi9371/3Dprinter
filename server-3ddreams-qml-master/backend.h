#ifndef BACKEND_H
#define BACKEND_H

#include "Arduino.h"
#include "ProjectorCOMM.h"
#include "ProjectorRS232.h"

#include "slcread.h"
#include "pyNet.h"
#include "message.pb.h"
#include <chrono>
#include <unistd.h>
#include "myutility.h"
#include <QObject>
#include <QDir>
#include <mutex>
#include <QSvgRenderer>
#include <QPainter>
#include <QDebug>
#include <QImage>
#include <QBuffer>
#include <QTimer>

#include "GeneralData.h"
#include "jsonstoring.h"
#include "imageitem.h"

#include "distancmodule.h"

#include <QElapsedTimer>

using namespace std::chrono;
using namespace std;


class BackEnd: public QObject
{
    Q_OBJECT
public:
//    BackEnd();

//    QTimer *arduinoTimer;

    explicit BackEnd(QObject *parent = nullptr);
    JsonStoring jStoring;
    GeneralData gData;
    DataBase *db;
    bool isPrint = false;
    Q_INVOKABLE bool isPrinting();
    QString printImage = "";
    Q_INVOKABLE QString getImagePreview();
    QString exePath = QDir::currentPath();

    // image renderer
    ImageItem *imageItem;

    Q_INVOKABLE void setImageItem(ImageItem *item);


    MaterialSchema materialSchema;
    MotionSchema motionSchema;
    JobSchema jobSchema;
    spdlog::logger *logger;
    mutex *mutexProtection;
    void setMutex(mutex *m);
    void setLogger(spdlog::logger *log);
    void setDataBase(DataBase *dataBase);
    struct timespec ts;
    MyUtility myUtility;
    vector<int> clientsfd;
    int writeSocket(int clientfd, const char *mBuf, int size);
    network_messages::NetClientRes netClientMessage;
//    DistancModule dModule;
    Arduino          arduino;
    ProjectorCOMM    projectorCOMM;
    ProjectorRS232   projectorRS232;

    QString ArduinoPort;

    float dModuleData;
    NetCommands    net_cmds;

    License        *license = new License();
    MaterialConfigFile *matrial_cfg = new MaterialConfigFile[MAXMATERIALS];
    MachineConfig *machine_cfg = new MachineConfig();
//    MachineConfigFile *machine_cfg = new MachineConfigFile();
    MotionConfigFile  *motion_cfg = new MotionConfigFile[MAXMOTIONS];

    SystemStatus   sys_status;

    DistancModule *dModule;

    bool bDebugMode = 0; //0
    int gProjectWidth  = 0;
    int gProjectHeight = 0;
    bool imageFileNameToggle = true;


    __Job3D jobinfo;

    int iCurZpos = 0;
    int NoOfTimedOut = 0;

    int NumOfSlices = 0;
    int iCurSlice = 2;
    char *tmpImage = new char[3840*2160];
    char *tmpImageBuf = new char[3840 * 2160];
    //char MaskBuff[1024*512];
    unsigned char MaskBuff[3840*2160];
    int  lenMaskImage = 0;

    char tempbuf[1024];

    int TotalLayers = 0;
    qint32 SumOfTimer = 0;

    bool bPassBurnInLayers = 0;

    int ZRaiseSpeed = 0;
    int ZLowerSpeed = 0;
    int TiltRaiseSpeed = 0;
    int TiltLowerSpeed = 0;
    int OverliftLayers = 5000;
    int sBreatheMs = 0;
    int sSettleMs = 0;
    int TiltPercent = 0;
    int FinalOverLiftLayers = 0;

    bool HasPlunger = false;
    int TDownZHomePos = 40000;//40200;  //37900
    float vacuumTimer = 0;//40; //Sec
    float SensorSetPointVacuum = 0;//0.6; //mm
    float SensorSetPoint = 0; //3.1; //mm   //16.4
    float SensorThreshold = 0; //0.003mm
    float XShift = 0; // 2.025;
    float YShift = 0;

    int iMachineStatus = 0;   // idle = 0   printing = 1  Calibrating = 2

    float fPixelSize = 75.0*0.001;

    float fCureTime;
    int Intensity;

    /////////////Time/////////////////////////////////////

    float OneLayerTime[2];

    float Z_MINSPEED = 1;
    float Z_NORMALSPD = 300.0;
    float TiltNormalSpeed = 115;
    float TiltMinSpeed = 1;
    float TiltDistanceSteps = 60000;


    float ZDelays[4];        // ZRaise (Init,Sub)  ZLower (Init,Sub)
    float TiltDelays[4];     // TRaise (Init,Sub)  TLower (Init,Sub)

    int LoadConfigs(void);
    void SaveLicense(void);
    void PrintLicenseInfo();
    void PrintMachineConfig();
    void PrintMotionConfig(MotionConfig mConf);
    void PrintMatConfig(int iIndex);
    int sendPrintProgress(const char *buf, int size, int currentSlice, int totalSlice);

    bool SetMotionConfig(MotionConfig mConfig, int iLayer);
    void EnableIntensity(int Status);
    void ProjectorOnOff(int Status);
    void ConnectToProjector();
    void GoHome(void);
    void Prepare(void);
    void GoPos(int iPos);
    void MovePos(int iMM);
    void MoveTilt(int TiltStatus);
    void MoveDoor(int DoorStatus) ;
    void ShowPattern(int patindex);
    void MaterialTest(int value,int iPat);
    void ChangeFrame(int layerno, bool ShiftImage, __Job3D *jobData);
    void MeasureDelays(MotionConfig mConf, MaterialConfig materialConfig);
    void MeasureMechanicalPeriod(MotionConfig mConf, MaterialConfig materialConfig);
    float TotalTimeMotion(float TotalLayer, MotionConfig mConf);
    float RemainingTimeTimer(float CurrentLayer, float TotalLayer, MotionConfig mConf,int TimerValueMsec);
    float RemainingTimeMotion(float CurrentLayer , float TotalLayer, MotionConfig mConf);
    float TotalTimeMaterial(MaterialConfig mConf, float TotalLayer);
    float RemainingTimeMaterial(MaterialConfig mConfig,float CurrentLayer,float TotalLayer);
    bool LayerHandler(int iLayer, MaterialConfig materialConf, __Job3D *jobData, MotionConfig motionConf);
    void SetMatConfig(MaterialConfig materialConf,int iLayer);
    float InterPolation(int X1,int X2, float Y1,float Y2,int iLayer);
    void SetPixelSize();
    int CheckLicense();     // 1 = ok    2 = Wrong Name   3 = License

    float ReadDistanceSensor();
    void MoveRecoater(int RecoaterStatus);     //1 = front 0 = back
    bool MaterialLevel(float Distance,float Threshold,bool UsePlunger);   // keeps material within Distance+-Threshold
    void PristalticState(int type);   // 2 = Steady State  1 = Add   0 = Remove

    void FillVacuum(float timer,float SensorSetPointVacuum);
    void VacuumState(int type);      // 2 = Steady State  1 = Add   0 = Remove


    int start();
    void printStart(MaterialConfig materialConfig, MotionConfig motionConfig, __Job3D job);
    int ExportSVGToMem(__Job3D *jobinfo, int iSlice, int ImageCX, int ImageCY, float fPixelSize,
                       unsigned int BkgColor, char *OutBuffer,float X_Shift,float Y_Shift);
    int ExportBlackSVGToMem(int ImageCX, int ImageCY, unsigned int BkgColor, char *OutBuffer);
    void ArduinoTimerSlot();

    bool hasermToggle = true;
    bool ermCommand = true;
    int jobFrameSize = 0;
    bool imageToggle = true;
    QImage *maskImage ;
    QString addMaskToImage(QString img);
    QString setBlack(QString img);
    void changeMachineConfig(int ModelCode);

signals:
    void changeImageView(QString imageSource); //, bool toggle
    void changeImageViewErm(QString imageSource, bool toggle, int layerNum);
    void changeFrameHandler(int layerno, bool ShiftImage, __Job3D *jobData, char *tmpImage);
    void sendQImage(QImage imageSource, QString flag);
    void toggleImageVisiblityErm();
    void imageInitializeErm();
    void setPrintImage(QImage printImage);
public slots:
    void moduleDistanceData(float d);
    void frameChanged(int jFrameSize);
    void getImageItem(QImage printImage);
    void addClientfd(int clientfd);

//    void socketReadyRead();
};

#endif // BACKEND_H
