#include "iostream"

using namespace std;

#define MAXMATERIALS 24
#define MAXMOTIONS   12


struct MachineConfigFile {
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


struct MaterialConfigFile {
      char   Name[10];
      unsigned int LayerThickness;
      unsigned int BurnInLayers;
      float BurnInCureTime;
      float NormalCureTime;
      float BurnIntensity;
      float Intensity;
};


struct MotionConfigFile {
      char   Name[11];
      unsigned int Layer_Z_Raise[2];
      unsigned int Layer_Z_Lower[2];
      unsigned int Layer_Tilt_Raise[2];
      unsigned int Layer_Tilt_Lower[2];
      unsigned int Layer_Overlift[2];
      unsigned int Layer_Breathe[2];
      unsigned int Layer_Settle[2];
      unsigned int Layer_Tilt_Percent[2];
      unsigned int Cut_Off_Layers;
      unsigned int Final_OverLift;
      unsigned int Base_Layer_settle;
};

struct License {
      char  MachineNo[32];
      unsigned int NoOfPrints;
      unsigned int NoOfFinishedPrints;
      unsigned long TotalWorkingHours;
      unsigned long RemainedWorkingSeconds;
};


