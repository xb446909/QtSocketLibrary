#ifndef TCPCLIENTPROC_H
#define TCPCLIENTPROC_H

#include <QtNetwork>
#include "socketlibrary.h"

class TcpClientProc : public QTcpSocket
{
    Q_OBJECT
public:
    TcpClientProc(RecvCallback pCallback, QObject* parent = nullptr);

public slots:
    void readData();
    void serverDisconnected();

private:
    RecvCallback recvCallBack;
};

#endif // TCPCLIENTPROC_H
