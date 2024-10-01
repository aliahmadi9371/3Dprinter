#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include "lib/sqlite3.h"
#include "schema.h"
#include "materialconfig.h"
#include "motionconfig.h"
#include "machineconfig.h"
#include "Job.h"

using namespace std;

class DataBase
{
public:
    string dbName;
    sqlite3* DB;
    bool isOpen = false;
    DataBase() {}
    DataBase(string dbName) : dbName(dbName)  {}
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    bool openConnection();
    void closeConnection();
    bool createTable(Schema tableSchema);
    bool insert(string sql_command);
    bool update(string sql_command);
    bool remove(string sql_command);
    bool findMaterialById(string sql_command, MaterialConfig *temp);
    bool findAllMaterial(string sql_command, vector<MaterialConfig> *mConfV);
    bool findMotionById(string sql_command, MotionConfig *temp);
    bool findAllMotion(string sql_command, vector<MotionConfig> *mConfV);
    bool findJobById(string sql_command, __Job3D *temp);
    bool findAllJob(string sql_command, vector<__Job3D> *j3DV);
    bool findMachineConfigById(string sql_command, MachineConfig *temp);
    bool findAllMachineConfig(string sql_command, vector<MachineConfig> *mConfV);
};

#endif // DATABASE_H
