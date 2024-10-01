#include "uimessages.h"

UIMessages::UIMessages()
{

}

void UIMessages::enqueue(QString message)
{
   mutexProtection.lock();
   messages.enqueue(message);
   mutexProtection.unlock();
}

QString UIMessages::getMessage()
{
    QString temp = "";
     mutexProtection.lock();
    if(messages.size() > 0) {
        temp = messages.dequeue();
    }
    mutexProtection.unlock();
    return temp;
}
