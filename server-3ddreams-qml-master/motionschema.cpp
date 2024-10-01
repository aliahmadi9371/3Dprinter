#include "motionschema.h"

MotionSchema::~MotionSchema()
{
//    cout<< "~MotionSchema()"<<endl;
}

string MotionSchema::getSqlInsertCommand()
{
    MyUtility u;
    string temp = "INSERT INTO "+tableName+"(Name, Layer_Z_Raise1, Layer_Z_Raise2, Layer_Z_Lower1, Layer_Z_Lower2,"+
            " Layer_Tilt_Raise1, Layer_Tilt_Raise2, Layer_Tilt_Lower1, Layer_Tilt_Lower2, Layer_Overlift1, "+
            "Layer_Overlift2, Layer_Breathe1, Layer_Breathe2, Layer_Settle1, Layer_Settle2, Layer_Tilt_Percent1,"+
            " Layer_Tilt_Percent2, Cut_Off_Layers, Final_OverLift, Base_Layer_settle) VALUES("
            +"\""+mConf.Name+"\","+u.numberToString(mConf.Layer_Z_Raise[0])+","+u.numberToString(mConf.Layer_Z_Raise[1])+","
            +u.numberToString(mConf.Layer_Z_Lower[0])+","+u.numberToString(mConf.Layer_Z_Lower[1])+","
            +u.numberToString(mConf.Layer_Tilt_Raise[0])+","+u.numberToString(mConf.Layer_Tilt_Raise[1])+","
            +u.numberToString(mConf.Layer_Tilt_Lower[0])+","+u.numberToString(mConf.Layer_Tilt_Lower[1])+","
            +u.numberToString(mConf.Layer_Overlift[0])+","+u.numberToString(mConf.Layer_Overlift[1])+","
            +u.numberToString(mConf.Layer_Breathe[0])+","+u.numberToString(mConf.Layer_Breathe[1])+","
            +u.numberToString(mConf.Layer_Settle[0])+","+u.numberToString(mConf.Layer_Settle[1])+","
            +u.numberToString(mConf.Layer_Tilt_Percent[0])+","+u.numberToString(mConf.Layer_Tilt_Percent[1])+","
            +u.numberToString(mConf.Cut_Off_Layers)+","+u.numberToString(mConf.Final_OverLift)+","+u.numberToString(mConf.Base_Layer_settle)+")";
    return temp;
}

string MotionSchema::getSqlUpdateCommand(uint16_t rowId)
{
//    rowId = rowId + 1;
    MyUtility u;
    //`UPDATE EEWConfig SET accTreshold = "`+accTreshold+`", highPass = "`+highPass+`", lowPass = "`+lowPass+`", longPoint = "`+longPoint+`", shortPoint = "`+shortPoint+`", staLtaTreshold = "`+staLtaTreshold+`", winLength = "`+winLength+`", a1 = "`+a1+`", a2 ="`+a2+`", a3="`+a3+`", a4="`+a4+`" WHERE id = 1` ;
    string temp = "UPDATE "+tableName+" SET Name=\""+mConf.Name+"\", Layer_Z_Raise1="+u.numberToString(mConf.Layer_Z_Raise[0])+
            ", Layer_Z_Raise2="+u.numberToString(mConf.Layer_Z_Raise[1])+", Layer_Z_Lower1="+u.numberToString(mConf.Layer_Z_Lower[0])+
            ", Layer_Z_Lower2="+u.numberToString(mConf.Layer_Z_Lower[1])+", Layer_Tilt_Raise1="+u.numberToString(mConf.Layer_Tilt_Raise[0])+
            ", Layer_Tilt_Raise2="+u.numberToString(mConf.Layer_Tilt_Raise[1])+", Layer_Tilt_Lower1="+u.numberToString(mConf.Layer_Tilt_Lower[0])+
            ", Layer_Tilt_Lower2="+u.numberToString(mConf.Layer_Tilt_Lower[1])+", Layer_Overlift1="+u.numberToString(mConf.Layer_Overlift[0])+
            ", Layer_Overlift2="+u.numberToString(mConf.Layer_Overlift[1])+", Layer_Breathe1="+u.numberToString(mConf.Layer_Breathe[0])+
            ", Layer_Breathe2="+u.numberToString(mConf.Layer_Breathe[1])+", Layer_Settle1="+u.numberToString(mConf.Layer_Settle[0])+
            ", Layer_Settle2="+u.numberToString(mConf.Layer_Settle[1])+", Layer_Tilt_Percent1="+u.numberToString(mConf.Layer_Tilt_Percent[0])+
            ", Layer_Tilt_Percent2="+u.numberToString(mConf.Layer_Tilt_Percent[1])+", Cut_Off_Layers="+u.numberToString(mConf.Cut_Off_Layers)+
            ", Final_OverLift="+u.numberToString(mConf.Final_OverLift)+", Base_Layer_settle="+u.numberToString(mConf.Base_Layer_settle)+
            +" WHERE id = "+u.numberToString(rowId);
    cout << "getSqlUpdateCommand :"<< temp;
    return temp;
}

