#include "database.h"


int DataBase::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    cout<< " database callback argc:"<< argc <<endl;
    int i;
    for(i = 0; i<argc; i++) {
        cout<<azColName[i] <<", "<< argv[i] ? argv[i] : "NULL" ;
        cout<<endl;
    }
    return 0;
}

bool DataBase::openConnection()
{
  int exit = 0;
  string str = dbName+".db";
  const char *cstr = str.c_str(); // convert string to char *
  exit = sqlite3_open_v2(cstr, &DB, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX, 0);

  if (exit != SQLITE_OK) {
          cerr << "Error Open connection" << endl;
  } else {
      isOpen = true;
      cout << dbName << " connection opened"<< endl;
      return true;
  }
}

void DataBase::closeConnection()
{
    if(isOpen) {
        sqlite3_close(DB);
        isOpen = false;
    }

}

bool DataBase::createTable(Schema tableSchema)
{
    int exit = 0;

    if(!isOpen) {return false;}

    char *zErrMsg = 0;
    string sql = "CREATE TABLE IF NOT EXISTS "+ tableSchema.tableName +" (id INTEGER PRIMARY KEY AUTOINCREMENT,"+tableSchema.sqlCommand+")";
    cout<<endl<<"createTable : " << sql << endl;
    exit = sqlite3_exec(DB, sql.c_str(), callback, 0, &zErrMsg);

      if( exit != SQLITE_OK ){
         cerr << "createTable SQL error: " << zErrMsg << ", EXIT CODE :"<< exit<< endl;
         sqlite3_free(zErrMsg);
         return false;
      } else {
         cout << tableSchema.tableName << " table created successfully" << endl;
         return true;
      }
}

bool DataBase::insert(string sql_command)
{
     cout<<"********************insert : " << endl;
    int exit = 0;
    if(DB == NULL) {cout<< "insert DB is null"<<endl;}
    if(!isOpen) {return false;}

    char *zErrMsg = 0;
    cout<<"DataBase  insert : " << sql_command << endl;
    exit = sqlite3_exec(DB, sql_command.c_str(), callback, 0, &zErrMsg);

      if( exit != SQLITE_OK ){
         cerr << "insert SQL error: " <<  ", EXIT CODE :"<< exit << endl;
         sqlite3_free(zErrMsg);
         return false;
      } else {
         cout <<  " table inserted successfully" << endl;
         return true;
      }
}

bool DataBase::update(string sql_command)
{
    int exit = 0;

    if(!isOpen) {return false;}

    char *zErrMsg = 0;
    cout<<"update : " << sql_command << endl;
    exit = sqlite3_exec(DB, sql_command.c_str(), callback, 0, &zErrMsg);

      if( exit != SQLITE_OK ){
         cerr << "update SQL error: " << zErrMsg << ", EXIT CODE :"<< exit<< endl;
         sqlite3_free(zErrMsg);
         return false;
      } else {
         cout <<  " table update successfully" << endl;
         cout <<  zErrMsg << endl;
         return true;
      }
}

bool DataBase::remove(string sql_command)
{
    int exit = 0;

    if(!isOpen) {return false;}

    char *zErrMsg = 0;
    cout<<"remove : " << sql_command << endl;
    exit = sqlite3_exec(DB, sql_command.c_str(), callback, 0, &zErrMsg);

      if( exit != SQLITE_OK ){
         cerr << "remove SQL error: " << zErrMsg<< ", EXIT CODE :"<< exit << endl;
         sqlite3_free(zErrMsg);
         return false;
      } else {
         cout <<  " row removed successfully" << endl;
         cout <<  zErrMsg << endl;
         return true;
      }
}

