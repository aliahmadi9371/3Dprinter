#include "backend.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
    if(!QDir("Jobs").exists()) {
        QDir().mkdir("Jobs");
    }
//    signal(SIGPIPE, SIG_IGN);
    gData = jStoring.getGeneralData();
    qDebug()<< "gData.modelCode : " << gData.modelCode;
    connect(this, SIGNAL(setPrintImage(QImage)), this, SLOT(getImageItem(QImage)) );
}

bool BackEnd::isPrinting()
{
    return isPrint;
}

void BackEnd::setMutex(mutex *m)
{
    mutexProtection = m ;
}

void BackEnd::setLogger(spdlog::logger *log)
{
    logger = log;
}

void BackEnd::setDataBase(DataBase *dataBase)
{
     db = dataBase;
}

int BackEnd::writeSocket(int clientfd, const char *mBuf, int size)
{
    int sendCount = 0;
    while (size > 0) {
        int resn;
        if(size > 1024) {
//            resn = write(clientfd, mBuf+sendCount, 1024);
            resn = send( clientfd, mBuf+sendCount, 1024, MSG_NOSIGNAL );
        } else {
//            resn = write(clientfd, mBuf+sendCount, size);
            resn = send( clientfd, mBuf+sendCount, size, MSG_NOSIGNAL );
        }

      if(resn <= 0) {
          return resn;
      } else {
          sendCount = sendCount + resn;
          size = size - resn;
      }
    }
    return sendCount;
}

//////////////////////////////////////////////////////
int BackEnd::LoadConfigs()
{
    cout<< "load configs "<<endl;
    int retval = 0;
    MachineConfigSchema mSchema;
    db->findMachineConfigById(mSchema.getSqlFindByModelCode(gData.modelCode), machine_cfg);
    FILE *file = fopen("Configs/machineconfig.bin","rb");
//    if (file == NULL)
//    {
//        cerr << "error load machine config"<<endl;
//        retval = 1;
//        return retval;
//    }
//    fread(machine_cfg,1,sizeof(MachineConfigFile),file);
    fclose(file);

     cout<< "load license"<<endl;
    file = fopen("Configs/license.bin","rb");
    if (file == NULL)
    {
        retval = 2;
        return retval;
    }
    fread(license,1,sizeof(License),file);
    fclose(file);

    return retval;
}
//////////////////////////////////////////////////////
void BackEnd::SaveLicense()
{
    FILE *file = fopen("Configs/license.bin","wb");
    fwrite(license,1,sizeof(License),file);
    fclose(file);
}
//////////////////////////////////////////////////////
void BackEnd::PrintLicenseInfo()
{
    cout<<endl;
    cout<<endl;
    cout<<"=================License Info================= \n"<<endl;
    cout<<"MachineNo-------------------"<<license->MachineNo<<endl;
    cout<<"NoOfPrints------------------"<<license->NoOfPrints<<endl;
    cout<<"NoOfFinishedPrints----------"<<license->NoOfFinishedPrints<<endl;
    cout<<"TotalWorkingHours-----------"<<license->TotalWorkingHours<<endl;
    cout<<"RemainedWorkingSeconds------"<<license->RemainedWorkingSeconds<<endl;
    cout<<"=================License Info================= "<<endl;
    cout<<endl;
    cout<<endl;
}
//////////////////////////////////////////////////////
void BackEnd::PrintMachineConfig()
{
    cout<<endl;
    cout<<endl;
    cout<<"=================Machine Configuration================= \n"<<endl;
    cout<<"ModelCode-------------"<<machine_cfg->ModelCode<<endl;
    cout<<"MachineNo-------------"<<machine_cfg->MachineNo<<endl;
    cout<<"gProjectWidth---------"<<machine_cfg->gProjectWidth<<endl;
    cout<<"gProjectHeight--------"<<machine_cfg->gProjectHeight<<endl;
    cout<<"Version---------------"<<machine_cfg->Version<<endl;
    cout<<"SubVersion------------"<<machine_cfg->SubVersion<<endl;
    cout<<"NeedLicense-----------"<<machine_cfg->NeedLicense<<endl;
    cout<<"HasDoor---------------"<<+machine_cfg->HasDoor<<endl;
    cout<<"HasErm----------------"<<+machine_cfg->HasErm<<endl;
    cout<<"BUpTDownConfig--------"<<machine_cfg->BUpTDownConfig<<endl;
    cout<<"NoOfMaskPoints--------"<<machine_cfg->NoOfMaskPoints<<endl;
    cout<<"PrinterUnit-----------"<<machine_cfg->PrinterUnit<<endl;
    cout<<"ZUpperLimit-----------"<<machine_cfg->ZUpperLimit<<endl;
    cout<<"ProjectorProtocol-----"<<machine_cfg->ProjectorProtocol<<endl;
    cout<<"NoOfMaskPoints--------"<<machine_cfg->NoOfMaskPoints<<endl;
    cout<<"MaxIntensity----------"<<machine_cfg->MaxIntensity<<endl;
    cout<<"MinIntensity----------"<<machine_cfg->MinIntensity<<endl;
    cout<<"MaxIntensitySensor----"<<machine_cfg->MaxIntensitySensor<<endl;
    cout<<"MinIntensitySensor----"<<machine_cfg->MinIntensitySensor<<endl;

    if (machine_cfg->BUpTDownConfig)
    {
        cout<<"TDownZHomePos-------"<<machine_cfg->TDownZHomePos<<endl;
        cout<<"vacuumTimer--------"<<machine_cfg->vacuumTimer<<endl;
        cout<<"SensorSetPntVacuum--"<<machine_cfg->SensorSetPointVacuum<<endl;
        cout<<"SensorSetPoint------"<<machine_cfg->SensorSetPoint<<endl;
        cout<<"SensorThreshold-----"<<machine_cfg->SensorThreshold<<endl;
        cout<<"HasPlunger----------"<<machine_cfg->HasPlunger<<endl;
        cout<<"XShift--------------"<<machine_cfg->XShift<<endl;
        cout<<"YShift--------------"<<machine_cfg->YShift<<endl;
    }
    cout<<"=================Machine Configuration================= "<<endl;
    cout<<endl;
    cout<<endl;
}

void BackEnd::PrintMotionConfig(MotionConfig mConf)
{
    cout<< "********** Motion Config **********"<<endl;
    cout<< "mConf.Name :"<< mConf.Name << endl;
    cout<< "mConf.Layer_Settle :"<< mConf.Layer_Settle[0] <<", "<< mConf.Layer_Settle[1] << endl;
    cout<< "mConf.Layer_Breathe :"<< mConf.Layer_Breathe[0] <<", "<< mConf.Layer_Breathe[1] << endl;
    cout<< "mConf.Layer_Z_Lower :"<< mConf.Layer_Z_Lower[0] <<", "<< mConf.Layer_Z_Lower[1] << endl;
    cout<< "mConf.Layer_Z_Raise :"<< mConf.Layer_Z_Raise[0] <<", "<< mConf.Layer_Z_Raise[1] << endl;
    cout<< "mConf.Layer_Overlift :"<< mConf.Layer_Overlift[0] <<", "<< mConf.Layer_Overlift[1] << endl;
    cout<< "mConf.Layer_Tilt_Lower :"<< mConf.Layer_Tilt_Lower[0] <<", "<< mConf.Layer_Tilt_Lower[1] << endl;
    cout<< "mConf.Layer_Tilt_Raise :"<< mConf.Layer_Tilt_Raise[0] <<", "<< mConf.Layer_Tilt_Raise[1] << endl;
    cout<< "mConf.Layer_Tilt_Percent :"<< mConf.Layer_Tilt_Percent[0] <<", "<< mConf.Layer_Tilt_Percent[1] << endl;
    cout<< "mConf.Cut_Off_Layers :"<< mConf.Cut_Off_Layers<< endl;
    cout<< "mConf.Final_OverLift :"<< mConf.Final_OverLift<< endl;
    cout<< "mConf.Base_Layer_settle :"<< mConf.Base_Layer_settle << endl;
    cout<< "=======================================" << endl;
}


//////////////////////////////////////////////////////
void BackEnd::PrintMatConfig(int iIndex)
{

}


//////////////////////////////////////////////////////
int BackEnd::sendPrintProgress(const char *buf, int size, int currentSlice, int totalSlice)
{
    logger->info("sendPrintProgress {0:d}",clientsfd.size() );
    network_messages::NetClientRes netMsg;
    netMsg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Progress);
    netMsg.set_currentslice(currentSlice);
    netMsg.set_totalslice(totalSlice);
    netMsg.set_remaining_time(sys_status.RemainedTime);
    netMsg.set_size(size);
    size_t sizeMsg = netMsg.ByteSizeLong();
    char mBuf[sizeMsg+1];

    netMsg.SerializeToArray(mBuf+1, sizeMsg);
    char bytes[ sizeof(sizeMsg)];
    std::copy(static_cast<const char*>(static_cast<const void*>(&sizeMsg)),
              static_cast<const char*>(static_cast<const void*>(&sizeMsg)) + sizeof sizeMsg,
              bytes);
    mBuf[0] = bytes[0];

    for(int i=0; i<clientsfd.size(); i++) {
        logger->info("sendPrintProgress i: {0:d}", i);
        int rcv = writeSocket(clientsfd[i], mBuf, sizeMsg+1 );
        if(rcv <= 0) {
            logger->error("sendPrintProgress header size: {0:d}", rcv);
            clientsfd.erase(clientsfd.begin() + i);
            i=i-1;
        } else {
            rcv = writeSocket(clientsfd[i], buf, size );
           if(rcv <= 0) {
             logger->error("sendPrintProgress image size: {0:d}", rcv);
             clientsfd.erase(clientsfd.begin() + i);
             i=i-1;
           }
        }
    }

    return 0;
}