string MotionSchema::getSqlRemoveCommand(uint16_t rowId)
{
//   rowId = rowId + 1;
   MyUtility u;
   string temp = "DELETE FROM "+tableName+" WHERE id="+u.numberToString(rowId);
   cout << "getSqlRemoveCommand :"<< temp;
   return temp;
}

string MotionSchema::getSqlFindById(uint16_t rowId)
{
//    rowId = rowId + 1;
   MyUtility u;
   string temp = "SELECT * FROM "+tableName+" WHERE id="+u.numberToString(rowId);
   cout << "getSqlFindById :"<< temp;
   return temp;
}

string MotionSchema::getSqlFindAll()
{
    string temp = "SELECT * FROM "+tableName;
    cout << "getSqlFindAll :"<< temp;
    return temp;
}

void MotionSchema::setMotionConfig(MotionConfig temp)
{
    mConf = temp;
}

void MotionSchema::setMotionPacket(network_messages::MotionConfig motionCmd)
{

    MotionConfig temp;
    temp.Name =  motionCmd.name() ;
    if(motionCmd.layer_settle_size() == 2) {
      temp.Layer_Settle[0] = motionCmd.layer_settle(0);
      temp.Layer_Settle[1] = motionCmd.layer_settle(1);
    } else {
     spdlog::warn("networkMessage layer_settle_size: {0:d}", motionCmd.layer_settle_size());
    }

    if(motionCmd.layer_z_raise_size() == 2) {
      temp.Layer_Z_Raise[0] = motionCmd.layer_z_raise(0);
      temp.Layer_Z_Raise[1] = motionCmd.layer_z_raise(1);
    } else {
     spdlog::warn("networkMessage layer_z_raise_size: {0:d}", motionCmd.layer_z_raise_size());
    }

    if(motionCmd.layer_tilt_raise_size() == 2) {
      temp.Layer_Tilt_Raise[0] = motionCmd.layer_tilt_raise(0);
      temp.Layer_Tilt_Raise[1] = motionCmd.layer_tilt_raise(1);
    } else {
     spdlog::warn("networkMessage layer_tilt_raise: {0:d}", motionCmd.layer_tilt_raise_size());
    }

    if(motionCmd.layer_tilt_lower_size() == 2) {
      temp.Layer_Tilt_Lower[0] = motionCmd.layer_tilt_lower(0);
      temp.Layer_Tilt_Lower[1] = motionCmd.layer_tilt_lower(1);
    } else {
     spdlog::warn("networkMessage layer_tilt_lower_size: {0:d}", motionCmd.layer_tilt_lower_size());
    }

    if(motionCmd.layer_z_lower_size() == 2) {
      temp.Layer_Z_Lower[0] = motionCmd.layer_z_lower(0);
      temp.Layer_Z_Lower[1] = motionCmd.layer_z_lower(1);
    } else {
     spdlog::warn("networkMessage layer_z_lower_size: {0:d}", motionCmd.layer_z_lower_size());
    }

    if(motionCmd.layer_overlift_size() == 2) {
      temp.Layer_Overlift[0] = motionCmd.layer_overlift(0);
      temp.Layer_Overlift[1] = motionCmd.layer_overlift(1);
    } else {
     spdlog::warn("networkMessage layer_overlift_size: {0:d}", motionCmd.layer_overlift_size());
    }

    if(motionCmd.layer_breathe_size() == 2) {
      temp.Layer_Breathe[0] = motionCmd.layer_breathe(0);
      temp.Layer_Breathe[1] = motionCmd.layer_breathe(1);
    } else {
     spdlog::warn("networkMessage layer_breathe_size: {0:d}", motionCmd.layer_breathe_size());
    }

    if(motionCmd.layer_tilt_percent_size() == 2) {
      temp.Layer_Tilt_Percent[0] = motionCmd.layer_tilt_percent(0);
      temp.Layer_Tilt_Percent[1] = motionCmd.layer_tilt_percent(1);
    } else {
     spdlog::warn("networkMessage layer_tilt_percent_size: {0:d}", motionCmd.layer_tilt_percent_size());
    }

    temp.Cut_Off_Layers = motionCmd.cut_off_layers();
    temp.Final_OverLift = motionCmd.final_overlift();
    temp.Base_Layer_settle = motionCmd.base_layer_settle();
    temp.id = motionCmd.rowid();

    setMotionConfig(temp);
}
