#ifndef JOBMODEL_H
#define JOBMODEL_H

#include <QAbstractListModel>
#include <QDir>
#include <QTcpSocket>
#include <fstream>
#include <thread>
#include <future>
#include "assistant.h"
//#include "ImageView.h"
#include "Job.h"
#include "uimessages.h"
#include "message.pb.h"


class JobList;

class JobModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(JobList *list READ list WRITE setList )
//    Q_PROPERTY(int precentage READ getPrecentage NOTIFY pressureChanged)
public:
    explicit JobModel(QObject *parent = nullptr);
    enum {
         Name, Size
       };

       // Basic functionality:
       int rowCount(const QModelIndex &parent = QModelIndex()) const override;

       QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

       // Editable:
       bool setData(const QModelIndex &index, const QVariant &value,
                    int role = Qt::EditRole) override;

       virtual QHash<int, QByteArray> roleNames() const override;

       Qt::ItemFlags flags(const QModelIndex& index) const override;

       JobList *list() const;
       void setList(JobList *list);
       bool addElement(__Job3D item);
       bool fileCopy(string src, string dest);
       int getId(int index);
       Q_INVOKABLE int size();
       Q_INVOKABLE bool addNewJob(QString name);
       QString CopyFileHere(QString name);
       void ClearFiles();
       QString FileNameFromQmlToCpp(QString filepath);
        Q_INVOKABLE bool getUploadingState();
       bool uploding = false;
//       Q_INVOKABLE void makeNewConfig(QString cName, int cLayerThickness, int cBurnInLayers,
//                                      double cBurnInCureTime, double cNormalCureTime, double cBurnIntensity,
//                                      double cIntensity);
//       Q_INVOKABLE void removeConfig(int index);
//       Q_INVOKABLE void setConfig(int index, QString cName, int cLayerThickness, int cBurnInLayers,
//                                  double cBurnInCureTime, double cNormalCureTime, double cBurnIntensity,
//                                  double cIntensity);
       Q_INVOKABLE void updateData(QString ipAddr, QString portAddr);
       Q_INVOKABLE void refreshData();
       Q_INVOKABLE bool removeJob(int index);
       void sendJobToServer();

       QString MachineAddress;
       QString MachinePort;
       void setMachineIpPort(QString mAddress, QString mPort);
       int connectToServer();
       int disconnetFromServer();
       int clearMessages();
       network_messages::NetServerCommands *serverCmdMesg;
       network_messages::NetClientRes *serverResMesg;
       network_messages::Job3D *jobCmd;
       char filebuff[2048];

       // render image from slc file
       FILE * infile;
       FILE * outfile;
       FILE * outfileerm;

       char inbuffer[8192];

       char headertext[MAXHEADERSIZE];

       double minx = 0;
       double maxx = 0;
       double miny = 0;
       double maxy = 0;
       double minz = 0;
       double maxz = 0;
       char XBound[64];

       char YBound[64];
       char ZBound[64];
       float scalefactor = 1.0f;

       unsigned int numslices = 0;

       unsigned int numboundries = 0;
       unsigned int numvertices = 0;
       unsigned int numgaps = 0;
       unsigned int minzlevel = 0;

       __Job3D tempFileInfo;
       unsigned int ImgBkgs[5] = { 0x202020 ,0x808080 ,0xF00000 , 0xF0780A ,0x106ED2};
       char tmpImage[3840 * 2160];
//       ImageView imgView;
       int iSelcetedBkgCol;
       __Vector2 minb;
       __Vector2 maxb;


       Q_INVOKABLE void setTemporaryJob(QString fileDir) ;
       Q_INVOKABLE int getNumSlices() ;
       Q_INVOKABLE bool getTrueFile() ;
       void SetFalseFile();
       Q_INVOKABLE QString getFileName() ;
       bool imageFileNameToggle = true;
       QString exePath = QDir::currentPath();
       QString tempFilePath = "";
       QString fileName = "";
       Q_INVOKABLE QString getFrameImage(int sliceNum);

       int  ImportSlcInfo(char *SlcFileName, __Job3D *jobinfo);
       int ExportPatternToMem(int index,int ImageCX, int ImageCY, float fPixelSize, unsigned int BkgColor, char *OutBuffer);
       int  ExportFrameToSVG(__Job3D *jobinfo, int iSlice, int ImageCX, int ImageCY, float fPixelSize, const char *OutFileName);
       int  ExportFrameToMem( __Job3D *jobinfo, int iSlice, int ImageCX, int ImageCY, float fPixelSize, unsigned int BkgColor, char *OutBuffer,float X_Shift,float Y_Shift);
       void ExportSlcFileToSVG(char *SlcFileName, char *OutFileName,float fPixelSize,int img_cx,int img_cy);
       void ExportSlcFileToSVGErm(char *SlcFileName, char *OutFileName,float fPixelSize,int img_cx,int img_cy,float X_Shift,float Y_Shift);
       void ExportJobFile( __Job3D *jobinfo, char *OutFileName);
       void OpenJobFile(char *JobFileName, __Job3D *jobinfo);

       UIMessages *uiMessages;
       void setUIMessages(UIMessages *uiMsg);
//       __Job3D itemTemp;
signals:
    void sendFile(QString name);
    void sendPrecentageToQml(int precentage);
    void newJobName(QString NewName);

public slots:
    void sendFileDone();
    void sendFileError(QString message);
    void GetPrecentage(int precentage);
    void onSendTrueFile(bool ckeck);
private:
    JobList *mList;
    QTcpSocket *socket;
};

#endif // JOBMODEL_H
