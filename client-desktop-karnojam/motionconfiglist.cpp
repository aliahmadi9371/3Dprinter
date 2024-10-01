#include "motionconfiglist.h"

MotionConfigList::MotionConfigList(QObject *parent) : QObject(parent)
{

}

bool MotionConfigList::setConfigItem(int index, MotionConfig &configItem)
{
    if(index <0 || index >= motionItems.size())
            return false;

        motionItems[index] = configItem ;
        return true;
}

QVector<MotionConfig> MotionConfigList::items()
{
    return motionItems;
}

void MotionConfigList::addConfig(MotionConfig config)
{
    emit preItemAppended();
    motionItems.append(config);
    emit postItemAppended();
}
