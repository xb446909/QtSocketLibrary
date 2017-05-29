#include "tcpserverthread.h"
#include <QtNetwork>
#include <sstream>

using namespace std;

TcpServerThread::TcpServerThread(int socketDescriptor, RecvCallback pCallback, QObject *parent)
    : QThread(parent)
    , socketDescriptor(socketDescriptor)
    , recvCallback(pCallback)
{

}

void TcpServerThread::run()
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor))
    {
        emit error(tcpSocket.error());
        return;
    }
    if ((recvCallback != nullptr) && tcpSocket.state() == QTcpSocket::ConnectedState)
        recvCallback(RECV_SOCKET, (char*)tcpSocket.peerAddress().toString().toStdString().c_str(),
                     tcpSocket.peerPort(), 0, nullptr);

    tcpSocket.write("str.toLocal8Bit()");
    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
}
