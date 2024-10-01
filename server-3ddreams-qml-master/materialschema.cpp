#include "materialschema.h"



MaterialSchema::~MaterialSchema()
{
}

string MaterialSchema::getSqlInsertCommand()
{
    MyUtility u;
    string temp = "INSERT INTO "+tableName+"(Name, LayerThickness, BurnInLayers, BurnInCureTime, NormalCureTime, BurnIntensity, Intensity ) VALUES("
            +"\""+mConf.Name+"\","+u.numberToString(mConf.LayerThickness)+","+u.numberToString(mConf.BurnInLayers)
            +","+u.numberToString(mConf.BurnInCureTime)+","+u.numberToString(mConf.NormalCureTime)+","
            +u.numberToString(mConf.BurnIntensity)+","+u.numberToString(mConf.Intensity)+ ")";
    return temp;
}

string MaterialSchema::getSqlUpdateCommand(uint16_t rowId)
{
//    rowId = rowId + 1;
    MyUtility u;
    //`UPDATE EEWConfig SET accTreshold = "`+accTreshold+`", highPass = "`+highPass+`", lowPass = "`+lowPass+`", longPoint = "`+longPoint+`", shortPoint = "`+shortPoint+`", staLtaTreshold = "`+staLtaTreshold+`", winLength = "`+winLength+`", a1 = "`+a1+`", a2 ="`+a2+`", a3="`+a3+`", a4="`+a4+`" WHERE id = 1` ;
    string temp = "UPDATE "+tableName+" SET Name=\""+mConf.Name+"\", LayerThickness="+u.numberToString(mConf.LayerThickness)+
            ", BurnInLayers="+u.numberToString(mConf.BurnInLayers)+", BurnInCureTime="+u.numberToString(mConf.BurnInCureTime)+
            ", NormalCureTime="+u.numberToString(mConf.NormalCureTime)+", BurnIntensity="+u.numberToString(mConf.BurnIntensity)+
            ", Intensity="+u.numberToString(mConf.Intensity)
            +" WHERE id = "+u.numberToString(rowId);
    cout << "getSqlUpdateCommand :"<< temp;
    return temp;
}

string MaterialSchema::getSqlRemoveCommand(uint16_t rowId)
{
//   rowId = rowId + 1;
   MyUtility u;
   string temp = "DELETE FROM "+tableName+" WHERE id="+u.numberToString(rowId);
   cout << "getSqlRemoveCommand :"<< temp;
   return temp;
}

string MaterialSchema::getSqlFindById(uint16_t rowId)
{
//    rowId = rowId + 1;
   MyUtility u;
   string temp = "SELECT * FROM "+tableName+" WHERE id="+u.numberToString(rowId);
   cout << "getSqlFindById :"<< temp;
   return temp;
}

string MaterialSchema::getSqlFindAll()
{
    string temp = "SELECT * FROM "+tableName;
    cout << "getSqlFindAll :"<< temp;
    return temp;
}

void MaterialSchema::setMaterialConfig(MaterialConfig temp)
{
    mConf = temp;
}

void MaterialSchema::setMaterialPacket(network_messages::MaterialConfig materialCmd)
{
    MaterialConfig temp;
    temp.Name =  materialCmd.name() ;
    temp.Intensity = materialCmd.intensity();
    temp.BurnInLayers = materialCmd.burninlayers();
    temp.BurnIntensity = materialCmd.burnintensity();
    temp.BurnInCureTime = materialCmd.burnincuretime();
    temp.LayerThickness = materialCmd.layerthickness();
    temp.NormalCureTime = materialCmd.normalcuretime();
    setMaterialConfig(temp);
}