bool DataBase::findMotionById(string sql_command, MotionConfig *temp)
{
    int rc = 0;
    char q[999];
    sqlite3_stmt* stmt;
    int row = 0;
    int bytes;
    const unsigned char* text;
    if(DB == NULL) {cout<< "findMotionById DB is null"<<endl;}
    if(!isOpen) { cout<<"findById connection is not open";  return false;}
    sqlite3_mutex_enter(sqlite3_db_mutex(DB));
    sqlite3_prepare_v2(DB, sql_command.c_str(), -1, &stmt, 0);

    bool done = false;
    bool successfullyFinded = false;
        while (!done) {
            cout<<"findMotionById";
            rc = sqlite3_step (stmt);
            switch (rc) {
              case SQLITE_ROW:
                cout<<" SQLITE_ROW"<<endl;
                temp->id = static_cast<int>(sqlite3_column_int(stmt, 0)) ;
                temp->Name = string( reinterpret_cast<const char*>( sqlite3_column_text(stmt, 1) ) );
                temp->Layer_Z_Raise[0] = static_cast<int>(sqlite3_column_int(stmt, 2)) ;
                temp->Layer_Z_Raise[1] = static_cast<int>(sqlite3_column_int(stmt, 3)) ;
                temp->Layer_Z_Lower[0] = static_cast<int>(sqlite3_column_int(stmt, 4)) ;
                temp->Layer_Z_Lower[1] = static_cast<int>(sqlite3_column_int(stmt, 5)) ;
                temp->Layer_Tilt_Raise[0] = static_cast<int>(sqlite3_column_int(stmt, 6)) ;
                temp->Layer_Tilt_Raise[1] = static_cast<int>(sqlite3_column_int(stmt, 7)) ;
                temp->Layer_Tilt_Lower[0] = static_cast<int>(sqlite3_column_int(stmt, 8)) ;
                temp->Layer_Tilt_Lower[1] = static_cast<int>(sqlite3_column_int(stmt, 9)) ;
                temp->Layer_Overlift[0] = static_cast<int>(sqlite3_column_int(stmt, 10)) ;
                temp->Layer_Overlift[1] = static_cast<int>(sqlite3_column_int(stmt, 11)) ;
                temp->Layer_Breathe[0] = static_cast<int>(sqlite3_column_int(stmt, 12))  ;
                temp->Layer_Breathe[1] = static_cast<int>(sqlite3_column_int(stmt, 13)) ;
                temp->Layer_Settle[0] = static_cast<int>(sqlite3_column_int(stmt, 14)) ;
                temp->Layer_Settle[1] = static_cast<int>(sqlite3_column_int(stmt, 15)) ;
                temp->Layer_Tilt_Percent[0] = static_cast<int>(sqlite3_column_int(stmt, 16))  ;
                temp->Layer_Tilt_Percent[1] = static_cast<int>(sqlite3_column_int(stmt, 17)) ;
                temp->Cut_Off_Layers = static_cast<int>(sqlite3_column_int(stmt, 18))  ;
                temp->Final_OverLift = static_cast<int>(sqlite3_column_int(stmt, 19)) ;
                temp->Base_Layer_settle = static_cast<int>(sqlite3_column_int(stmt, 20)) ;

                successfullyFinded = true;

                row++;
                break;

              case SQLITE_DONE:
                cout<<" SQLITE_DONE"<<endl;
                 done = true;
                 break;

              default:
                sqlite3_finalize(stmt);
                cout<<" Failed"<<endl;
                fprintf(stderr, "Failed.\n");
                sqlite3_mutex_leave(sqlite3_db_mutex(DB));
                return false;
            }
        }

        sqlite3_finalize(stmt);
        sqlite3_mutex_leave(sqlite3_db_mutex(DB));
        return successfullyFinded;
}

