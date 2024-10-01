#ifndef MACHINECONFIG_H
#define MACHINECONFIG_H

#include <iostream>
#include <string>

using namespace std;

struct MachineConfig {
      unsigned int ModelCode = 2162;
      unsigned int gProjectWidth = 3840;
      unsigned int gProjectHeight = 2160;
      string  MachineNo = "PD2162E0T10000001";
      unsigned int  Version = 1;
      unsigned int  SubVersion = 0;
      bool  NeedLicense = false;  // 0 = NO
      bool  HasDoor = true;  // 0 = NO
      bool  HasErm = false;  // 0 = NO
      bool  BUpTDownConfig = false;  // 0 = Bottom Up (DLP)      1 = Top Down (SLA)
      float PrinterUnit = 1.25;  // 1.25
      unsigned int ZUpperLimit = 140000;
      unsigned int ProjectorProtocol = 0;
      unsigned int NoOfMaskPoints = 60;
      unsigned int MaxIntensity = 1000; // 1000 810 22000
      unsigned int MinIntensity = 50; // 50 91 200

      unsigned int MaxIntensitySensor = 7450; // 7450 810 22000
      unsigned int MinIntensitySensor = 350; // 350   91 200

      bool HasPlunger = false;
      unsigned int TDownZHomePos = 40400;//40200;  //37900
      float vacuumTimer = 1.3;//40; //Sec
      float SensorSetPointVacuum = 0.35;//0.6; //mm
      float SensorSetPoint = 1.1; //3.1; //mm   //16.4
      float SensorThreshold = 0.003; //mm
      float XShift = 0; // 2.025;
      float YShift = 0;

      uint16_t id;
};




#endif // MACHINECONFIG_H