////////////////////////////////////////////////////////
//bool BackEnd::GetSelMotion(MotionConfig mConfig, int iLayer)
//{
//    bool PassedInitialLayer = false;
//    int indxlayer = 0;
//    if (iLayer >= mConfig.Cut_Off_Layers)
//    {
//        indxlayer = 1;
//        PassedInitialLayer = true;
//    }
//    ZRaiseSpeed = mConfig.Layer_Z_Raise[indxlayer];
//    ZLowerSpeed = mConfig.Layer_Z_Lower[indxlayer];
//    TiltRaiseSpeed = mConfig.Layer_Tilt_Raise[indxlayer];
//    TiltLowerSpeed = mConfig.Layer_Tilt_Lower[indxlayer];
//    TiltPercent = mConfig.Layer_Tilt_Percent[indxlayer];
//    OverliftLayers = mConfig.Layer_Overlift[indxlayer]*1000.0/machine_cfg->PrinterUnit;;
//    sBreatheMs = mConfig.Layer_Breathe[indxlayer]*1000;
//    FinalOverLiftLayers = mConfig.Final_OverLift*1000.0/machine_cfg->PrinterUnit;
//    sSettleMs = mConfig.Layer_Settle[indxlayer]*1000;

//    return PassedInitialLayer;
//}

//////////////////////////////////////////////////////
bool BackEnd::SetMotionConfig(MotionConfig mConfig, int iLayer)
{
    bool PassedInitialLayer = false;
    int iBufferLayers = 20;

    if (iLayer >= mConfig.Cut_Off_Layers+iBufferLayers)
    {

        ZRaiseSpeed = mConfig.Layer_Z_Raise[1];
        ZLowerSpeed = mConfig.Layer_Z_Lower[1];
        TiltRaiseSpeed = mConfig.Layer_Tilt_Raise[1];
        TiltLowerSpeed = mConfig.Layer_Tilt_Lower[1];
        TiltPercent = mConfig.Layer_Tilt_Percent[1];
        OverliftLayers = mConfig.Layer_Overlift[1]*1000.0/machine_cfg->PrinterUnit;;
        sBreatheMs = mConfig.Layer_Breathe[1]*1000;
        FinalOverLiftLayers = mConfig.Final_OverLift*1000.0/machine_cfg->PrinterUnit;
        sSettleMs = mConfig.Layer_Settle[1]*1000;
        PassedInitialLayer = true;

    }else if (iLayer >= mConfig.Cut_Off_Layers)
    {

        int X1 = mConfig.Cut_Off_Layers;
        int X2 = X1 + iBufferLayers;

        ZRaiseSpeed = InterPolation(X1, X2, mConfig.Layer_Z_Raise[0],mConfig.Layer_Z_Raise[1],iLayer+1);
        ZLowerSpeed = InterPolation(X1, X2, mConfig.Layer_Z_Lower[0],mConfig.Layer_Z_Lower[1],iLayer+1);
        TiltRaiseSpeed = InterPolation(X1, X2, mConfig.Layer_Tilt_Raise[0],mConfig.Layer_Tilt_Raise[1],iLayer+1);
        TiltLowerSpeed = InterPolation(X1, X2, mConfig.Layer_Tilt_Lower[0],mConfig.Layer_Tilt_Lower[1],iLayer+1);

        TiltPercent = mConfig.Layer_Tilt_Percent[1];
        OverliftLayers = mConfig.Layer_Overlift[1]*1000.0/machine_cfg->PrinterUnit;;
        sBreatheMs = mConfig.Layer_Breathe[1]*1000;
        FinalOverLiftLayers = mConfig.Final_OverLift*1000.0/machine_cfg->PrinterUnit;
        sSettleMs = mConfig.Layer_Settle[1]*1000;

    }else {

        ZRaiseSpeed = mConfig.Layer_Z_Raise[0];
        ZLowerSpeed = mConfig.Layer_Z_Lower[0];
        TiltRaiseSpeed = mConfig.Layer_Tilt_Raise[0];
        TiltLowerSpeed = mConfig.Layer_Tilt_Lower[0];
        TiltPercent = mConfig.Layer_Tilt_Percent[0];
        OverliftLayers = mConfig.Layer_Overlift[0]*1000.0/machine_cfg->PrinterUnit;;
        sBreatheMs = mConfig.Layer_Breathe[0]*1000;
        FinalOverLiftLayers = mConfig.Final_OverLift*1000.0/machine_cfg->PrinterUnit;
        sSettleMs = mConfig.Layer_Settle[0]*1000;

    }
    return PassedInitialLayer;
}
//////////////////////////////////////////////////////
void BackEnd::EnableIntensity(int Status)
{
    if (machine_cfg->ModelCode == 1280){
        projectorRS232.Shutter(Status);
    }else{
        projectorCOMM.EnableIntensity(Status);
    }
}
//////////////////////////////////////////////////////
void BackEnd::ProjectorOnOff(int Status)
{
    if (machine_cfg->ModelCode == 1280){
        projectorRS232.PONOF(Status);
        if(Status)
        {
            usleep(1000*1000);
            projectorRS232.Shutter(0);
            int TimeOut = 0;
            while (!projectorRS232.POW()&&TimeOut == 10)
            {
                usleep(1000*1000);
                TimeOut++;

                if(TimeOut==20)
                {
                    cout<<"Failed to turn on Projector with RS232"<<endl;
                    break;
                }
            }
            projectorRS232.Shutter(0);
        }
    } else {
        projectorCOMM.ProjectorOnOff(Status);
    }
}
//////////////////////////////////////////////////////
void BackEnd::ConnectToProjector()
{
    projectorCOMM.SetIntensityMinMax(machine_cfg->MinIntensity,machine_cfg->MaxIntensity,machine_cfg->MinIntensitySensor,machine_cfg->MaxIntensitySensor);

    if (machine_cfg->ModelCode == 1280){
        cout<<"Projector COMM is RS232"<<endl;
        projectorRS232.Connect("/dev/ttyUSB0");

    }else if(machine_cfg->ModelCode == 1675){

        cout<<"Projector COMM is HID"<<endl;
        projectorCOMM.ConnectToProjector(machine_cfg->ModelCode);

    }else if(machine_cfg->ModelCode == 2150 || machine_cfg->ModelCode==21100 || machine_cfg->ModelCode==2162){

        cout<<"Projector COMM is I2C 4k"<<endl;
        projectorCOMM.ConnectToProjector(machine_cfg->ModelCode);
        projectorCOMM.ReadProjectorMask(0xA0000,"project_mask.png");

    }else if (machine_cfg->ModelCode == 1075)
    {
        cout<<"Projector COMM is I2C 1080p"<<endl;
        projectorCOMM.ConnectToProjector(machine_cfg->ModelCode);
        projectorCOMM.ProjectorOnOff(1);
        projectorCOMM.ReadProjectorMask(0x10000,"project_mask.png");
        projectorCOMM.ProjectorOnOff(0);

    }else if (machine_cfg->ModelCode == 21100)
    {
        cout<<"Projector COMM is I2C 4k"<<endl;
        projectorCOMM.ConnectToProjector(machine_cfg->ModelCode);
        projectorCOMM.ReadProjectorMask(0xA0000,"project_mask.png");
    }

    maskImage = new QImage("./project_mask.png" );
    *maskImage = maskImage->convertToFormat(QImage::Format_Indexed8);
    qDebug() << "ConnectToProjector Mask width:"<<maskImage->width()<<", height:"<<maskImage->height();
}
//////////////////////////////////////////////////////
void BackEnd::FillVacuum(float timer,float SensorSetPointVacuum)
{
    logger->info("vacuuming and Filling Recoater");

    MaterialLevel(SensorSetPoint-SensorSetPointVacuum,SensorThreshold,false);
    VacuumState(1);
    usleep(timer*1000000);
    VacuumState(2);

    logger->info("vacuuming and Filling Done");
}

//////////////////////////////////////////////////////
void BackEnd::VacuumState(int type)
{
    arduino.SendMessage('V',type);
}

//////////////////////////////////////////////////////
bool BackEnd::MaterialLevel(float Distance,float Threshold,bool UsePlunger)
{
    int iterration = 0;
    float DistanceSensor = -1;
    bool SuccessfullyLeveled = false;
    while (iterration<20)
    {
//        float DistanceSensor = ReadDistanceSensor();
        DistanceSensor= dModule->readData();
        logger->info("BackEnd::moduleDistanceData : {0:f}", DistanceSensor);

        printf("\n");
        printf("\n");
        printf("================================== \n");
        printf("iterration : %d\n",iterration);
        printf("================================== \n");
        printf("\n");
        printf("\n");


        if (DistanceSensor == -1)
        {
            iterration++;
            PristalticState(2);
            printf("iterration failed : %d" , iterration);
            usleep(500*1000);
        }else{
            if (DistanceSensor-Distance>Threshold)
            {
                printf("\n");
                printf("\n");
                printf("================================== \n");
                printf("Filling \n");
                printf("================================== \n");
                printf("\n");
                printf("\n");

                if (UsePlunger && HasPlunger){
                    PristalticState(4);
                }else{
                    PristalticState(1);
                }

                while(true)
                {
//                    usleep(5*1000);
                    DistanceSensor= dModule->readData();
                    logger->info("BackEnd::moduleDistanceData : {0:f}", DistanceSensor);

    //                printf("DistanceSensor : %f\n",DistanceSensor-Distance);

//                    if (DistanceSensor-Distance<=0){
                    if (DistanceSensor-Distance<Threshold){

                        printf("\n");
                        printf("\n");
                        printf("================================== \n");
                        printf("Filling Done");
                        printf("================================== \n");
                        printf("\n");
                        printf("\n");
                        PristalticState(2);


                        break;
                    }
                }
            }else if (DistanceSensor-Distance<-Threshold)
            {
                printf("\n");
                printf("\n");
                printf("================================== \n");
                printf("Depleting \n");
                printf("================================== \n");
                printf("\n");
                printf("\n");

                if (UsePlunger && HasPlunger){
                    PristalticState(3);
                }else{
                    PristalticState(0);
                }

                while(true)
                {
                    DistanceSensor= dModule->readData();
                    logger->info("BackEnd::moduleDistanceData : {0:f}", DistanceSensor);
//                    usleep(5*1000);

    //                printf("DistanceSensor : %f\n",DistanceSensor-Distance);

//                    if (DistanceSensor-Distance>=0){
                    if (DistanceSensor-Distance>-Threshold){
                        printf("\n");
                        printf("\n");
                        printf("================================== \n");
                        printf("Depleting Done\n");
                        printf("================================== \n");
                        printf("\n");
                        printf("\n");
                        PristalticState(2);

                        break;
                    }
                }
            }else{
                iterration++;
                printf("iterration : %d" , iterration);
                SuccessfullyLeveled = true;
            }

        }


    }

    printf("Done \n");
    return SuccessfullyLeveled;

}

