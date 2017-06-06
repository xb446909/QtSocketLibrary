#include "tcpserverproc.h"
#include "tcpserver.h"

TcpServerProc::TcpServerProc(int socketDescriptor, RecvCallback pCallback, QObject *parent)
    : QObject(parent)
    , socketDescriptor(socketDescriptor)
    , recvCallback(pCallback)
{
    if (!tcpSocket.setSocketDescriptor(socketDescriptor))
    {
        emit error(tcpSocket.error());
        if (recvCallback != nullptr)
            recvCallback(RECV_ERROR, nullptr, 0, 0, nullptr);
        return;
    }

    TcpServer* pServer = (TcpServer*)parent;
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnect()));
    connect(this, SIGNAL(newConnection(QTcpSocket*)), pServer, SLOT(getNewConnection(QTcpSocket*)));
    connect(this, SIGNAL(disconncted(QTcpSocket*)), pServer, SLOT(removeConnection(QTcpSocket*)));
    emit newConnection(&tcpSocket);
    if ((recvCallback != nullptr) && tcpSocket.state() == QTcpSocket::ConnectedState)
        recvCallback(RECV_SOCKET, tcpSocket.peerAddress().toString().toStdString().c_str(),
                     tcpSocket.peerPort(), 0, nullptr);
}

void TcpServerProc::readData()
{
    QByteArray recvBytes = tcpSocket.readAll();
    if (recvCallback != nullptr)
        recvCallback(RECV_DATA, tcpSocket.peerAddress().toString().toStdString().c_str(),
                     tcpSocket.peerPort(), recvBytes.size(), recvBytes.data());
}


void TcpServerProc::socketDisconnect()
{
    if (recvCallback != nullptr)
        recvCallback(RECV_CLOSE, tcpSocket.peerAddress().toString().toStdString().c_str(),
                     tcpSocket.peerPort(), 0, nullptr);
    emit disconncted(&tcpSocket);
}

