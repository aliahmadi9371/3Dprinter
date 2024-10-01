#include <stdio.h>
#include <stdlib.h>

#include "Configs.h"

MachineConfigFile  machine_cfg;
License license;
MaterialConfigFile matrial_cfg[MAXMATERIALS];
MotionConfigFile   motion_cfg[MAXMOTIONS];

//=====================================================================================================================================================
int InitConfigs(void)
{
    for (int i=0;i<MAXMATERIALS;i++)
    {
        matrial_cfg[i].Name[0] = 0;
    }
    for (int i=0;i<MAXMOTIONS;i++)
    {
        motion_cfg[i].Name[0] = 0;
    }

    machine_cfg.ModelCode = 2150; //21100; //2150; //1075; //1280
    sprintf(machine_cfg.MachineNo,"PD1675E1T19821002");
    machine_cfg.gProjectWidth = 3840;    // 3840
    machine_cfg.gProjectHeight = 2160;   // 2160
    machine_cfg.Version = 1;
    machine_cfg.SubVersion = 0;
    machine_cfg.NeedLicense = 0;  // 0 = NO
    machine_cfg.HasDoor = 0;  // 0 = NO
    machine_cfg.HasErm = 0;  // 0 = NO
    machine_cfg.BUpTDownConfig = 0; // ButtomUp
    machine_cfg.NoOfMaskPoints = 60;
    machine_cfg.PrinterUnit = 1.25;
    machine_cfg.ZUpperLimit = 82000;
    machine_cfg.ProjectorProtocol = 0;
    // machine_cfg.NoOfMaskPoints = 1;
    machine_cfg.MaxIntensity = 1000;  // 1000 810 //22000
    machine_cfg.MinIntensity = 50;    // 50   91  //200

/////License ////////////////////////////////////////////////////////////////////////////////////////////
    
    sprintf(license.MachineNo,"PD1675E1T19821002");
    license.NoOfPrints = 0;
    license.NoOfFinishedPrints = 0;
    license.TotalWorkingHours = 0;
    license.RemainedWorkingSeconds = 1440000;

/////For Beta 21625 /////////////////////////////////////////////////////////////////////////////////////
    
    // JCast
    sprintf(matrial_cfg[0].Name,"JCast");
    matrial_cfg[0].LayerThickness = 50;
    matrial_cfg[0].BurnInLayers = 5;
    matrial_cfg[0].BurnInCureTime = 15;
    matrial_cfg[0].NormalCureTime = 5;
    matrial_cfg[0].BurnIntensity = 50;
    matrial_cfg[0].Intensity = 30;

    // Cherry
    sprintf(matrial_cfg[1].Name,"Cherry");
    matrial_cfg[1].LayerThickness = 50;
    matrial_cfg[1].BurnInLayers = 15;
    matrial_cfg[1].BurnInCureTime = 15;
    matrial_cfg[1].NormalCureTime = 5;
    matrial_cfg[1].BurnIntensity = 80;
    matrial_cfg[1].Intensity = 70;

        // ITough100
    sprintf(matrial_cfg[2].Name,"ITough100");
    matrial_cfg[2].LayerThickness = 100;
    matrial_cfg[2].BurnInLayers = 15;
    matrial_cfg[2].BurnInCureTime = 6;
    matrial_cfg[2].NormalCureTime = 2;
    matrial_cfg[2].BurnIntensity = 35;
    matrial_cfg[2].Intensity = 25;

    //  // ITough2100
    // sprintf(matrial_cfg[3].Name,"ITough200");
    // matrial_cfg[3].LayerThickness = 100;
    // matrial_cfg[3].BurnInLayers = 15;
    // matrial_cfg[3].BurnInCureTime = 5;
    // matrial_cfg[3].NormalCureTime = 2;
    // matrial_cfg[3].BurnIntensity = 30;
    // matrial_cfg[3].Intensity = 30;

    // // Tough50
    // sprintf(matrial_cfg[4].Name,"Tough50");
    // matrial_cfg[4].LayerThickness = 50;
    // matrial_cfg[4].BurnInLayers = 15;
    // matrial_cfg[4].BurnInCureTime = 6;
    // matrial_cfg[4].NormalCureTime = 2;
    // matrial_cfg[4].BurnIntensity = 25;
    // matrial_cfg[4].Intensity = 25;


    // // Epic1075
    // sprintf(matrial_cfg[5].Name,"Epic1075");
    // matrial_cfg[5].LayerThickness = 50;
    // matrial_cfg[5].BurnInLayers = 15;
    // matrial_cfg[5].BurnInCureTime = 20;
    // matrial_cfg[5].NormalCureTime = 6;
    // matrial_cfg[5].BurnIntensity = 80;
    // matrial_cfg[5].Intensity = 70;





    // // Green LT
    // sprintf(matrial_cfg[3].Name,"Green LT");
    // matrial_cfg[3].LayerThickness = 50;
    // matrial_cfg[3].BurnInLayers = 15;
    // matrial_cfg[3].BurnInCureTime = 6;
    // matrial_cfg[3].NormalCureTime = 2;
    // matrial_cfg[3].BurnIntensity = 50;
    // matrial_cfg[3].Intensity = 50;


    // // Flexible
    // sprintf(matrial_cfg[4].Name,"Flexible");
    // matrial_cfg[4].LayerThickness = 100;
    // matrial_cfg[4].BurnInLayers = 5;
    // matrial_cfg[4].BurnInCureTime = 6;
    // matrial_cfg[4].NormalCureTime = 2;
    // matrial_cfg[4].BurnIntensity = 25;
    // matrial_cfg[4].Intensity = 25;

    // // DigiCast 100
    // sprintf(matrial_cfg[5].Name,"DigiC50");
    // matrial_cfg[5].LayerThickness = 50;
    // matrial_cfg[5].BurnInLayers = 15;
    // matrial_cfg[5].BurnInCureTime = 20;
    // matrial_cfg[5].NormalCureTime = 5;
    // matrial_cfg[5].BurnIntensity = 80;
    // matrial_cfg[5].Intensity = 70;


    // // Flash Grey
    // sprintf(matrial_cfg[6].Name,"FlashGrey");
    // matrial_cfg[6].LayerThickness = 100;
    // matrial_cfg[6].BurnInLayers = 15;
    // matrial_cfg[6].BurnInCureTime = 6;
    // matrial_cfg[6].NormalCureTime = 2;
    // matrial_cfg[6].BurnIntensity = 50;
    // matrial_cfg[6].Intensity = 30;




    // // 1065
    // sprintf(matrial_cfg[8].Name,"1065");
    // matrial_cfg[8].LayerThickness = 100;
    // matrial_cfg[8].BurnInLayers = 15;
    // matrial_cfg[8].BurnInCureTime = 5;
    // matrial_cfg[8].NormalCureTime = 1.5;
    // matrial_cfg[8].BurnIntensity = 30;
    // matrial_cfg[8].Intensity = 20;






    // // 205-100
    // sprintf(matrial_cfg[3].Name,"205-100");
    // matrial_cfg[3].LayerThickness = 100;
    // matrial_cfg[3].BurnInLayers = 20;
    // matrial_cfg[3].BurnInCureTime = 7;
    // matrial_cfg[3].NormalCureTime = 1.5;
    // matrial_cfg[3].BurnIntensity = 60;
    // matrial_cfg[3].Intensity = 60;

    // // 205-50
    // sprintf(matrial_cfg[4].Name,"205-50");
    // matrial_cfg[4].LayerThickness = 50;
    // matrial_cfg[4].BurnInLayers = 20;
    // matrial_cfg[4].BurnInCureTime = 7;
    // matrial_cfg[4].NormalCureTime = 1.5;
    // matrial_cfg[4].BurnIntensity = 60;
    // matrial_cfg[4].Intensity = 50;


    // Motion Semi-fast
    sprintf(motion_cfg[0].Name,"Semi-fast");
    motion_cfg[0].Cut_Off_Layers = 20;
    motion_cfg[0].Final_OverLift = 70;
    motion_cfg[0].Base_Layer_settle = 20;

    motion_cfg[0].Layer_Z_Raise[0] = 3;
    motion_cfg[0].Layer_Z_Raise[1] = 40;

    motion_cfg[0].Layer_Z_Lower[0] = 5;
    motion_cfg[0].Layer_Z_Lower[1] = 5;

    motion_cfg[0].Layer_Tilt_Raise[0] = 12;
    motion_cfg[0].Layer_Tilt_Raise[1] = 80;

    motion_cfg[0].Layer_Tilt_Lower[0] = 12;
    motion_cfg[0].Layer_Tilt_Lower[1] = 25;

    motion_cfg[0].Layer_Tilt_Percent[0] = 50;
    motion_cfg[0].Layer_Tilt_Percent[1] = 50;

    motion_cfg[0].Layer_Overlift[0] = 3;
    motion_cfg[0].Layer_Overlift[1] = 1;

    motion_cfg[0].Layer_Breathe[0] = 0;
    motion_cfg[0].Layer_Breathe[1] = 0;

    motion_cfg[0].Layer_Settle[0] = 5;
    motion_cfg[0].Layer_Settle[1] = 2;

    // Motion Test 
      sprintf(motion_cfg[1].Name,"Test");
    motion_cfg[1].Cut_Off_Layers = 5;
    motion_cfg[1].Final_OverLift = 10;
    motion_cfg[1].Base_Layer_settle = 0;

    motion_cfg[1].Layer_Z_Raise[0] = 100;
    motion_cfg[1].Layer_Z_Raise[1] = 100;

    motion_cfg[1].Layer_Z_Lower[0] = 100;
    motion_cfg[1].Layer_Z_Lower[1] = 100;

    motion_cfg[1].Layer_Tilt_Raise[0] = 100;
    motion_cfg[1].Layer_Tilt_Raise[1] = 100;

    motion_cfg[1].Layer_Tilt_Lower[0] = 100;
    motion_cfg[1].Layer_Tilt_Lower[1] = 100;

    motion_cfg[1].Layer_Tilt_Percent[0] = 70;
    motion_cfg[1].Layer_Tilt_Percent[1] = 10;

    motion_cfg[1].Layer_Overlift[0] = 3;
    motion_cfg[1].Layer_Overlift[1] = 1;

    motion_cfg[1].Layer_Breathe[0] = 0;
    motion_cfg[1].Layer_Breathe[1] = 0;

    motion_cfg[1].Layer_Settle[0] = 0;
    motion_cfg[1].Layer_Settle[1] = 0;

    FILE *file = fopen("machineconfig.bin","wb");
    fwrite(&machine_cfg,1,sizeof(MachineConfigFile),file);
    fclose(file);

    file = fopen("license.bin","wb");
    fwrite(&license,1,sizeof(license),file);
    fclose(file);

    file = fopen("mtrlconfig.bin","wb");
    fwrite(matrial_cfg,1,sizeof(MaterialConfigFile)*MAXMATERIALS,file);
    fclose(file);

    file = fopen("motnconfig.bin","wb");
    fwrite(motion_cfg,1,sizeof(MotionConfigFile)*MAXMOTIONS,file);
    fclose(file);

    return 0;
}


//=====================================================================================================================================================
int main(int argc, char *argv[])
{
    InitConfigs();

    return 0;
}
