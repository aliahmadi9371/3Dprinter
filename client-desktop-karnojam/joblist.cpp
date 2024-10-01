#include "joblist.h"

JobList::JobList()
{

}

bool JobList::setConfigItem(int index, __Job3D &job3D)
{
    if(index <0 || index >= job3DItems.size())
            return false;

        job3DItems[index] = job3D ;
        return true;
}

QVector<__Job3D> JobList::items()
{
    return job3DItems;
}

void JobList::addJob3D(__Job3D job3D)
{
    emit preItemAppended();
    job3DItems.append(job3D);
    emit postItemAppended();
}
