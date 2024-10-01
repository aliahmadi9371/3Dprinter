#ifndef UIMESSAGES_H
#define UIMESSAGES_H

#include <mutex>
#include <QObject>
#include <QQueue>
#include <thread>

using namespace std;

class UIMessages: public QObject
{
    Q_OBJECT
public:
    UIMessages();
    mutex mutexProtection;
    QQueue<QString> messages;
    void enqueue(QString message);
    Q_INVOKABLE QString getMessage();

};

#endif // UIMESSAGES_H
