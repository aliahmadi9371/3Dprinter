#include "machineconfiglist.h"

MachineConfigList::MachineConfigList()
{

}

bool MachineConfigList::setConfigItem(int index, MachineConfig &configItem)
{
    if(index <0 || index >= configItems.size())
            return false;

        configItems[index] = configItem ;
        return true;
}

QVector<MachineConfig> MachineConfigList::items()
{
    return configItems;
}

void MachineConfigList::addConfig(MachineConfig config)
{
    emit preItemAppended();
    configItems.append(config);
    emit postItemAppended();
}