//////////////////////////////////////////////////////
void BackEnd::PristalticState(int type)
{
    arduino.SendMessage('U',type);
}

//////////////////////////////////////////////////////
void BackEnd::GoHome()
{
    if (machine_cfg->BUpTDownConfig == 1)
    {
        MoveRecoater(1);
    }

    arduino.SendMessage('S',machine_cfg->ZUpperLimit);
    arduino.SendMessage('R',1);

    cout<<"Going Home 1"<<endl;


    arduino.Response();
    while(arduino.GetWorkState())
    {
        arduino.Response();
        if (bDebugMode) {
            iCurZpos = arduino.GetZoffset();
            cout<<"Working: "<<arduino.GetWorkState() <<" Z:"<< iCurZpos  <<endl;
        }

    }

    arduino.SendMessage('R',2);

    cout<<"Going Home 2"<<endl;

    arduino.Response();
    while(arduino.GetWorkState())
    {
        arduino.Response();
        if (bDebugMode)
            cout<<"Working: "<<arduino.GetWorkState()<<endl;
    }
}
//////////////////////////////////////////////////////
void BackEnd::GoPos(int iPos)
{
    arduino.SendMessage('G',iPos);

    cout<<"Going to: "<<iPos<<endl;
    // usleep(100*1000);

    arduino.Response();
    while (arduino.GetWorkState())
    {
        arduino.Response();
        if (bDebugMode)
            cout<<"Working: "<< arduino.GetWorkState()<<" , Z: "<<arduino.GetZoffset()<<endl;
    }
}
//////////////////////////////////////////////////////
void BackEnd::MovePos(int iMM)
{
    int newpos = (float)iMM*1000.0/machine_cfg->PrinterUnit;
    arduino.Response();
    iCurZpos = arduino.GetZoffset();
    arduino.SendMessage('G',iCurZpos+newpos);
    arduino.Response();
    while (arduino.GetWorkState())
    {
        arduino.Response();
        if (bDebugMode)
            cout<<"Working: "<< arduino.GetWorkState() <<" , Z: "<<arduino.GetZoffset()<<endl;
    }
}
//////////////////////////////////////////////////////
void BackEnd::MoveTilt(int TiltStatus)
{
    // TiltStatus Up=3 Dn-eject=4   Up=7 Dn=8
    if (TiltStatus==3){
        arduino.SendMessage('@',7);
    }else if (TiltStatus==2){
        arduino.SendMessage('@',8);
    }else if (TiltStatus==1){
        arduino.SendMessage('@',3);
    }else{
        arduino.SendMessage('@',4);
    }

    arduino.Response();

    while(arduino.GetWorkState() == 2)
    {
        arduino.Response();
        if (bDebugMode)
            cout<<"Tilt Status: "<<arduino.GetWorkState()<<endl;
    }
}

//////////////////////////////////////////////////////
void BackEnd::MoveDoor(int DoorStatus) // DoorStatus=0 Close  DoorStatus=1 open
{
    if (DoorStatus){
        arduino.SendMessage('@',5);
    }else{
        arduino.SendMessage('@',6);
    }

    arduino.Response();

    while (arduino.GetWorkState() == 3)
    {
        arduino.Response();
        if (bDebugMode)
            cout<<"Door Status:"<<arduino.GetWorkState()<<endl;
    }
}

//////////////////////////////////////////////////////
void BackEnd::MoveRecoater(int RecoaterStatus)
{
//    arduino.Response();
//    qDebug()<< "arduino.GetZoffset() ::::::::::::"<<arduino.GetZoffset();
    if (RecoaterStatus==1){
        arduino.SendMessage('@',3);
    }else if (RecoaterStatus==0){
        if (arduino.GetZoffset() >= TDownZHomePos)
        {
            arduino.SendMessage('@',4);
        }
    }else if (RecoaterStatus==3){
        if (arduino.GetZoffset() >= TDownZHomePos)
        {
            arduino.SendMessage('@',7);             // front
            cout<<"Recoater Front Bubble"<<endl;
        }
    }else if (RecoaterStatus==2){
        if (arduino.GetZoffset() >= TDownZHomePos)
        {
            arduino.SendMessage('@',8);            //back
            cout<<"Recoater back Bubble"<<endl;
        }
    }

    arduino.Response();
    while(arduino.GetWorkState() == 2)
    {
        arduino.Response();
        if (bDebugMode)
            cout<<"Recoater Status: "<<arduino.GetWorkState()<<endl;
    }
}
//////////////////////////////////////////////////////
void BackEnd::ShowPattern(int patindex)
{
    int len = 0;

    cout<<"gProjectWidth : "<<gProjectWidth<<endl;
    cout<<"gProjectHeight :"<<gProjectHeight<<endl;

    if (patindex > 0)
    {
        isPrint = false;
        emit changeImageView("images/black.png");
        usleep(20*1000);
        len = ExportPatternToMem(patindex, gProjectWidth, gProjectHeight, fPixelSize , 0x000000, tmpImage);  // 144.0 / (float)gProjectWidth
        QFile file ("./printImage.svg");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text) ) {
             logger->warn("ShowPattern can not open printImage.svg file");
        } else {
           file.write(tmpImage, len);
           file.close();
        }
        addMaskToImage("./printImage.svg");
//        emit changeImageView("file:/"+exePath+"/printImage.svg");
        isPrint = true;
    }
    else
    {
        emit changeImageView("images/black.png");
        isPrint = false;
    }
}
//////////////////////////////////////////////////////
void BackEnd::MaterialTest(int value, int iPat)
{
    cout<<"Material Test Message ! ...... "<<(float)value/100.0 <<" -> "<<iPat<<endl;
    ShowPattern(iPat);
    EnableIntensity(1);
    cout<<"LED ON\n"<<endl;
    usleep(value*1000.0*1000.0);
    EnableIntensity(0);
    cout<<"LED OFF\n"<<endl;
}
//////////////////////////////////////////////////////
void BackEnd::ChangeFrame(int layerno, bool ShiftImage, __Job3D *jobData)
{
    if(jobData==NULL) {
        LogInstance::Instance().error("ChangeFrame jobData is null, layerno: {0:d}", layerno);
        return;
    }

    int X_Shift = 0;
    int Y_Shift = 0;
    if (layerno <0)
    {
//        isPrint = false;
//        emit setPrintImage(QImage("./black.png"));

        setBlack("./black.svg");

    }
    else
    {
        if (ShiftImage)
        {
            if (machine_cfg->ModelCode == 1675){
                X_Shift = 0.5;
                Y_Shift = -0.5;
//                 X_Shift = 200;
//                 Y_Shift = -200;
            }else{
                X_Shift = -0.5;
                Y_Shift = 0.5;
//                X_Shift = 200;
//                Y_Shift = -200;
            }
        }

        ////////////////// we skip first 2 layers
         int  jobframelen = ExportSVGToMem(jobData, layerno+2, gProjectWidth, gProjectHeight, fPixelSize, 0x000000, tmpImage, X_Shift, Y_Shift); // 144.0 / (float)gProjectWidth
//        cout<<" ChangeFrame layerno:" << layerno<<endl;
         logger->info(" ChangeFrame layerno: {0:d}", layerno);
         logger->info(" ChangeFrame jobframelen: {0:d}", jobframelen);

//         char svgName[256];

//         sprintf(svgName, "./Layers/%s%d.svg", "TimedOut",layerno);

//         ExportFrameToSVG(jobData, layerno+2, gProjectWidth, gProjectHeight, fPixelSize, svgName);

         isPrint = true;
//         string temp = "data:image/svg+xml;utf8,"+ string(tmpImage);
         QFile fileTemp("./print_image.svg");
         if(fileTemp.open(QIODevice::WriteOnly)) {
             fileTemp.write(tmpImage);
             fileTemp.waitForBytesWritten(2000);
             fileTemp.close();
         } else {
            qDebug()<< "can not open file";
         }
         QString imagePath = addMaskToImage("./print_image.svg"); // QString::fromStdString(temp)
//         if (machine_cfg->HasErm) {
//             logger->info("Change frame render image HasErm");
////             emit changeImageViewErm(imagePath, hasermToggle, layerno); // QString::fromStdString(temp)
//             hasermToggle = !hasermToggle;
//         } else {
//             imageToggle = !imageToggle;
//             logger->info("Change frame render image");
////             emit changeImageView(imagePath); //, imageToggle  imagePath QString::fromStdString(temp)
//         }

       if ( !ShiftImage ) {
           sendPrintProgress(tmpImage, jobframelen, layerno, TotalLayers);
       }

//        sendPrintProgress(temp.c_str(), temp.size(), layerno, TotalLayers);
//        sendPrintProgress(imagePath.toStdString().c_str(), imagePath.toStdString().size(), layerno, TotalLayers);
       logger->info("*************************** isPrint: {0:d}", isPrint);

    }
}

