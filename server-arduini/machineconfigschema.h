#ifndef MACHINECONFIGSCHEMA_H
#define MACHINECONFIGSCHEMA_H

#include "schema.h"
#include "myutility.h"
#include "machineconfig.h"
#include "message.pb.h"
#include "spdlog/spdlog.h"


class MachineConfigSchema : public Schema
{
public:
    MachineConfigSchema(): Schema("MachineConfig") {
        addColumn("MachineNo", "TEXT", static_cast<string>("Name") );
        addColumn("ModelCode", "INTEGER", static_cast<string>("0") );
        addColumn("gProjectWidth", "INTEGER", static_cast<string>("0") );
        addColumn("gProjectHeight", "INTEGER", static_cast<string>("0") );
        addColumn("Version", "INTEGER", static_cast<string>("0") );
        addColumn("SubVersion", "INTEGER", static_cast<string>("0") );
        addColumn("NeedLicense", "INTEGER", static_cast<string>("0") );
        addColumn("HasDoor", "INTEGER", static_cast<string>("0") );
        addColumn("HasErm", "INTEGER", static_cast<string>("0") );
        addColumn("BUpTDownConfig", "INTEGER", static_cast<string>("0") );
        addColumn("PrinterUnit", "REAL", static_cast<string>("0") );
        addColumn("ZUpperLimit", "INTEGER", static_cast<string>("0") );
        addColumn("ProjectorProtocol", "INTEGER", static_cast<string>("0") );
        addColumn("NoOfMaskPoints", "INTEGER", static_cast<string>("0") );
        addColumn("MaxIntensity", "INTEGER", static_cast<string>("0") );
        addColumn("MinIntensity", "INTEGER", static_cast<string>("0") );
        addColumn("MaxIntensitySensor", "INTEGER", static_cast<string>("0") );
        addColumn("MinIntensitySensor", "INTEGER", static_cast<string>("0") );

        addColumn("HasPlunger", "INTEGER", static_cast<string>("0") );
        addColumn("TDownZHomePos", "INTEGER", static_cast<string>("0") );
        addColumn("vacuumTimer", "REAL", static_cast<string>("0") );
        addColumn("SensorSetPointVacuum", "REAL", static_cast<string>("0") );
        addColumn("SensorSetPoint", "REAL", static_cast<string>("0") );
        addColumn("SensorThreshold", "REAL", static_cast<string>("0") );
        addColumn("XShift", "REAL", static_cast<string>("0") );
        addColumn("YShift", "REAL", static_cast<string>("0") );
    }

    MachineConfig mConf;
    string getSqlInsertCommand();
    string getSqlUpdateCommand(uint16_t rowId);
    string getSqlRemoveCommand(uint16_t rowId);
    string getSqlFindById(uint16_t rowId);
    string getSqlFindByModelCode(uint32_t rowId);
    string getSqlFindAll();
    void setMachineConfig(MachineConfig temp);
    void setMachinePacket(network_messages::MachineConfig motionCmd);
};

#endif // MACHINECONFIGSCHEMA_H
