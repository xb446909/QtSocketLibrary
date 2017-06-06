#ifndef UDPPROC_H
#define UDPPROC_H

#include "socketlibrary.h"
#include <QUdpSocket>

class UdpProc : public QUdpSocket
{
    Q_OBJECT
public:
    UdpProc(RecvCallback pCallback, QObject* parent = nullptr);

public slots:
    void readPendingDatagrams();

private:
    RecvCallback recvCallBack;
};

#endif // UDPPROC_H
