#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include "socketlibrary.h"
#include "tcpserverproc.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(RecvCallback pCallback, QObject *parent = 0);
    ~TcpServer();

    QTcpSocket* getSocket(const char* szIP, int nPort);

public slots:
    void getNewConnection(QTcpSocket* sock);
    void removeConnection(QTcpSocket* sock);


protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    RecvCallback recvCallback;
    QList<QTcpSocket*> clientList;
    QList<TcpServerProc*> procList;
};

#endif // TCPSERVER_H