QString BackEnd::getImagePreview() {
    return "file:/"+exePath+"/printImage.svg";
}

void BackEnd::setImageItem(ImageItem *item)
{
    imageItem = item;
//    cout<< "**********BackEnd::setImageItem***********"<<endl;
//    logger->info("**********BackEnd::setImageItem***********");
}
//////////////////////////////////////////////////////
void BackEnd::MeasureDelays(MotionConfig mConf, MaterialConfig materialConfig)
{
    float Init_Z_Raise = mConf.Layer_Z_Raise[0];
    float Sub_Z_Raise = mConf.Layer_Z_Raise[1];

    float Init_Z_Lower = mConf.Layer_Z_Lower[0];
    float Sub_Z_Lower = mConf.Layer_Z_Lower[1];

    float Init_Tilt_Raise = mConf.Layer_Tilt_Raise[0];
    float Sub_Tilt_Raise = mConf.Layer_Tilt_Raise[1];

    float Init_Tilt_Lower = mConf.Layer_Tilt_Lower[0];
    float Sub_Tilt_Lower = mConf.Layer_Tilt_Lower[1];



    //////////////////
    // For z, we must do *2, since each delay is for one step.
    // For Tilt, there's no need, we must correct the arduino.

    ZDelays[0] = 18750*2/(((Z_NORMALSPD-Z_MINSPEED)*(Init_Z_Raise/100.0)) + Z_MINSPEED)/1000000;
    ZDelays[1] = 18750*2/(((Z_NORMALSPD-Z_MINSPEED)*(Sub_Z_Raise/100.0)) + Z_MINSPEED)/1000000;
    ZDelays[2] = 18750*2/(((Z_NORMALSPD-Z_MINSPEED)*(Init_Z_Lower/100.0)) + Z_MINSPEED)/1000000;
    ZDelays[3] = 18750*2/(((Z_NORMALSPD-Z_MINSPEED)*(Sub_Z_Lower/100.0)) + Z_MINSPEED)/1000000;


    TiltDelays[0] = (2344*2/(((TiltNormalSpeed-TiltMinSpeed)*(Init_Tilt_Raise/100.0))+TiltMinSpeed)) / 1000000;
    TiltDelays[1] = (2344*2/(((TiltNormalSpeed-TiltMinSpeed)*(Sub_Tilt_Raise/100.0))+TiltMinSpeed)) / 1000000;
    TiltDelays[2] = (2344*2/(((TiltNormalSpeed-TiltMinSpeed)*(Init_Tilt_Lower/100.0))+TiltMinSpeed)) / 1000000;
    TiltDelays[3] = (2344*2/(((TiltNormalSpeed-TiltMinSpeed)*(Sub_Tilt_Lower/100.0))+TiltMinSpeed)) / 1000000;


    // ZStepperDelaySec+=((160/1000000)*(Sub_Z_Raise/100));   /// added fot the arduino delay (2*80)
}
//////////////////////////////////////////////////////
void BackEnd::MeasureMechanicalPeriod(MotionConfig mConf, MaterialConfig materialConfig)
{
    MeasureDelays(mConf, materialConfig);

    float LayerThicknessMicron = materialConfig.LayerThickness;


    float Init_Tilt_Percent = mConf.Layer_Tilt_Percent[0]/100.0;
    float Sub_Tilt_Percent = mConf.Layer_Tilt_Percent[1]/100.0;

    float Init_Overlift_steps = mConf.Layer_Overlift[0]*1000.0/machine_cfg->PrinterUnit;
    float Sub_Overlift_steps = mConf.Layer_Overlift[1]*1000.0/machine_cfg->PrinterUnit;


    float Init_Breathe_Sec = mConf.Layer_Breathe[0];
    float Sub_Breathe_Sec = mConf.Layer_Breathe[1];


    float Init_Settle_Sec = mConf.Layer_Settle[0];
    float Sub_Settle_Sec = mConf.Layer_Settle[1];



    //////////////////////////////
    float InitZRaiseTimeSec = (Init_Overlift_steps)*ZDelays[0];
    float SubZRaiseTimeSec = (Sub_Overlift_steps)*ZDelays[1];

    float InitZLowerTimeSec = (Init_Overlift_steps-(LayerThicknessMicron/(machine_cfg->PrinterUnit))) * ZDelays[2];
    float SubZLowerTimeSec = (Sub_Overlift_steps-(LayerThicknessMicron/(machine_cfg->PrinterUnit))) * ZDelays[3];

    /////////////////////////////////

    float InitTiltRaiseTimeSec = (TiltDistanceSteps*Init_Tilt_Percent) * TiltDelays[0];
    float SubTiltRaiseTimeSec = (TiltDistanceSteps*Sub_Tilt_Percent) * TiltDelays[1];


    float InitTiltLowerTimeSec = (TiltDistanceSteps*Init_Tilt_Percent) * TiltDelays[2];
    float SubTiltLowerTimeSec = (TiltDistanceSteps*Sub_Tilt_Percent) * TiltDelays[3];

    /////////////////////////////////////

    // float UnwantedDelays = 0.5;
    float UnwantedDelays = 0;

    OneLayerTime[0] = InitZRaiseTimeSec+InitZLowerTimeSec+InitTiltRaiseTimeSec+
                      InitTiltLowerTimeSec+Init_Breathe_Sec+Init_Settle_Sec+UnwantedDelays;



    OneLayerTime[1] = SubZRaiseTimeSec + SubZLowerTimeSec + SubTiltRaiseTimeSec +
                      SubTiltLowerTimeSec + Sub_Breathe_Sec + Sub_Settle_Sec+ UnwantedDelays;

}
//////////////////////////////////////////////////////
float BackEnd::TotalTimeMotion(float TotalLayer, MotionConfig mConf)
{
    float fCut_Off_Layers = mConf.Cut_Off_Layers;
    float TotalTimeSec;

    if (TotalLayer>fCut_Off_Layers) {
        TotalTimeSec = (fCut_Off_Layers*OneLayerTime[0])+ ((TotalLayer-fCut_Off_Layers)*OneLayerTime[1]);
    }else{
        TotalTimeSec = (TotalLayer * OneLayerTime[0]);
    }

    return TotalTimeSec;
}

//////////////////////////////////////////////////////
float BackEnd::RemainingTimeTimer(float CurrentLayer, float TotalLayer, MotionConfig mConf,int TimerValueMsec)
{
    float fCut_Off_Layers = mConf.Cut_Off_Layers;
    float RemainingTime;
    float OneLayerSec = 7;    // default value for first layers (fCut_Off_Layers+10)

    if (CurrentLayer>fCut_Off_Layers+2)  // -2 because I want to skipp the layer after cutoff (arduino config delays)
                                         // also measured value is after layer
    {
        SumOfTimer = SumOfTimer + TimerValueMsec;

        if (CurrentLayer>fCut_Off_Layers+12)  // we wait to have at least 10 data for timer +2 for first layer
        {
            OneLayerSec = (float)SumOfTimer/1000.0/(CurrentLayer-(fCut_Off_Layers+2));
        }
    }

    qDebug()<< "One Layer Sec :::::::::::::::::::::::"<<OneLayerSec;

    RemainingTime = ((TotalLayer - CurrentLayer) * OneLayerSec);

    return RemainingTime;
}

//////////////////////////////////////////////////////
float BackEnd::RemainingTimeMotion(float CurrentLayer, float TotalLayer, MotionConfig mConf)
{
    float fCut_Off_Layers = mConf.Cut_Off_Layers;
    float RemainingTime;
    if (TotalLayer>fCut_Off_Layers){
        if (CurrentLayer>fCut_Off_Layers){
            RemainingTime = ((TotalLayer - CurrentLayer) * OneLayerTime[1]);
        }else{
            RemainingTime = ((fCut_Off_Layers-CurrentLayer) * OneLayerTime[0]) + ((TotalLayer - fCut_Off_Layers) * OneLayerTime[1]);
        }
    }else{
        RemainingTime = ((TotalLayer - CurrentLayer) * OneLayerTime[0]);
    }
    return RemainingTime;
}
//////////////////////////////////////////////////////
float BackEnd::TotalTimeMaterial(MaterialConfig mConf, float TotalLayer)
{
    float fBurnInLayers = mConf.BurnInLayers;
    float fBurnInCureTime = mConf.BurnInCureTime;
    float fNormalCureTime = mConf.NormalCureTime;
    float TotalTimeSec;
    if (TotalLayer>fBurnInLayers){
        TotalTimeSec = (fBurnInLayers*fBurnInCureTime)+((TotalLayer-fBurnInLayers)*fNormalCureTime);
    }else{
        TotalTimeSec = TotalLayer*fBurnInCureTime;
    }
    return TotalTimeSec;
}
//////////////////////////////////////////////////////
float BackEnd::RemainingTimeMaterial(MaterialConfig mConfig, float CurrentLayer, float TotalLayer)
{
    float fBurnInLayers = mConfig.BurnInLayers;
    float fBurnInCureTime = mConfig.BurnInCureTime;
    float fNormalCureTime = mConfig.NormalCureTime;
    float RemainingTime;
    if (TotalLayer>fBurnInLayers){
        if (CurrentLayer>fBurnInLayers){
            RemainingTime = (TotalLayer-CurrentLayer)*fNormalCureTime;
        }else{
            RemainingTime = ((fBurnInLayers-CurrentLayer)*fBurnInCureTime)+((TotalLayer-fBurnInLayers)*fNormalCureTime);
        }
    }else{
        RemainingTime = (TotalLayer-CurrentLayer)*fBurnInCureTime;
    }
    return RemainingTime;
}



