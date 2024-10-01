#include "machineconfigschema.h"

string MachineConfigSchema::getSqlInsertCommand()
{

    MyUtility u;
    string temp = "INSERT INTO "+tableName+"(MachineNo, ModelCode, gProjectWidth, gProjectHeight, Version, SubVersion, NeedLicense"+
            ", HasDoor, HasErm, BUpTDownConfig, PrinterUnit, ZUpperLimit, ProjectorProtocol, NoOfMaskPoints, MaxIntensity, MinIntensity, MaxIntensitySensor, MinIntensitySensor,"
            "HasPlunger, TDownZHomePos, vacuumTimer,SensorSetPointVacuum, SensorSetPoint,SensorThreshold,XShift,YShift) VALUES("
            +"\""+mConf.MachineNo+"\","+u.numberToString(mConf.ModelCode)+","+u.numberToString(mConf.gProjectWidth)
            +","+u.numberToString(mConf.gProjectHeight)+","+u.numberToString(mConf.Version)+","
            +u.numberToString(mConf.SubVersion)+","+u.numberToString(mConf.NeedLicense)+","+u.numberToString(mConf.HasDoor)+","
            +u.numberToString(mConf.HasErm)+","+u.numberToString(mConf.BUpTDownConfig)+","+u.numberToString(mConf.PrinterUnit)+","
            +u.numberToString(mConf.ZUpperLimit)+","+u.numberToString(mConf.ProjectorProtocol)+","+u.numberToString(mConf.NoOfMaskPoints)+","
            +u.numberToString(mConf.MaxIntensity)+","+u.numberToString(mConf.MinIntensity)+","
            +u.numberToString(mConf.MaxIntensitySensor)+","+u.numberToString(mConf.MinIntensitySensor)+","
            +u.numberToString(mConf.HasPlunger)+","+u.numberToString(mConf.TDownZHomePos)+","
            +u.numberToString(mConf.vacuumTimer)+","+u.numberToString(mConf.SensorSetPointVacuum)+","
            +u.numberToString(mConf.SensorSetPoint)+","+u.numberToString(mConf.SensorThreshold)+","
            +u.numberToString(mConf.XShift)+","+u.numberToString(mConf.YShift)+")";
    return temp;
}

string MachineConfigSchema::getSqlUpdateCommand(uint16_t rowId)
{
//    rowId = rowId + 1;
    MyUtility u;
    //`UPDATE EEWConfig SET accTreshold = "`+accTreshold+`", highPass = "`+highPass+`", lowPass = "`+lowPass+`", longPoint = "`+longPoint+`", shortPoint = "`+shortPoint+`", staLtaTreshold = "`+staLtaTreshold+`", winLength = "`+winLength+`", a1 = "`+a1+`", a2 ="`+a2+`", a3="`+a3+`", a4="`+a4+`" WHERE id = 1` ;
    string temp = "UPDATE "+tableName+" SET MachineNo=\""+mConf.MachineNo+"\", ModelCode="+u.numberToString(mConf.ModelCode)+
            ", gProjectWidth="+u.numberToString(mConf.gProjectWidth)+", gProjectHeight="+u.numberToString(mConf.gProjectHeight)+
            ", Version="+u.numberToString(mConf.Version)+", SubVersion="+u.numberToString(mConf.SubVersion)+
            ", NeedLicense="+u.numberToString(mConf.NeedLicense)+", HasDoor="+u.numberToString(mConf.HasDoor)+
            ", HasErm="+u.numberToString(mConf.HasErm)+", BUpTDownConfig="+u.numberToString(mConf.BUpTDownConfig)+
            ", PrinterUnit="+u.numberToString(mConf.PrinterUnit)+", ZUpperLimit="+u.numberToString(mConf.ZUpperLimit)+
            ", ProjectorProtocol="+u.numberToString(mConf.ProjectorProtocol)+", NoOfMaskPoints="+u.numberToString(mConf.NoOfMaskPoints)+
            ", MaxIntensity="+u.numberToString(mConf.MaxIntensity)+", MinIntensity="+u.numberToString(mConf.MinIntensity)+
            ", MaxIntensitySensor="+u.numberToString(mConf.MaxIntensitySensor)+", MinIntensitySensor="+u.numberToString(mConf.MinIntensitySensor)+
            ", HasPlunger="+u.numberToString(mConf.HasPlunger)+", TDownZHomePos="+u.numberToString(mConf.TDownZHomePos)+
            ", vacuumTimer="+u.numberToString(mConf.vacuumTimer)+", SensorSetPointVacuum="+u.numberToString(mConf.SensorSetPointVacuum)+
            ", SensorSetPoint="+u.numberToString(mConf.SensorSetPoint)+", SensorThreshold="+u.numberToString(mConf.SensorThreshold)+
            ", XShift="+u.numberToString(mConf.XShift)+", YShift="+u.numberToString(mConf.YShift)+
            +" WHERE id = "+u.numberToString(rowId);
    cout << "getSqlUpdateCommand :"<< temp<<endl;
    return temp;
}

