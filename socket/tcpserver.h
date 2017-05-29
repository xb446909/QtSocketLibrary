#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include "socketlibrary.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(RecvCallback pCallback, QObject *parent = 0);

signals:
    void Send();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    RecvCallback recvCallback;
};

#endif // TCPSERVER_H