//////////////////////////////////////////////////////
void BackEnd::ArduinoTimerSlot()
{
    logger->warn("arduino Timed out");
//    arduino.SendMessage('N',NextLayer+PosOffset);
}

//////////////////////////////////////////////////////
bool BackEnd::LayerHandler(int iLayer, MaterialConfig materialConf, __Job3D *jobData, MotionConfig motionConf)
{
//    arduinoTimer = new QTimer(this);
//    connect(arduinoTimer, SIGNAL(timeout()),this, SLOT(ArduinoTimerSlot()));

//    PrintMotionConfig(motionConf);

    bool SentTwiceForTimedOut = false;
    bool StopPrint = false;
    int NoOfSteps = materialConf.LayerThickness/machine_cfg->PrinterUnit;
    int NextLayer = NoOfSteps*(iLayer+1);

    int BufferLayers = 20;

    if(!bPassBurnInLayers)
    {
        SetMatConfig(materialConf,iLayer);   // for cure time and intensity
    }



//    else
//    {
//        if (bPassBurnInLayers == 0)
//        {
//            bPassBurnInLayers = 1;
//            projectorCOMM.SetIntensitySensor(materialConf.Intensity);
//        }
//    }

    int PosOffset = 0;
    if (machine_cfg->BUpTDownConfig)
    {
         PosOffset = TDownZHomePos;
    }

    if (iLayer == 0)
    {
        arduino.SendMessage('#',0);
        ChangeFrame(-1,false, jobData);
        arduino.SendMessage('B',PosOffset);
        cout<<"PosOffset "<<PosOffset<<endl;

        bool MaterialLeveled = false;


        arduino.Response();
        while (arduino.GetWorkState() )
        {
            arduino.Response();
            iCurZpos = arduino.GetZoffset();
            if (bDebugMode)
                cout<<"Working: "<<arduino.GetWorkState()<<" , NZ Position: "<<iCurZpos <<"  "<<arduino.GetErr()<<endl;

            if (machine_cfg->BUpTDownConfig && arduino.GetWorkState() == 5 && !MaterialLeveled)
            {
                arduino.SendMessage('M',0);
                if(MaterialLevel(SensorSetPoint,SensorThreshold,false))
                {
                    arduino.SendMessage('M',1);
                    MaterialLeveled = true;
                }else{
                    arduino.SendMessage('M',1);
                    MaterialLeveled = true;
                    StopPrint = true;
                }

            }else if (machine_cfg->BUpTDownConfig && arduino.GetWorkState()== 6 && !MaterialLeveled) // We level only in front
            {
                arduino.SendMessage('M',1);
                MaterialLeveled = true;
            }
        }


        usleep(motionConf.Base_Layer_settle*1000*1000);


//        projectorCOMM.SetIntensitySensor(materialConf.BurnIntensity);
         projectorCOMM.SetIntensitySensor(Intensity);
        ChangeFrame(iLayer,false, jobData);
        EnableIntensity(1);  cout<<"[LED ON]"<<endl;
        usleep(fCureTime*1000*1000);
        EnableIntensity(0);  cout<<"[LED OFF]"<<endl;


        arduino.SendMessage('N',NextLayer+PosOffset);

        if (machine_cfg->HasErm){
            ChangeFrame(iLayer+1,false, jobData);
//            emit toggleImageVisiblityErm();
        } else {
            ChangeFrame(iLayer+1,false, jobData);
        }

        MaterialLeveled = false;

        arduino.Response();
        while (arduino.GetWorkState() )
        {
            arduino.Response();
            iCurZpos = arduino.GetZoffset();
            if (bDebugMode)
                cout<<"Working: "<<arduino.GetWorkState()<<" , NZ Position: "<<iCurZpos <<"  "<<arduino.GetErr()<<endl;

            if (machine_cfg->BUpTDownConfig && arduino.GetWorkState() == 5 && !MaterialLeveled)
            {
                arduino.SendMessage('M',0);
                MaterialLevel(SensorSetPoint,SensorThreshold,false);
                arduino.SendMessage('M',1);
                MaterialLeveled = true;
            }
        }


    }
    else if (iLayer == TotalLayers-1)
    {
        if (machine_cfg->HasErm){
            ChangeFrame(iLayer,false, jobData);

            arduino.SendMessage('#',0);
            logger->info("[LED ON]");
            EnableIntensity(1);

            usleep(fCureTime/2*1000*1000);
            ChangeFrame(iLayer,true, jobData);
            arduino.SendMessage('#',1);
            usleep(fCureTime/2*1000*1000);
            logger->info("[LED OFF]");
            EnableIntensity(0);
            ChangeFrame(-1,false, jobData);
        } else {
//            ChangeFrame(iLayer,false, jobData);
            logger->info("[LED ON]");
            EnableIntensity(1);
            usleep(fCureTime*1000*1000);
            logger->info("[LED OFF]");
            EnableIntensity(0);
            ChangeFrame(-1,false, jobData);
        }

        arduino.SendMessage('#',0);
        if (machine_cfg->BUpTDownConfig)
        {
            arduino.SendMessage('F',0);
        }else{
            arduino.SendMessage('F',NextLayer+FinalOverLiftLayers);
        }
        // while ((iCurZpos != NextLayer+FinalOverLiftLayers) || (arduino.GetWorkState() )
        while ( arduino.GetWorkState() )
        {
            arduino.Response();
            iCurZpos = arduino.GetZoffset();
            if (bDebugMode)
                cout<<"Working: "<<arduino.GetWorkState() <<" , FZ Position: "<<iCurZpos <<"  "<<arduino.GetErr()<<endl;
        }

//        if (machine_cfg->BUpTDownConfig)
//        {
//            VacuumState(0);
//            usleep(vacuumTimer*1000000);
//            VacuumState(2);
//        }

    }
    else
    {

        if (machine_cfg->HasErm){
//            ChangeFrame(iLayer,false, jobData);


            if (iLayer > materialConf.BurnInLayers+BufferLayers)
            {
                if (bPassBurnInLayers == 0)
                {
                    ChangeFrame(-1,false, jobData);
                    bPassBurnInLayers = 1;
                    projectorCOMM.SetIntensitySensor(Intensity);
                    ChangeFrame(iLayer,false, jobData);
                }

            }else if (iLayer > materialConf.BurnInLayers)   // For Buffer Layers
            {
                 ChangeFrame(-1,false, jobData);
                 bPassBurnInLayers = 1;
                 projectorCOMM.SetIntensitySensor(Intensity);
                 ChangeFrame(iLayer,false, jobData);
            }

            arduino.SendMessage('#',0);
            logger->info("HasErm [LED ON]");
            EnableIntensity(1);
            usleep(fCureTime/2*1000*1000);

            ChangeFrame(iLayer,true, jobData);
            logger->info("HasErm frame changed");
            arduino.SendMessage('#',1);
            usleep(fCureTime/2*1000*1000);
            logger->info("HasErm [LED OFF]");
            EnableIntensity(0);
            ChangeFrame(iLayer+1,false, jobData);
            arduino.SendMessage('N',NextLayer+PosOffset);
        } else {

            if (iLayer > materialConf.BurnInLayers+BufferLayers)
            {
                if (bPassBurnInLayers == 0)
                {
                    ChangeFrame(-1,false, jobData);
                    bPassBurnInLayers = 1;
                    projectorCOMM.SetIntensitySensor(Intensity);
                    ChangeFrame(iLayer,false, jobData);
                }

            }else if (iLayer > materialConf.BurnInLayers)   // For Buffer Layers
            {
                 ChangeFrame(-1,false, jobData);
                 bPassBurnInLayers = 1;
                 projectorCOMM.SetIntensitySensor(Intensity);
                 ChangeFrame(iLayer,false, jobData);
            }

            logger->info("[LED ON]");
            EnableIntensity(1);
            usleep(fCureTime*1000*1000);
            logger->info("[LED OFF]");
            EnableIntensity(0);
            arduino.SendMessage('N',NextLayer+PosOffset);
            if (iLayer == materialConf.BurnInLayers)
            {
                ChangeFrame(-1,false, jobData);    // This is for changing the intensity
            }else{
                ChangeFrame(iLayer+1,false, jobData);
            }

//            ChangeFrame(-1,false, jobData);

        }


        bool MaterialLeveled = false;

        logger->info("Layer handler before finished");
        double timeoutCounter = 0 ;

//        arduinoTimer->start(2000);
        arduino.Response();
        while (arduino.GetWorkState() )
        {
            arduino.Response();
            iCurZpos = arduino.GetZoffset();
            if (bDebugMode)
                cout<<"Working: "<<arduino.GetWorkState()<<" , NZ Position: "<<iCurZpos <<"  "<<arduino.GetErr()<<endl;

            if (machine_cfg->BUpTDownConfig && arduino.GetWorkState() == 5 && !MaterialLeveled)
            {
                arduino.SendMessage('M',0);

                usleep(2*1000*1000);
                if(MaterialLevel(SensorSetPoint,SensorThreshold,false))
                {
                    arduino.SendMessage('M',1);
                    MaterialLeveled = true;
                }else{
                    arduino.SendMessage('M',1);
                    MaterialLeveled = true;
                    StopPrint = true;
                }
            }else if (machine_cfg->BUpTDownConfig && arduino.GetWorkState()== 6 && !MaterialLeveled) // We level only in front
            {
                arduino.SendMessage('M',1);
                MaterialLeveled = true;
            }

            timeoutCounter = timeoutCounter + 1;    // each loop iteration is 0.151 second (151ms) (for 10 is 1.665s)
//            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if(timeoutCounter > (750) ) {
               logger->warn("arduino Time out");
               arduino.SendMessage('N',NextLayer+PosOffset);
               NoOfTimedOut ++;
               timeoutCounter=0;
            }
        }
//        arduinoTimer->stop();
        logger->info("Layer handler finished");
        logger->warn("NoOfTimedOut : {0:d}",NoOfTimedOut);
    }

    return StopPrint;
}