bool DataBase::findAllMotion(string sql_command, vector<MotionConfig> *mConfV)
{
    int rc = 0;
    char q[999];
    sqlite3_stmt* stmt;
    int row = 0;
    int bytes;
    const unsigned char* text;
    MotionConfig mConf;
    if(DB == NULL) {cout<< "findAllMotion DB is null"<<endl;}
    if(!isOpen) { cout<<"findById connection is not open";  return false;}
    sqlite3_mutex_enter(sqlite3_db_mutex(DB));
    sqlite3_prepare_v2(DB, sql_command.c_str(), -1, &stmt, 0);

    bool done = false;
    bool successfullyFinded = false;
        while (!done) {
            printf("In select while\n");
            rc = sqlite3_step (stmt);
            switch (rc) {
              case SQLITE_ROW:
                mConf.id = static_cast<int>(sqlite3_column_int(stmt, 0)) ;
                mConf.Name = string( reinterpret_cast<const char*>( sqlite3_column_text(stmt, 1) ) );
                mConf.Layer_Z_Raise[0] = static_cast<int>(sqlite3_column_int(stmt, 2)) ;
                mConf.Layer_Z_Raise[1] = static_cast<int>(sqlite3_column_int(stmt, 3)) ;
                mConf.Layer_Z_Lower[0] = static_cast<int>(sqlite3_column_int(stmt, 4)) ;
                mConf.Layer_Z_Lower[1] = static_cast<int>(sqlite3_column_int(stmt, 5)) ;
                mConf.Layer_Tilt_Raise[0] = static_cast<int>(sqlite3_column_int(stmt, 6)) ;
                mConf.Layer_Tilt_Raise[1] = static_cast<int>(sqlite3_column_int(stmt, 7)) ;
                mConf.Layer_Tilt_Lower[0] = static_cast<int>(sqlite3_column_int(stmt, 8)) ;
                mConf.Layer_Tilt_Lower[1] = static_cast<int>(sqlite3_column_int(stmt, 9)) ;
                mConf.Layer_Overlift[0] = static_cast<int>(sqlite3_column_int(stmt, 10)) ;
                mConf.Layer_Overlift[1] = static_cast<int>(sqlite3_column_int(stmt, 11)) ;
                mConf.Layer_Breathe[0] = static_cast<int>(sqlite3_column_int(stmt, 12))  ;
                mConf.Layer_Breathe[1] = static_cast<int>(sqlite3_column_int(stmt, 13)) ;
                mConf.Layer_Settle[0] = static_cast<int>(sqlite3_column_int(stmt, 14)) ;
                mConf.Layer_Settle[1] = static_cast<int>(sqlite3_column_int(stmt, 15)) ;
                mConf.Layer_Tilt_Percent[0] = static_cast<int>(sqlite3_column_int(stmt, 16))  ;
                mConf.Layer_Tilt_Percent[1] = static_cast<int>(sqlite3_column_int(stmt, 17)) ;
                mConf.Cut_Off_Layers = static_cast<int>(sqlite3_column_int(stmt, 18))  ;
                mConf.Final_OverLift = static_cast<int>(sqlite3_column_int(stmt, 19)) ;
                mConf.Base_Layer_settle = static_cast<int>(sqlite3_column_int(stmt, 20)) ;
                mConfV->push_back(mConf);
                successfullyFinded = true;

                row++;
                break;

              case SQLITE_DONE:
                 done = true;
                 break;

              default:
                sqlite3_finalize(stmt);
                fprintf(stderr, "Failed.\n");
                sqlite3_mutex_leave(sqlite3_db_mutex(DB));
                return false;
            }
        }
        sqlite3_mutex_leave(sqlite3_db_mutex(DB));
        sqlite3_finalize(stmt);

        return successfullyFinded;
}

bool DataBase::findJobById(string sql_command, __Job3D *temp)
{
    int rc = 0;
    char q[999];
    sqlite3_stmt* stmt;
    int row = 0;
    int bytes;
    const unsigned char* text;
    if(DB == NULL) {cout<< "findJobById DB is null"<<endl;}
    if(!isOpen) { cout<<"findById connection is not open";  return false;}
    sqlite3_mutex_enter(sqlite3_db_mutex(DB));
    sqlite3_prepare_v2(DB, sql_command.c_str(), -1, &stmt, 0);

    bool done = false;
    bool successfullyFinded = false;
        while (!done) {
            cout<<"findJobById ";
            rc = sqlite3_step (stmt);
            switch (rc) {
              case SQLITE_ROW:
                cout<<"SQLITE_ROW"<<endl;
                temp->id = static_cast<int>(sqlite3_column_int(stmt, 0)) ;
                temp->Name = string( reinterpret_cast<const char*>( sqlite3_column_text(stmt, 1) ) );
                temp->Size = static_cast<int>(sqlite3_column_int(stmt, 2)) ;

                successfullyFinded = true;

                row++;
                break;

              case SQLITE_DONE:
                 done = true;
                 cout<<"SQLITE_DONE"<<endl;
                 break;

              default:
                sqlite3_finalize(stmt);
                cout<<"Failed"<<endl;
                fprintf(stderr, "Failed.\n");
                sqlite3_mutex_leave(sqlite3_db_mutex(DB));
                return false;
            }
        }

        sqlite3_finalize(stmt);
        sqlite3_mutex_leave(sqlite3_db_mutex(DB));

        return successfullyFinded;
}

