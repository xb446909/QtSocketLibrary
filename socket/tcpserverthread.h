#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "socketlibrary.h"

class TcpServerThread : public QThread
{
    Q_OBJECT
public:
    TcpServerThread(int socketDescriptor, RecvCallback pCallback, QObject* parent);

    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    RecvCallback recvCallback;
};

#endif // TCPSERVERTHREAD_H
