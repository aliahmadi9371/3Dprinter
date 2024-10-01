#ifndef JOBSCHEMA_H
#define JOBSCHEMA_H
#include "message.pb.h"
#include "schema.h"
#include "myutility.h"
#include "Job.h"

class JobSchema : public Schema
{
public:
    JobSchema(): Schema("Job") {
        addColumn("Name", "TEXT", static_cast<string>("Name") );
        addColumn("Size", "INTEGER", static_cast<string>("0") );
    };
    ~JobSchema();

    __Job3D mConf;
    string getSqlInsertCommand();
    string getSqlUpdateCommand(uint16_t rowId);
    string getSqlRemoveCommand(uint16_t rowId);
    string getSqlFindById(uint16_t rowId);
    string getSqlFindAll();
    void setJob3DConfig(__Job3D temp);
    void setJob3DPacket(network_messages::Job3D jobCmd);
};


#endif // JOBSCHEMA_H