//////////////////////////////////////////////////////
void BackEnd::SetMatConfig(MaterialConfig materialConf,int iLayer)
{
    fCureTime = 0;
    int iBufferLayers = 20;
    if (iLayer < materialConf.BurnInLayers)
    {
        Intensity = materialConf.BurnIntensity;
        fCureTime = materialConf.BurnInCureTime;
    }else if (iLayer < materialConf.BurnInLayers+iBufferLayers)
    {
        int X1 = materialConf.BurnInLayers;
        int X2 = X1 + iBufferLayers;
        Intensity = InterPolation(X1,X2,materialConf.BurnIntensity,materialConf.Intensity,iLayer);
        fCureTime = InterPolation(X1,X2,materialConf.BurnInCureTime,materialConf.NormalCureTime,iLayer);
    }else {
        Intensity = materialConf.Intensity;
        fCureTime = materialConf.NormalCureTime;
    }
}

//////////////////////////////////////////////////////
float BackEnd::InterPolation(int X1,int X2, float Y1,float Y2,int iLayer)   // y = a(x-X1)^2+b:
{

    float b = Y1;
    float a = (Y2-Y1)/(((float)X2-(float)X1)*((float)X2-(float)X1));

    float result = a*((float)iLayer-(float)X1)+b;

    return result;
}

//////////////////////////////////////////////////////
void BackEnd::Prepare()
{
    arduino.SendMessage('W',10);
    arduino.Response();
    GoHome();

    if (machine_cfg->HasDoor)
    {
        MoveDoor(0);
    }

    if (machine_cfg->BUpTDownConfig == 1)
    {

        arduino.SendMessage('Z',80);
        GoPos(TDownZHomePos);

        FillVacuum(vacuumTimer,SensorSetPointVacuum);
        MaterialLevel(SensorSetPoint,SensorThreshold,false);

        for (int var = 0; var < 2; ++var)    //  For Bubble removal
        {
            MoveRecoater(3);      // front
            MoveRecoater(2);      // back
        }

        MaterialLevel(SensorSetPoint,SensorThreshold,false);
    }
    else
    {
        arduino.SendMessage('Z',100);
        GoPos(50000);
        arduino.SendMessage('Z',70);
        GoPos(1000);
    }

}

////////////////////////////////////////////////
void BackEnd::frameChanged(int jFrameSize)
{
    jobFrameSize = jFrameSize;
}

void BackEnd::getImageItem(QImage printImage)
{
    imageItem->setImage(printImage);
}

void BackEnd::addClientfd(int clientfd)
{
    for(size_t i=0; i< clientsfd.size(); i++) {
        if(clientsfd[i] == clientfd){
            return;
        }
    }
    clientsfd.push_back(clientfd);
}

void BackEnd::changeMachineConfig(int ModelCode) //MachineConfig mConfig,
{
    gData.modelCode = ModelCode;
    jStoring.storeGeneralData(gData);
    PrintMachineConfig();
    //    *machine_cfg = mConfig;
}


//////////////////////////////////////////
void BackEnd::moduleDistanceData(float d)
{
   dModuleData  = d;
   logger->info("BackEnd::moduleDistanceData : {0:f}", dModuleData);
}

////////////////////////////////////////
QString BackEnd::addMaskToImage(QString img)
{
    // Load your SVG
     QSvgRenderer renderer(img); // .toUtf8()

     // Prepare a QImage with desired characteritisc
     QImage *image = new QImage(gProjectWidth, gProjectHeight, QImage::Format_ARGB32); //QImage::Format_Indexed8 QImage::Format_ARGB32


     // Get QPainter that paints to the image
    QPainter painter; //(image)
    painter.begin(image);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    renderer.render(&painter);
    painter.end();
    while (painter.isActive()) {
        qDebug() << "QPainter is active";
    }
//    qDebug() << "i"
    QImage image2 = image->convertToFormat(QImage::Format_Indexed8);
//    *image = image->convertToFormat(QImage::Format_Indexed8);
    for(int i = 0; i< image->width(); i++) {
        for(int j=0; j< image->height(); j++) { //image.height()
            if(image2.pixelIndex(i,j) != 0) {
                int R1, B1, G1, R2, B2, G2;
                maskImage->pixelColor(i,j).getRgb(&R1, &G1, &B1);
                image->pixelColor(i,j).getRgb(&R2, &G2, &B2);
                QColor temp = image->pixelColor(i,j) ;
                temp.setRgb( (R2*R1/255), (G2*G1/255), (B2*B1/255)  );
                image->setPixelColor(i,j, temp );
//                image->setPixelColor(i,j, maskImage->pixelColor(i,j));
            }
        }
    }
//    qDebug()<< "setImage";
//    imageItem->setImage(*image); //image QImage("./images.png")
    emit setPrintImage(*image);
//    QByteArray bArray;
//    QBuffer buffer(&bArray);
//    buffer.open(QIODevice::WriteOnly);
//    image->save(&buffer, "png");

//    QString image_outPut("data:image/png;base64,");
//    image_outPut.append(QString::fromLatin1(bArray.toBase64().data()));
    delete image;
    return "";
//    return image_outPut;

//    if(hasermToggle) {
//        image->save("./image_print1.png");
//        delete image;
//        return "file:/"+exePath+"/image_print1.png";
//    }
//    image->save("./image_print2.png");
//    delete image;
//    return "file:/"+exePath+"/image_print2.png";
}


////////////////////////////////////////
QString BackEnd::setBlack(QString img)
{
    // Load your SVG
     QSvgRenderer renderer(img); // .toUtf8()

     // Prepare a QImage with desired characteritisc
     QImage *image = new QImage(gProjectWidth, gProjectHeight, QImage::Format_ARGB32); //QImage::Format_Indexed8 QImage::Format_ARGB32


     // Get QPainter that paints to the image
    QPainter painter; //(image)
    painter.begin(image);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    renderer.render(&painter);
    painter.end();
    while (painter.isActive()) {
        qDebug() << "QPainter is active";
    }

    emit setPrintImage(*image);

    delete image;
    return "";
}
//////////////////////////////////////////////////////
void BackEnd::SetPixelSize()
{
    if (machine_cfg->ModelCode == 2150)
    {
        cout<<"Pixel Size is 54"<<endl;
        fPixelSize = 54.0*0.001;
    }
    else if (machine_cfg->ModelCode == 1075)
    {
        cout<<"Pixel Size is 75"<<endl;
        fPixelSize = 75.0*0.001;
    }
    else if (machine_cfg->ModelCode == 2162)
    {
        cout<<"Pixel Size is 62.5"<<endl;
        fPixelSize = 62.5*0.001;
    }
    else if (machine_cfg->ModelCode == 21100)
    {
        cout<<"Pixel Size is 100"<<endl;
        fPixelSize = 100*0.001;
    }
    else if (machine_cfg->ModelCode == 1280)
    {
        cout<<"Pixel Size is 80"<<endl;
        fPixelSize = 80.0*0.001;
    }
}
//////////////////////////////////////////////////////
int BackEnd::CheckLicense()
{
    // if (machine_cfg->MachineNo != (char)license->MachineNo )

    if (machine_cfg->MachineNo == myUtility.charArrayToString(license->MachineNo) )
    {
        return 2;
    }else if(machine_cfg->NeedLicense)
    {
        if(license->RemainedWorkingSeconds/3600<=1)
            return 3;

    }
    return 1;
}

