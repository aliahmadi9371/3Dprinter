#ifndef FRAMEHANDLER_H
#define FRAMEHANDLER_H

#include <QObject>
#include <QString>
#include <iostream>
#include "Job.h"
//#include "Configs/Configs.h"

using namespace std;


struct MachineConfigFile2 {
      unsigned int ModelCode;
      unsigned int gProjectWidth;
      unsigned int gProjectHeight;
      char  MachineNo[32];
      char  Version;
      char  SubVersion;
      char  NeedLicense;  // 0 = NO
      char  HasDoor;  // 0 = NO
      char  HasErm;  // 0 = NO
      char  BUpTDownConfig;  // 0 = Bottom Up (DLP)      1 = Top Down (SLA)
      float PrinterUnit;  // 1.25
      unsigned int ZUpperLimit;
      unsigned int ProjectorProtocol;
      unsigned int NoOfMaskPoints;
      unsigned int MaxIntensity;
      unsigned int MinIntensity;
      unsigned int MaxIntensitySensor;
      unsigned int MinIntensitySensor;
};

class FrameHandler : public QObject
{
    Q_OBJECT
public:
    explicit FrameHandler(QObject *parent = nullptr);
    MachineConfigFile2 *machine_cfg = new MachineConfigFile2();
    int LoadConfigs();
//    char *tmpImage = new char[3840*512];
    bool hasermToggle = true;
    float fPixelSize = 75.0*0.001;
    void SetPixelSize();
    int ExportSVGToMem(__Job3D *jobinfo, int iSlice, int ImageCX, int ImageCY, float fPixelSize,
                       unsigned int BkgColor, char *OutBuffer,float X_Shift,float Y_Shift);

    int ExportBlackSVGToMem(int ImageCX, int ImageCY, unsigned int BkgColor, char *OutBuffer);
public slots:
    void ChangeFrame(int layerno, bool ShiftImage, __Job3D *jobData, char *tmpImage);
signals:
    void changeImageView(QString imageSource);
    void changeImageViewErm(QString imageSource, bool toggle);
    void frameChanged(int jFrameSize);

};

#endif // FRAMEHANDLER_H
