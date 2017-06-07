#include "tcpclientproc.h"

TcpClientProc::TcpClientProc(RecvCallback pCallback, QObject *parent)
    : QTcpSocket(parent)
    , recvCallBack(pCallback)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(this, SIGNAL(disconnected()), this, SLOT(serverDisconnected()));
}

void TcpClientProc::readData()
{
    QByteArray recvBytes = readAll();
    if (recvCallBack != nullptr)
        recvCallBack(RECV_DATA, peerAddress().toString().toStdString().c_str(),
                     peerPort(), recvBytes.size(), recvBytes.data());
}

void TcpClientProc::serverDisconnected()
{
    if (recvCallBack != nullptr)
        recvCallBack(RECV_CLOSE, peerAddress().toString().toStdString().c_str(),
                     peerPort(), 0, nullptr);
}