float BackEnd::ReadDistanceSensor()
{
  return 0;
}
//////////////////////////////////////////////////////
int BackEnd::start()
{
    bool RS485 = true;
    cout<<"BackEnd::start()"<<endl;

    dModule = new DistancModule();
    ArduinoPort = dModule->availablePortByVID(9025);
    if (RS485){
//        dModule->DistanceModulePort = dModule->availablePortByVID(1659);    //Mostafa Mohammadi
        dModule->DistanceModulePort = dModule->availablePortByVID(6790);
    }else{
        dModule->DistanceModulePort = dModule->availablePortByVID(1155);
    }


    FILE *file;
    int tmpval = 0;

    if (tmpval = LoadConfigs()>0)
    {
        cout<<"Config Files Not Found: "<<tmpval<<endl;
        return 0;
    }

    gProjectWidth = machine_cfg->gProjectWidth;
    gProjectHeight = machine_cfg->gProjectHeight;
    cout<<"gProjectWidth : "<<gProjectWidth<<endl;
    cout<<"gProjectHeight : "<<gProjectHeight<<endl;

    PrintMachineConfig();



    bool HasPlunger = machine_cfg->HasPlunger;
    int TDownZHomePos = machine_cfg->TDownZHomePos;
    float vacuumTimer = machine_cfg->vacuumTimer;
    float SensorSetPointVacuum = machine_cfg->SensorSetPointVacuum;
    float SensorSetPoint = machine_cfg->SensorSetPoint;
    float SensorThreshold = machine_cfg->SensorThreshold;
    float XShift = machine_cfg->XShift;
    float YShift = machine_cfg->YShift;


    net_cmds.iLicenseStatus = CheckLicense();
    sys_status.RemainedLicense = license->RemainedWorkingSeconds/3600;

    PrintLicenseInfo();

    SetPixelSize();

    net_cmds.iCalibrState = 0;
    net_cmds.iPrintState = 0;
    net_cmds.getstatus = 0;
    net_cmds.iMachineStatus = 0;


    ArduinoPort = "/dev/"+ArduinoPort;
    arduino.Connect(ArduinoPort.toLocal8Bit().data());

    if (machine_cfg->BUpTDownConfig){
        dModule->Connect();
    }
//    arduino.Connect("/dev/ttyACM0");

    ConnectToProjector();

    ////////////////////// creating black image and setting

    int  jobframelen = ExportBlackSVGToMem(gProjectWidth, gProjectHeight, 0x000000, tmpImage);

    QFile fileTemp("./black.svg");
    if(fileTemp.open(QIODevice::WriteOnly)) {
        fileTemp.write(tmpImage);
        fileTemp.waitForBytesWritten(2000);
        fileTemp.close();
    } else {
       qDebug()<< "can not open file";
    }

    setBlack("./black.svg");


    ////////////////////////////////////
    projectorCOMM.ProjectorOnOff(0);

    for (int i=0;i<20;i++)
    {
    }


    bool ReadingSensor;

    while(1)
    {
        ReadingSensor = false;

        if (net_cmds.iRenewLicense == 1)
        {
            cout<<"license activated "<<endl;
            net_cmds.iRenewLicense = 0;
            license->RemainedWorkingSeconds = 720000;
            net_cmds.iLicenseStatus = CheckLicense();
            SaveLicense();
        }
        if (net_cmds.iCalibrState == 0xffff11)
        {
            net_cmds.iCalibrState = 0;
            GoHome();
        }
        else if (net_cmds.iMachineConfig == 1)
        {
            net_cmds.iMachineConfig = 0;
            changeMachineConfig(machine_cfg->ModelCode);
        }
        else if (net_cmds.iCalibrState == 0xffff21)
        {
            net_cmds.iCalibrState = 0;
            GoPos(net_cmds.iGoPos);
        }
        else if (net_cmds.iCalibrState == 0xffff31)
        {
            net_cmds.iCalibrState = 0;
            MoveTilt(3);
        }
        else if (net_cmds.iCalibrState == 0xffff32)
        {
            net_cmds.iCalibrState = 0;
            MoveTilt(2);
        }
        else if (net_cmds.iCalibrState == 14)  //Material Fill mm
        {
            net_cmds.iCalibrState = 0;
            MaterialLevel(net_cmds.fmateriallevelmm,SensorThreshold,false);
            qDebug()<< "MaterialLevel received ::::::::::::"<<net_cmds.fmateriallevelmm;
        }
        else if (net_cmds.iCalibrState == 15)   //Vacuum Fill sec
        {
            net_cmds.iCalibrState = 0;

            qDebug()<< "ffillvacuumsec received ::::::::::::"<<net_cmds.ffillvacuumsec;

            VacuumState(1);
            usleep(net_cmds.ffillvacuumsec*1000*1000);
            VacuumState(2);

        }
        else if (net_cmds.iCalibrState == 16)   //read sensor
        {
            net_cmds.iCalibrState = 0;
            net_cmds.sensorVal = dModule->readData();
//            net_cmds.sensorVal = 5.2;
            qDebug()<< "net_cmds.sensorVal ::::::::::::"<<net_cmds.sensorVal;

        }
        else if (net_cmds.iCalibrState == 0xffff81)
        {
            net_cmds.iCalibrState = 0;
            MaterialTest(net_cmds.iGoPos,net_cmds.iMatPat);
            isPrint = false;
            emit changeImageView("images/black.png");
        }
        else if (net_cmds.iCalibrState == 0xffff91)
        {
            net_cmds.iCalibrState = 0;
            projectorCOMM.SetIntensitySensor(net_cmds.iGoPos);
        }
        else if (net_cmds.iCalibrState == 7)
        {
            net_cmds.iCalibrState = 0;
            ProjectorOnOff(1);
        }
        else if (net_cmds.iCalibrState == 8)
        {
            net_cmds.iCalibrState = 0;
            EnableIntensity(0);
            ProjectorOnOff(0);
            isPrint = false;
            emit changeImageView("images/black.png");
        }
        else if (net_cmds.iCalibrState == 20)
        {
            isPrint = false;
            emit changeImageView("images/black.png");
            net_cmds.iCalibrState = 0;
            ShowPattern(0);
            EnableIntensity(1);
        }
        else if (net_cmds.iCalibrState == 21)
        {
            isPrint = false;
            emit changeImageView("images/black.png");
            net_cmds.iCalibrState = 0;
            ShowPattern(1);
            EnableIntensity(1);
        }
        else if (net_cmds.iCalibrState == 22)
        {
            isPrint = false;
            emit changeImageView("images/black.png");
            net_cmds.iCalibrState = 0;
            ShowPattern(2);
            EnableIntensity(1);
        }
        else if (net_cmds.iCalibrState == 9)
        {
            net_cmds.iCalibrState = 0;
            EnableIntensity(0);
             ProjectorOnOff(0);
             isPrint = false;
             emit changeImageView("images/black.png");
        }
        else if (net_cmds.iCalibrState == 11)
        {
            net_cmds.iCalibrState = 0;
            EnableIntensity(1);
        }
        else if (net_cmds.iCalibrState == 12)
        {
            net_cmds.iCalibrState = 0;
            EnableIntensity(0);
        }
        else if (net_cmds.iCalibrState == 13)
        {
            isPrint = false;
            emit changeImageView("images/black.png");
            net_cmds.iCalibrState = 0;
            ShowPattern(net_cmds.iMatPat);
            EnableIntensity(1);
        }


        else if (net_cmds.iPrintState == 11)
        {

            net_cmds.iPrintState = 0;
            net_cmds.iMachineStatus = 1;
            printStart(net_cmds.materialConfig, net_cmds.motionConfig, net_cmds.job);
            net_cmds.iMachineStatus = 0;
            logger->info("printstart finished iMachineStatus: {0:d}", net_cmds.iMachineStatus );
        }
        if (net_cmds.iManualMV > 0)
        {
            if (net_cmds.iManualMV<100)
            {
                if (net_cmds.iManualMV == 13)
                {
                    if (machine_cfg->BUpTDownConfig)
                    {
                        MoveRecoater(1);
                    }else{
                        MoveTilt(1);
                    }

                    net_cmds.iManualMV = 0;
                }

                else if (net_cmds.iManualMV == 14)
                {
                    if (machine_cfg->BUpTDownConfig)
                    {
                        MoveRecoater(0);
                    }else{
                        MoveTilt(0);
                    }

                    net_cmds.iManualMV = 0;
                }

                else if (net_cmds.iManualMV == 15)
                {
                    if (machine_cfg->HasDoor)
                    {
                        MoveDoor(1);
                        net_cmds.iManualMV = 0;
                    }else if(machine_cfg->BUpTDownConfig){
                        VacuumState(1);
                        usleep(500*1000);
                        VacuumState(2);
                        net_cmds.iManualMV = 0;
                        while(net_cmds.iManualMV == 0)
                        {
                            logger->info("BackEnd::moduleDistanceData : {0:f}", dModule->readData());
                        }
                    }

                }
                else if (net_cmds.iManualMV == 16)
                {
                    if (machine_cfg->HasDoor)
                    {
                        MoveDoor(0);
                        net_cmds.iManualMV = 0;
                    }else if(machine_cfg->BUpTDownConfig){
                        VacuumState(0);
                        net_cmds.iManualMV = 0;
                    }
                }
            }
            else
            {
                if (net_cmds.iManualMV == 101)
                    tmpval = 1;
                else if (net_cmds.iManualMV == 102)
                    tmpval = -1;
                else if (net_cmds.iManualMV == 111)
                    tmpval = 10;
                else if (net_cmds.iManualMV == 112)
                    tmpval = -10;
                else if (net_cmds.iManualMV == 121)
                    tmpval = 50;
                else if (net_cmds.iManualMV == 122)
                    tmpval = -50;
                if (machine_cfg->BUpTDownConfig)
                {
                    if (tmpval==1)
                    {
                        PristalticState(1);
                        net_cmds.iManualMV = 0;
                        while(net_cmds.iManualMV == 0)
                        {
                            logger->info("BackEnd::moduleDistanceData : {0:f}", dModule->readData());
                        }
                    }else if(tmpval==-1){
                        PristalticState(0);
                        net_cmds.iManualMV = 0;
                        while(net_cmds.iManualMV == 0)
                        {
                            logger->info("BackEnd::moduleDistanceData : {0:f}", dModule->readData());
                        }
                        ReadingSensor = true;
                    }else if(tmpval==10)
                    {
                        if(HasPlunger)
                        {
                            PristalticState(4);
                            net_cmds.iManualMV = 0;
                            while(net_cmds.iManualMV == 0)
                            {
                                logger->info("BackEnd::moduleDistanceData : {0:f}", dModule->readData());
                            }
                            ReadingSensor = true;
                        }else{
                            net_cmds.iManualMV = 0;
                            while(net_cmds.iManualMV == 0)
                            {
                                logger->info("BackEnd::moduleDistanceData : {0:f}", dModule->readData());
                            }
                            ReadingSensor = true;
                        }

                    }else if(tmpval==-10){
                        if(HasPlunger)
                        {
                            PristalticState(3);
                            net_cmds.iManualMV = 0;
                            while(net_cmds.iManualMV == 0)
                            {
                                logger->info("BackEnd::moduleDistanceData : {0:f}", dModule->readData());
                            }
                            ReadingSensor = true;
                        }else{
                            net_cmds.iManualMV = 0;
                            while(net_cmds.iManualMV == 0)
                            {
                                logger->info("BackEnd::moduleDistanceData : {0:f}", dModule->readData());
                            }
                            ReadingSensor = true;
                        }
                    }else{
                        net_cmds.iManualMV = 0;
                        PristalticState(2);
                        VacuumState(2);
                    }
                }else{
                    MovePos(tmpval);  //  (mm)
                    net_cmds.iManualMV = 0;
                }
            }

//            net_cmds.iManualMV = 0;

        }
        usleep(20*1000);
    }

    arduino.Disconnect();
}

