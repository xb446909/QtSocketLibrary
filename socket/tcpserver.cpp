#include "tcpserver.h"
#include "tcpserverthread.h"

TcpServer::TcpServer(RecvCallback pCallback, QObject *parent)
    : QTcpServer(parent)
    , recvCallback(pCallback)
{

}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    TcpServerThread *thread = new TcpServerThread(socketDescriptor, recvCallback, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
