#ifndef MATERIALSCHEMA_H
#define MATERIALSCHEMA_H

#include "schema.h"
#include "myutility.h"
#include "materialconfig.h"
#include "message.pb.h"
#include "spdlog/spdlog.h"

class MaterialSchema : public Schema
{
public:
    MaterialSchema() : Schema("Material") {
        addColumn("Name", "TEXT", "Name" );
        addColumn("LayerThickness", "INTEGER", "0");
        addColumn("BurnInLayers", "INTEGER", "0" );
        addColumn("BurnInCureTime", "REAL", "0" );
        addColumn("NormalCureTime", "REAL", "0" );
        addColumn("BurnIntensity", "REAL", "0" );
        addColumn("Intensity", "REAL", "0" );
    }
    ~MaterialSchema();

    MaterialConfig mConf;
    string getSqlInsertCommand();
    string getSqlUpdateCommand(uint16_t rowId);
    string getSqlRemoveCommand(uint16_t rowId);
    string getSqlFindById(uint16_t rowId);
    string getSqlFindAll();
    void setMaterialConfig(MaterialConfig temp);
    void setMaterialPacket(network_messages::MaterialConfig materialCmd);
};

#endif // MATERIALSCHEMA_H