//////////////////////////////////
void BackEnd::printStart(MaterialConfig materialConfig, MotionConfig motionConfig, __Job3D job)
{
    logger->info("Start Print Loop ! ......................................... ");

    QElapsedTimer timer;

    __Job3D *jobData = new __Job3D();
    isPrint = false;
    emit changeImageView("images/black.png");

    license->NoOfPrints ++;
    sys_status.RemainedLicense = license->RemainedWorkingSeconds/3600;

    logger->info("Phase 1 ");

    string jobFilePath = "Jobs/"+job.Name+".slc";
    NumOfSlices = ImportSlcInfo( (char *)jobFilePath.c_str() ,jobData ,XShift ,YShift);
    NoOfTimedOut = 0;

    sys_status.iTotalLayers = TotalLayers = jobData->iNumSlices; // we must skipp first 2 layers in changeframe

    TotalLayers = TotalLayers-2;  // we skip first 2 layers
    sys_status.RemainedTime = RemainingTimeTimer(0, TotalLayers, motionConfig,0) + RemainingTimeMaterial(materialConfig, 0, TotalLayers-2);

//    sendPrintProgress(0, 0, 0, TotalLayers);
    cout<< "TotalLayers:"<<TotalLayers<<endl;
    if (bDebugMode)
        cout<<"slices: "<<TotalLayers<<endl;

    ChangeFrame(0,false, jobData);    // This is for Lcd Preview

    logger->info("Preparing");

    Prepare();

    logger->info("Preparing Done, turning on projector");

    ProjectorOnOff(1);

    logger->info("Turning on projector done");
//    projectorCOMM.SetIntensitySensor(materialConfig.BurnIntensity);

    logger->info("gProjectWidth : {0:d}",gProjectWidth);
    logger->info("gProjectHeight : {0:d}",gProjectHeight);


    LogInstance::Instance().info("Pahse 5 ");

    bool ArduinoMotionSet = false;
    bool HasStopped = false;

    bPassBurnInLayers = 0;
    hasermToggle = true;
    emit imageInitializeErm();

    timer.start();
    int TimerValueMsec = 0;
    for (iCurSlice=0;iCurSlice<TotalLayers;iCurSlice++) // we skip first 2 layers
    {
        timer.restart();

        sys_status.iCurentLayer = iCurSlice;
        logger->info("PrintStart iCurSlice: {0:d}",iCurSlice);
        bool PassedInitialLayer = SetMotionConfig(motionConfig, iCurSlice);

        ///////////////////////////////////////////
//        MeasureMechanicalPeriod(motionConfig, materialConfig);

        //sys_status.RemainedTime = RemainingTimeMotion(iCurSlice, TotalLayers, motionConfig) + RemainingTimeMaterial(materialConfig, iCurSlice, TotalLayers);
//        sys_status.RemainedTime = RemainingTimeTimer(iCurSlice, TotalLayers, motionConfig,TimerValueMsec) + RemainingTimeMaterial(materialConfig, iCurSlice, TotalLayers);

        sys_status.RemainedTime = RemainingTimeTimer(iCurSlice, TotalLayers, motionConfig,TimerValueMsec);

        qDebug() << "sys_status.RemainedTime :::::::::::::::::::::::::::"<<sys_status.RemainedTime;
        sys_status.TotalTime = TotalTimeMotion(TotalLayers, motionConfig) + TotalTimeMaterial(materialConfig, TotalLayers);

          if (iCurSlice==0)
          {
              arduino.SendMessage('K',ZRaiseSpeed);
              arduino.Response();
              arduino.SendMessage('L',ZLowerSpeed);
              arduino.Response();
              arduino.SendMessage('W',TiltRaiseSpeed);
              arduino.Response();
              arduino.SendMessage('X',TiltLowerSpeed);
              arduino.Response();
              arduino.SendMessage('T',TiltPercent);
              arduino.Response();
              arduino.SendMessage('J',OverliftLayers);
              arduino.Response();
              arduino.SendMessage('D',sBreatheMs);
              arduino.Response();
              arduino.SendMessage('E',sSettleMs);
              arduino.Response();
          }else if(!ArduinoMotionSet && PassedInitialLayer){

              ArduinoMotionSet = true;

              arduino.SendMessage('K',ZRaiseSpeed);
              arduino.Response();
              arduino.SendMessage('L',ZLowerSpeed);
              arduino.Response();
              arduino.SendMessage('W',TiltRaiseSpeed);
              arduino.Response();
              arduino.SendMessage('X',TiltLowerSpeed);
              arduino.Response();
              arduino.SendMessage('T',TiltPercent);
              arduino.Response();
              arduino.SendMessage('J',OverliftLayers);
              arduino.Response();
              arduino.SendMessage('D',sBreatheMs);
              arduino.Response();
              arduino.SendMessage('E',sSettleMs);
              arduino.Response();
          }

          if (net_cmds.iPrintState == 12)  // Stop Command
          {
              if (machine_cfg->BUpTDownConfig)
              {
                  arduino.SendMessage('F',0);
                  VacuumState(0);
                  usleep(vacuumTimer*1000000);
                  VacuumState(2);
              }else{
                  arduino.SendMessage('F',(materialConfig.LayerThickness/machine_cfg->PrinterUnit)*(iCurSlice+1)+FinalOverLiftLayers);
              }
              arduino.SendMessage('Z',50);
              logger->info("printStart stop print before arduino while");
              while (arduino.GetWorkState())
              {
                  arduino.Response();
                  if (bDebugMode) {
                      iCurZpos = arduino.GetZoffset();
                      cout<<"Working: "<< arduino.GetWorkState() <<" , FZ Position: "<< iCurZpos <<"  "<<arduino.GetErr();
                  }

              }
              logger->info("printStart stop print arduino while finished");
              HasStopped = true;
              break;
          }


        HasStopped = LayerHandler(iCurSlice, materialConfig, jobData, motionConfig);
        TimerValueMsec = timer.elapsed();

        qDebug() << "timer :::::::::::::::::::::::::::"<<TimerValueMsec;

        qDebug() << "///////////////////////////////////////////////////////////////////";
    }

    EnableIntensity(0);
    ProjectorOnOff(0);

    net_cmds.iMachineStatus = 0;

    if(!HasStopped)
    {
        license->TotalWorkingHours += sys_status.TotalTime/3600;
        if (machine_cfg->NeedLicense){
            license->RemainedWorkingSeconds -= sys_status.TotalTime;
        }
        license->NoOfFinishedPrints++;
    }else{
        license->TotalWorkingHours += (sys_status.TotalTime-sys_status.RemainedTime)/3600;
        if (machine_cfg->NeedLicense){
            license->RemainedWorkingSeconds -= (sys_status.TotalTime-sys_status.RemainedTime);
        }
    }
    SaveLicense();
    ChangeFrame(-1, false, jobData);

    logger->info("Print start clientsfd.size : {0:d}", clientsfd.size());
    for(int i=0; i<clientsfd.size(); i++) {
        logger->info("close clientsfd[i]: {0:d}", i);
        close(clientsfd[i]);
    }
    clientsfd.clear();

    if(jobData) {
        LogInstance::Instance().info("printStart: delete job data");
       delete jobData;
    }

    SumOfTimer = 0;

    logger->info("Finish  \r\n");
}

int BackEnd::ExportSVGToMem(__Job3D *jobinfo, int iSlice, int ImageCX, int ImageCY, float fPixelSize, unsigned int BkgColor, char *OutBuffer, float X_Shift, float Y_Shift)
{
    int aa = 0;
    int jj = 0;
    int size = 0;
    int zz = 0;
    while (aa < MAXPOINTS)
    {
        if (jobinfo->points[aa].Slice == iSlice)
            break;
        aa++;
    }

    zz = sprintf(OutBuffer+size, "<svg width='%d' height='%d'>\r\n", ImageCX, ImageCY);

    size += zz;
    zz = sprintf(OutBuffer+size, "<rect x='0' y='0' width='%d' height='%d' style='fill:#%x;stroke-width:0;' />\r\n", ImageCX, ImageCY, BkgColor);
    size += zz;
    zz = sprintf(OutBuffer+size, "<path d='");
    size += zz;


    jj = 0;
    while (jobinfo->points[aa].Slice == iSlice)
    {
        if (jobinfo->points[aa].VertNum == 0) {
            zz = sprintf(OutBuffer + size, "M%.3f %.3f ", (jobinfo->points[aa].fX*(1.0 / fPixelSize))+X_Shift, (jobinfo->points[aa].fY*(1.0 / fPixelSize))+Y_Shift);
        } else {
            zz = sprintf(OutBuffer + size, "L%.3f %.3f ", (jobinfo->points[aa].fX*(1.0 / fPixelSize))+X_Shift, (jobinfo->points[aa].fY*(1.0 / fPixelSize))+Y_Shift);
        }
        size += zz;
        aa++;
    }


    zz = sprintf(OutBuffer + size, "Z' fill='white'   />\r\n"); //fill='white' fill-opacity='0.4' fill-opacity='0.1'
    size += zz;


    zz = sprintf(OutBuffer + size, "</svg>\r\n");

    size += zz;

    return size;
}



int BackEnd::ExportBlackSVGToMem(int ImageCX, int ImageCY, unsigned int BkgColor, char *OutBuffer)
{
    int size = 0;
    int zz = 0;


    zz = sprintf(OutBuffer+size, "<svg width='%d' height='%d'>\r\n", ImageCX, ImageCY);

    size += zz;
    zz = sprintf(OutBuffer+size, "<rect x='0' y='0' width='%d' height='%d' style='fill:#%x;stroke-width:0;' />\r\n", ImageCX, ImageCY, BkgColor);
    size += zz;

    zz = sprintf(OutBuffer + size, "</svg>\r\n");
    size += zz;

    return size;
}
