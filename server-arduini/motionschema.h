#ifndef MOTIONSCHEMA_H
#define MOTIONSCHEMA_H
#include "message.pb.h"
#include "schema.h"
#include "myutility.h"
#include "motionconfig.h"
#include "spdlog/spdlog.h"

class MotionSchema : public Schema
{
public:
    MotionSchema() : Schema("Motion") {
        addColumn("Name", "TEXT", "Name");
        addColumn("Layer_Z_Raise1", "INTEGER", "0");
        addColumn("Layer_Z_Raise2", "INTEGER", "0");
        addColumn("Layer_Z_Lower1", "INTEGER", "0");
        addColumn("Layer_Z_Lower2", "INTEGER", "0");
        addColumn("Layer_Tilt_Raise1", "INTEGER", "0");
        addColumn("Layer_Tilt_Raise2", "INTEGER", "0");
        addColumn("Layer_Tilt_Lower1", "INTEGER", "0");
        addColumn("Layer_Tilt_Lower2", "INTEGER", "0");
        addColumn("Layer_Overlift1", "INTEGER", "0");
        addColumn("Layer_Overlift2", "INTEGER", "0");
        addColumn("Layer_Breathe1", "INTEGER", "0");
        addColumn("Layer_Breathe2", "INTEGER", "0");
        addColumn("Layer_Settle1", "INTEGER", "0");
        addColumn("Layer_Settle2", "INTEGER", "0");
        addColumn("Layer_Tilt_Percent1", "INTEGER", "0");
        addColumn("Layer_Tilt_Percent2", "INTEGER", "0");
        addColumn("Cut_Off_Layers", "INTEGER", "0");
        addColumn("Final_OverLift", "INTEGER", "0");
        addColumn("Base_Layer_settle", "INTEGER", "0");
    };

    ~MotionSchema();

    MotionConfig mConf;
    string getSqlInsertCommand();
    string getSqlUpdateCommand(uint16_t rowId);
    string getSqlRemoveCommand(uint16_t rowId);
    string getSqlFindById(uint16_t rowId);
    string getSqlFindAll();
    void setMotionConfig(MotionConfig temp);
    void setMotionPacket(network_messages::MotionConfig motionCmd);
};



#endif // MOTIONSCHEMA_H