bool DataBase::findAllJob(string sql_command, vector<__Job3D> *j3DV)
{
    int rc = 0;
    char q[999];
    sqlite3_stmt* stmt;
    int row = 0;
    int bytes;
    __Job3D j3D;
    const unsigned char* text;
    if(DB == NULL) {cout<< "findAllJob DB is null"<<endl;}
    if(!isOpen) { cout<<"findAllJob connection is not open";  return false;}
    sqlite3_mutex_enter(sqlite3_db_mutex(DB));
    sqlite3_prepare_v2(DB, sql_command.c_str(), -1, &stmt, 0);

    bool done = false;
    bool successfullyFinded = false;
        while (!done) {
            printf("findAllJob step one\n");
            rc = sqlite3_step (stmt);
            switch (rc) {
              case SQLITE_ROW:
                j3D.id = static_cast<int>(sqlite3_column_int(stmt, 0)) ;
                j3D.Name = string( reinterpret_cast<const char*>( sqlite3_column_text(stmt, 1) ) );
                j3D.Size = static_cast<int>(sqlite3_column_int(stmt, 2)) ;
                j3DV->push_back(j3D);
                successfullyFinded = true;
                row++;
                break;

              case SQLITE_DONE:
                 done = true;
                 break;

              default:
                fprintf(stderr, "Failed.\n");
                sqlite3_finalize(stmt);
                sqlite3_mutex_leave(sqlite3_db_mutex(DB));
                return false;
            }
        }

        sqlite3_finalize(stmt);
        sqlite3_mutex_leave(sqlite3_db_mutex(DB));

        return successfullyFinded;
}

bool DataBase::findMachineConfigById(string sql_command, MachineConfig *temp)
{
    int rc = 0;
    char q[999];
    sqlite3_stmt* stmt;
    int row = 0;
    int bytes;
    const unsigned char* text;
    if(DB == NULL) {cout<< "findMachineConfigById DB is null"<<endl;}
    if(!isOpen) { cout<<"findMachineConfigById connection is not open";  return false;}
    sqlite3_mutex_enter(sqlite3_db_mutex(DB));
    sqlite3_prepare_v2(DB, sql_command.c_str(), -1, &stmt, 0);

    bool done = false;
    bool successfullyFinded = false;
        while (!done) {
            printf("In select while\n");
            rc = sqlite3_step (stmt);
            switch (rc) {
              case SQLITE_ROW:
                temp->id = static_cast<int>(sqlite3_column_int(stmt, 0)) ;
                temp->MachineNo = string( reinterpret_cast<const char*>( sqlite3_column_text(stmt, 1) ) );
                temp->ModelCode = static_cast<int>(sqlite3_column_int(stmt, 2)) ;
                temp->gProjectWidth = static_cast<int>(sqlite3_column_int(stmt, 3)) ;
                temp->gProjectHeight = static_cast<int>(sqlite3_column_int(stmt, 4)) ;
                temp->Version = static_cast<int>(sqlite3_column_int(stmt, 5)) ;
                temp->SubVersion = static_cast<int>(sqlite3_column_int(stmt, 6)) ;
                temp->NeedLicense = static_cast<int>(sqlite3_column_int(stmt, 7)) ;
                temp->HasDoor = static_cast<int>(sqlite3_column_int(stmt, 8)) ;
                temp->HasErm = static_cast<int>(sqlite3_column_int(stmt, 9)) ;
                temp->BUpTDownConfig = static_cast<int>(sqlite3_column_int(stmt, 10)) ;
                temp->PrinterUnit = static_cast<float>(sqlite3_column_double(stmt, 11)) ;
                temp->ZUpperLimit = static_cast<int>(sqlite3_column_int(stmt, 12)) ;
                temp->ProjectorProtocol = static_cast<int>(sqlite3_column_int(stmt, 13)) ;
                temp->NoOfMaskPoints = static_cast<int>(sqlite3_column_int(stmt, 14)) ;
                temp->MaxIntensity = static_cast<int>(sqlite3_column_int(stmt, 15)) ;
                temp->MinIntensity = static_cast<int>(sqlite3_column_int(stmt, 16)) ;
                temp->MaxIntensitySensor = static_cast<int>(sqlite3_column_int(stmt, 17)) ;
                temp->MinIntensitySensor = static_cast<int>(sqlite3_column_int(stmt, 18)) ;

                temp->HasPlunger = static_cast<int>(sqlite3_column_int(stmt, 19)) ;
                temp->TDownZHomePos = static_cast<int>(sqlite3_column_int(stmt, 20)) ;
                temp->vacuumTimer = static_cast<float>(sqlite3_column_double(stmt, 21)) ;
                temp->SensorSetPointVacuum = static_cast<float>(sqlite3_column_double(stmt, 22)) ;
                temp->SensorSetPoint = static_cast<float>(sqlite3_column_double(stmt, 23)) ;
                temp->SensorThreshold = static_cast<float>(sqlite3_column_double(stmt, 24)) ;
                temp->XShift = static_cast<float>(sqlite3_column_double(stmt, 25)) ;
                temp->YShift = static_cast<float>(sqlite3_column_double(stmt, 26)) ;
                successfullyFinded = true;
                row++;
                break;

              case SQLITE_DONE:
                 done = true;
                 break;

              default:
                fprintf(stderr, "Failed.\n");
                sqlite3_finalize(stmt);
                return false;
            }
        }

        sqlite3_finalize(stmt);
        sqlite3_mutex_leave(sqlite3_db_mutex(DB));

        return successfullyFinded;
}

