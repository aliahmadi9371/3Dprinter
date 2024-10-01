#include "materialconfiglist.h"

MaterialConfigList::MaterialConfigList()
{

}

bool MaterialConfigList::setConfigItem(int index, MaterialConfig &configItem)
{
    if(index <0 || index >= configItems.size())
            return false;

        configItems[index] = configItem ;
        return true;
}

QVector<MaterialConfig> MaterialConfigList::items()
{
    return configItems;
}

void MaterialConfigList::addConfig(MaterialConfig config)
{
    emit preItemAppended();
    configItems.append(config);
    emit postItemAppended();
}
