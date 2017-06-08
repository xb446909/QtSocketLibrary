#include "udpproc.h"

UdpProc::UdpProc(RecvCallback pCallback, QObject *parent)
    : QUdpSocket(parent)
    , recvCallBack(pCallback)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}


void UdpProc::readPendingDatagrams()
{
    while (hasPendingDatagrams() && (recvCallBack != nullptr))
    {
        QByteArray datagram;
        datagram.resize(pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        readDatagram(datagram.data(), datagram.size(),
                     &sender, &senderPort);
        recvCallBack(RECV_DATA, sender.toString().toStdString().c_str(),
                     senderPort, datagram.size(), datagram.data());

    }
}