bool DataBase::findAllMachineConfig(string sql_command, vector<MachineConfig> *mConfV)
{
    int rc = 0;
    char q[999];
    sqlite3_stmt* stmt;
    int row = 0;
    int bytes;
    const unsigned char* text;
    MachineConfig mConf;
    if(!isOpen) { cout<<"findAllMachineConfig connection is not open";  return false;}
    if(DB == NULL) {cout<< "findAllMachineConfig DB is null"<<endl;}
    sqlite3_mutex_enter(sqlite3_db_mutex(DB));
    sqlite3_prepare_v2(DB, sql_command.c_str(), -1, &stmt, 0);

    bool done = false;
    bool successfullyFinded = false;
        while (!done) {
            printf("In select while\n");
            rc = sqlite3_step (stmt);
            switch (rc) {
              case SQLITE_ROW:
                mConf.id = static_cast<int>(sqlite3_column_int(stmt, 0)) ;
                mConf.MachineNo = string( reinterpret_cast<const char*>( sqlite3_column_text(stmt, 1) ) );
                mConf.ModelCode = static_cast<int>(sqlite3_column_int(stmt, 2)) ;
                mConf.gProjectWidth = static_cast<int>(sqlite3_column_int(stmt, 3)) ;
                mConf.gProjectHeight = static_cast<int>(sqlite3_column_int(stmt, 4)) ;
                mConf.Version = static_cast<int>(sqlite3_column_int(stmt, 5)) ;
                mConf.SubVersion = static_cast<int>(sqlite3_column_int(stmt, 6)) ;
                mConf.NeedLicense = static_cast<int>(sqlite3_column_int(stmt, 7)) ;
                mConf.HasDoor = static_cast<int>(sqlite3_column_int(stmt, 8)) ;
                mConf.HasErm = static_cast<int>(sqlite3_column_int(stmt, 9)) ;
                mConf.BUpTDownConfig = static_cast<int>(sqlite3_column_int(stmt, 10)) ;
                mConf.PrinterUnit = static_cast<float>(sqlite3_column_double(stmt, 11)) ;
                mConf.ZUpperLimit = static_cast<int>(sqlite3_column_int(stmt, 12)) ;
                mConf.ProjectorProtocol = static_cast<int>(sqlite3_column_int(stmt, 13)) ;
                mConf.NoOfMaskPoints = static_cast<int>(sqlite3_column_int(stmt, 14)) ;
                mConf.MaxIntensity = static_cast<int>(sqlite3_column_int(stmt, 15)) ;
                mConf.MinIntensity = static_cast<int>(sqlite3_column_int(stmt, 16)) ;

                mConf.MaxIntensitySensor = static_cast<int>(sqlite3_column_int(stmt, 17)) ;
                mConf.MinIntensitySensor = static_cast<int>(sqlite3_column_int(stmt, 18)) ;

                mConf.HasPlunger = static_cast<int>(sqlite3_column_int(stmt, 19)) ;
                mConf.TDownZHomePos = static_cast<int>(sqlite3_column_int(stmt, 20)) ;

                mConf.vacuumTimer = static_cast<float>(sqlite3_column_double(stmt, 21)) ;
                mConf.SensorSetPointVacuum = static_cast<float>(sqlite3_column_double(stmt, 22)) ;
                mConf.SensorSetPoint = static_cast<float>(sqlite3_column_double(stmt, 23)) ;
                mConf.SensorThreshold = static_cast<float>(sqlite3_column_double(stmt, 24)) ;
                mConf.XShift = static_cast<float>(sqlite3_column_double(stmt, 25)) ;
                mConf.YShift = static_cast<float>(sqlite3_column_double(stmt, 26)) ;
                successfullyFinded = true;
                mConfV->push_back(mConf);
                row++;
                break;

              case SQLITE_DONE:
                 done = true;
                 break;

              default:
                fprintf(stderr, "Failed.\n");
                sqlite3_mutex_leave(sqlite3_db_mutex(DB));
                return false;
            }
        }

        sqlite3_finalize(stmt);
        sqlite3_mutex_leave(sqlite3_db_mutex(DB));

        return successfullyFinded;
}

