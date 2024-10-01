#ifndef SENDFILE_H
#define SENDFILE_H
#include <QObject>
#include <QTcpSocket>
#include <fstream>
#include "assistant.h"
#include "uimessages.h"
#include "message.pb.h"
#include <QCryptographicHash>
#include <QFile>

class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QObject *parent = nullptr);
    QString MachineAddress;
    QString MachinePort;
    QTcpSocket *socket;
    void setMachineIpPort(QString mAddress, QString mPort);
    int connectToServer();
    int disconnetFromServer();
    int clearMessages();
    network_messages::NetServerCommands *serverCmdMesg;
    network_messages::NetClientRes *serverResMesg;
    network_messages::Job3D *jobCmd;
    char filebuff[2048];
    UIMessages *uiMessages;
    void setUIMessages(UIMessages *uiMsg);

    QByteArray fileChecksum(QString fileName, QCryptographicHash::Algorithm hashAlgorithm);
    QByteArray CurrentfileCheckSum;

    void SetTcpConnectionSignalSlot(bool connect);
    void Md5SendGet();
    void SendMd5Results();
    bool ResMd5;
    bool ResMd5Check;



public slots:
    void sendFile(QString jobName);


    void TcpOnReadyRead();
signals:
    void sendFileCompleted();
    void sendFileError(QString message);
    void SendPrecentage(int progress);

    void SendTrueFile(bool check);

};

#endif // SENDFILE_H
