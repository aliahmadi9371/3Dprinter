#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QTcpSocket>
#include "materialconfigmodel.h"
#include "motionconfigmodel.h"
#include "jobmodel.h"
#include "machineconfigmodel.h"
#include <QTimer>
#include <fstream>
#include <QQueue>
#include "assistant.h"
#include "uimessages.h"
#include "sendfile.h"
#include "jsonstoring.h"

class BackEnd: public QObject
{
    Q_OBJECT
public:
    explicit BackEnd(QObject *parent = nullptr);
    JsonStoring jStoring;
    GeneralData gData;
    Q_INVOKABLE QString getIpAddress();
#ifdef linux
    int osType = 0;
#endif

#ifdef _WIN32
    int osType = 1;
#endif
    Q_INVOKABLE int getOsType();
    MaterialConfigModel *materialConfigModel = NULL;
    MotionConfigModel *motionConfigModel  = NULL;
    JobModel *jobModel = NULL;
    MachineConfigModel *machineConfigModel = NULL;
    SendFile *sendFile = NULL;
    // for socket
    Q_INVOKABLE bool connectToThis(QString Address,QString Port);
    QTcpSocket *socket;
    QString MachineAddress;
    QString MachinePort;
    int connectToServer();
    int disconnetFromServer();
    int clearMessages();
    network_messages::NetServerCommands *serverCmdMesg;
    network_messages::NetClientRes *serverResMesg;
    // manual movement
    Q_INVOKABLE bool manualMV(int mvDevice, int moveStep);
    // calibrate
    Q_INVOKABLE bool startProjectorCalib();
    Q_INVOKABLE bool finishProjectorCalib();
    Q_INVOKABLE bool turnOffProjectorCalib();
    Q_INVOKABLE bool goHomeProjectorCalib();
    Q_INVOKABLE bool ledTurnOnProjectorCalib();
    Q_INVOKABLE bool ledTurnOffProjectorCalib();
    Q_INVOKABLE bool ejectUpProjectorCalib();
    Q_INVOKABLE bool ejectDownProjectorCalib();
    Q_INVOKABLE bool materialLevelProjectorCalib(float position);
    Q_INVOKABLE bool fillVacuumProjectorCalib(float position);
    Q_INVOKABLE float getSensorProjectorCalib();
    Q_INVOKABLE bool goPositionProjectorCalib(int position);
    Q_INVOKABLE bool ledIntensityProjectorCalib(int position);
    Q_INVOKABLE bool materialTestProjectorCalib(int position, int matPat);
    Q_INVOKABLE bool setPattern(int matPat);
    bool projectorCalib(int packetCode, int value1, int value2,float value3);
    // pritnt
    bool printCMD(int packetCode, int materialId, int motionId, int jobFileId);
    Q_INVOKABLE bool stopPrint();
    Q_INVOKABLE bool pausePrint();
    Q_INVOKABLE bool startPrint(int materialIndex, int motionIndex, int jobFileIndex);
    Q_INVOKABLE QString getImagePreview();
    Q_INVOKABLE int getPrintProgress();
    Q_INVOKABLE int getRemainingTime();
    Q_INVOKABLE int getPrintCurrentSlice();
    Q_INVOKABLE int getPrintTotalSlice();
    Q_INVOKABLE bool isLastPrintFile();
    Q_INVOKABLE int getServerState(); // add it in timer
    int currentSlice = 0;
    int totalSlice = 0;
    int remainingTime = 0;
    float sensorVal = -1;
    QString imagePriview = "";
    QString exePath = QDir::currentPath();
    QByteArray fileBuf;
    bool imageFileNameToggle = true;
    bool isPrinting = false;
    bool isGettingFile = false;
    bool isLastPrintingImage = false;
    uint32_t fileSizeCounter = 0;
    uint32_t fileSize = 0;
    float printingProgress = 0;
    QByteArray mesgBuf;
    int messageState = 0;
    uint16_t messageSize = 0;
    void prinitngMessageHandler();
    QString printImage = "";

    QTimer *timer;
    QFile *file;
    QFile preImgFile;
    int counter = 0;
    Q_INVOKABLE int getZoonQuantity();
    Q_INVOKABLE int getZoonValue(int zoonNum);
    Q_INVOKABLE bool setZoonValue(int zoonNum, int zoonValue);
    // message
    QQueue<QString> messages;
    Q_INVOKABLE QString getMessage();

    UIMessages *uiMessages;
    void setUIMessages(UIMessages *uiMsg);


    bool lcd = false;
    bool topDown = false;
    bool bShowConfig = false;

    Q_INVOKABLE bool isTopDown();
    Q_INVOKABLE bool isLcd();
    Q_INVOKABLE bool showConfig();



signals:
    void changeImageView(QString imageSource); //, bool toggle
public slots:
    void socketReadyRead();
    void socketDisconnected();
    void selectedFile(QString path);

};

#endif // BACKEND_H