bool DataBase::findMaterialById(string sql_command, MaterialConfig *temp)
{
    int rc = 0;
    char q[999];
    sqlite3_stmt* stmt;
    int row = 0;
    int bytes;
    const unsigned char* text;
    if(DB == NULL) {cout<< "findMaterialById DB is null"<<endl;}
    if(!isOpen) { cout<<"findById connection is not open";  return false;}
    sqlite3_mutex_enter(sqlite3_db_mutex(DB));
    sqlite3_prepare_v2(DB, sql_command.c_str(), -1, &stmt, 0);

    bool done = false;
    bool successfullyFinded = false;
        while (!done) {
            cout<< "findMaterialById";
            rc = sqlite3_step (stmt);
            switch (rc) {
              case SQLITE_ROW:
                temp->id = static_cast<int>(sqlite3_column_int(stmt, 0)) ;
                temp->Name = string( reinterpret_cast<const char*>( sqlite3_column_text(stmt, 1) ) );
                temp->LayerThickness = static_cast<int>(sqlite3_column_int(stmt, 2)) ;
                temp->BurnInLayers = static_cast<int>(sqlite3_column_int(stmt, 3)) ;
                temp->BurnInCureTime = static_cast<float>(sqlite3_column_double(stmt, 4)) ;
                temp->NormalCureTime = static_cast<float>(sqlite3_column_double(stmt, 5)) ;
                temp->BurnIntensity = static_cast<float>(sqlite3_column_double(stmt, 6)) ;
                temp->Intensity = static_cast<float>(sqlite3_column_double(stmt, 7)) ;
                cout<< "SQLITE_ROW"<<endl;
                successfullyFinded = true;

                row++;
                break;

              case SQLITE_DONE:
                 cout<< "SQLITE_DONE"<<endl;
                 done = true;
                 break;

              default:
                cout<< "Failed"<<endl;
                sqlite3_finalize(stmt);
                fprintf(stderr, "Failed.\n");
                sqlite3_mutex_leave(sqlite3_db_mutex(DB));
                return false;
            }
        }

        sqlite3_finalize(stmt);
        sqlite3_mutex_leave(sqlite3_db_mutex(DB));

        return successfullyFinded;
}

bool DataBase::findAllMaterial(string sql_command, vector<MaterialConfig> *mConfV)
{
    int rc = 0;
    char q[999];
    sqlite3_stmt* stmt;
    int row = 0;
    int bytes;
    MaterialConfig mConf;
    const unsigned char* text;
    if(DB == NULL) {cout<< "findAllMaterial DB is null"<<endl;}
    if(!isOpen) { cout<<"findAllMaterial connection is not open";  return false;}

    sqlite3_mutex_enter(sqlite3_db_mutex(DB));

    sqlite3_prepare_v2(DB, sql_command.c_str(), -1, &stmt, 0);

    bool done = false;
    bool successfullyFinded = false;
        while (!done) {
            rc = sqlite3_step (stmt);
            switch (rc) {
              case SQLITE_ROW:
                mConf.id = static_cast<int>(sqlite3_column_int(stmt, 0)) ;
                mConf.Name = string( reinterpret_cast<const char*>( sqlite3_column_text(stmt, 1) ) );
                mConf.LayerThickness = static_cast<int>(sqlite3_column_int(stmt, 2)) ;
                mConf.BurnInLayers = static_cast<int>(sqlite3_column_int(stmt, 3)) ;
                mConf.BurnInCureTime = static_cast<float>(sqlite3_column_double(stmt, 4)) ;
                mConf.NormalCureTime = static_cast<float>(sqlite3_column_double(stmt, 5)) ;
                mConf.BurnIntensity = static_cast<float>(sqlite3_column_double(stmt, 6)) ;
                mConf.Intensity = static_cast<float>(sqlite3_column_double(stmt, 7)) ;
                mConfV->push_back(mConf);
                successfullyFinded = true;

                row++;
                break;

              case SQLITE_DONE:
                 done = true;
                 break;

              default:
                sqlite3_finalize(stmt);
                cout<< "findAllMaterial Failed :"<< rc<<endl;
                sqlite3_mutex_leave(sqlite3_db_mutex(DB));
                return false;
            }
        }

        sqlite3_finalize(stmt);
        sqlite3_mutex_leave(sqlite3_db_mutex(DB));

        return successfullyFinded;
}
