#include "tcpserver.h"

TcpServer::TcpServer(RecvCallback pCallback, QObject *parent)
    : QTcpServer(parent)
    , recvCallback(pCallback)
{

}

TcpServer::~TcpServer()
{
    qDebug() << __FUNCTION__;
    foreach (TcpServerProc* proc, procList)
    {
        delete proc;
    }
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    TcpServerProc* proc = new TcpServerProc(socketDescriptor, recvCallback, this);
    procList.append(proc);
}

void TcpServer::getNewConnection(QTcpSocket* sock)
{
    clientList.append(sock);
}

void TcpServer::removeConnection(QTcpSocket* sock)
{
    clientList.removeAll(sock);
}