string MachineConfigSchema::getSqlRemoveCommand(uint16_t rowId)
{
//   rowId = rowId + 1;
   MyUtility u;
   string temp = "DELETE FROM "+tableName+" WHERE id="+u.numberToString(rowId);
   cout << "getSqlRemoveCommand :"<< temp;
   return temp;
}

string MachineConfigSchema::getSqlFindById(uint16_t rowId)
{
//    rowId = rowId + 1;
   MyUtility u;
   string temp = "SELECT * FROM "+tableName+" WHERE id="+u.numberToString(rowId);
   cout << "getSqlFindById :"<< temp;
   return temp;
}

string MachineConfigSchema::getSqlFindByModelCode(uint32_t rowId)
{
    MyUtility u;
    string temp = "SELECT * FROM "+tableName+" WHERE ModelCode="+u.numberToString(rowId);
    cout << "getSqlFindById :"<< temp;
    return temp;
}

string MachineConfigSchema::getSqlFindAll()
{
    string temp = "SELECT * FROM "+tableName;
    cout << "getSqlFindAll :"<< temp;
    return temp;
}

void MachineConfigSchema::setMachineConfig(MachineConfig temp)
{
    mConf = temp;
}

void MachineConfigSchema::setMachinePacket(network_messages::MachineConfig mCmd)
{
    MachineConfig temp;
    temp.HasErm = mCmd.haserm();
    temp.HasDoor = mCmd.hasdoor();
    temp.Version = mCmd.version() ;
    temp.MachineNo = mCmd.machineno();
    temp.ModelCode = mCmd.modelcode();
    temp.SubVersion = mCmd.subversion();
    temp.NeedLicense = mCmd.needlicense();
    temp.PrinterUnit = mCmd.printerunit();
    temp.ZUpperLimit = mCmd.zupperlimit();
    temp.MaxIntensity = mCmd.maxintensity();
    temp.MinIntensity = mCmd.minintensity();

    temp.MaxIntensitySensor = mCmd.maxintensitysensor();
    temp.MinIntensitySensor = mCmd.minintensitysensor();

    temp.gProjectWidth = mCmd.gprojectwidth();
    temp.BUpTDownConfig = mCmd.buptdownconfig();
    temp.NoOfMaskPoints = mCmd.noofmaskpoints();
    temp.gProjectHeight = mCmd.gprojectheight();
    temp.ProjectorProtocol = mCmd.projectorprotocol();

    temp.HasPlunger = mCmd.hasplunger();
    temp.TDownZHomePos = mCmd.tdownzhomepos();
    temp.vacuumTimer = mCmd.vacuumtimer();
    temp.SensorSetPointVacuum = mCmd.sensorsetpointvacuum();
    temp.SensorSetPoint = mCmd.sensorsetpoint();
    temp.SensorThreshold = mCmd.sensorthreshold();
    temp.XShift = mCmd.xshift();
    temp.YShift = mCmd.yshift();

    setMachineConfig(temp);
}
