#include "jobschema.h"


JobSchema::~JobSchema()
{
//    cout<< "~JobSchema()";
}

string JobSchema::getSqlInsertCommand()
{
    MyUtility u;
    string temp = "INSERT INTO "+tableName+"(Name, Size ) VALUES("
            +"\""+mConf.Name+"\","+u.numberToString(mConf.Size)+ ")";
    return temp;
}

string JobSchema::getSqlUpdateCommand(uint16_t rowId)
{
//    rowId = rowId + 1;
    MyUtility u;
    //`UPDATE EEWConfig SET accTreshold = "`+accTreshold+`", highPass = "`+highPass+`", lowPass = "`+lowPass+`", longPoint = "`+longPoint+`", shortPoint = "`+shortPoint+`", staLtaTreshold = "`+staLtaTreshold+`", winLength = "`+winLength+`", a1 = "`+a1+`", a2 ="`+a2+`", a3="`+a3+`", a4="`+a4+`" WHERE id = 1` ;
    string temp = "UPDATE "+tableName+" SET Name=\""+mConf.Name+"\", Size="+u.numberToString(mConf.Size)
            +" WHERE id = "+u.numberToString(rowId);
    cout << "getSqlUpdateCommand :"<< temp;
    return temp;
}

string JobSchema::getSqlRemoveCommand(uint16_t rowId)
{
//   rowId = rowId + 1;
   MyUtility u;
   string temp = "DELETE FROM "+tableName+" WHERE id="+u.numberToString(rowId);
   cout << "getSqlRemoveCommand :"<< temp<<endl;
   return temp;
}

string JobSchema::getSqlFindById(uint16_t rowId)
{
//    rowId = rowId + 1;
   MyUtility u;
   string temp = "SELECT * FROM "+tableName+" WHERE id="+u.numberToString(rowId);
   cout << "getSqlFindById :"<< temp<<endl;
   return temp;
}

string JobSchema::getSqlFindAll()
{
    string temp = "SELECT * FROM "+tableName;
    cout << "getSqlFindAll :"<< temp<<endl;
    return temp;
}

void JobSchema::setJob3DPacket(network_messages::Job3D jobCmd)
{
    __Job3D temp;
    temp.Name =  jobCmd.name() ;
    temp.Size = jobCmd.size();
    setJob3DConfig(temp);
}

void JobSchema::setJob3DConfig(__Job3D temp)
{
   mConf = temp;
}
