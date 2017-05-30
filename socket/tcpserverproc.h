#ifndef TCPSERVERPROC_H
#define TCPSERVERPROC_H

#include <QObject>
#include <QTcpSocket>
#include "socketlibrary.h"

class TcpServerProc : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerProc(int socketDescriptor, RecvCallback pCallback, QObject *parent = 0);

signals:
    void error(QTcpSocket::SocketError socketError);
    void newConnection(QTcpSocket* pSock);
    void disconncted(QTcpSocket* pSock);

public slots:
    void readData();
    void socketDisconnect();

private:
    int socketDescriptor;
    RecvCallback recvCallback;
    QTcpSocket tcpSocket;
};

#endif // TCPSERVERPROC_H
