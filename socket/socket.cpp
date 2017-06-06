#include "socket.h"
#include <QHash>
#include <QCoreApplication>
#include "iniconfig.h"
#include "tcpserver.h"

typedef struct _tagSocketParam
{
    int nType;
    QObject* pObj;
    QString szIniPath;

    ~_tagSocketParam()
    {
        pObj->deleteLater();
    }
}SocketParam, *pSocketParam;

int _argc = 1;
QSharedPointer<QCoreApplication> app(new QCoreApplication(_argc, nullptr));

QHash<int, QSharedPointer<SocketParam>> g_hashSockets;
pSocketParam FindSocket(int nId);


int InitSocket(int nID, int nType, const char* szIniPath, RecvCallback pCallback)
{
    qDebug() << __FUNCTION__;

    IniConfig config(szIniPath);
    QString section;
    TcpServer* pServer;

    g_hashSockets.remove(nID);
    g_hashSockets.insert(nID, QSharedPointer<SocketParam>(new SocketParam()));
    g_hashSockets[nID]->nType = nType;
    g_hashSockets[nID]->szIniPath = QString(szIniPath);

    switch (nType)
    {
    case TCP_SERVER:
        pServer = new TcpServer(pCallback);
        g_hashSockets[nID]->pObj = pServer;
        section = QString().sprintf("TcpServer%d", nID);
        pServer->listen(QHostAddress(config.GetValue(section, "Address", "127.0.0.1").toString()),
                        config.GetValue(section, "Port", 9999).toInt());
        break;
    case TCP_CLIENT:
        g_hashSockets[nID]->pObj = new QTcpSocket();
        break;
    default:
        break;
    }
    return 0;
}

int TCPSend(int nID, const char* szSendBuf, const char* szDstIP, int nDstPort)
{
    pSocketParam socket = FindSocket(nID);
    TcpServer* pServer = nullptr;
    QTcpSocket* pSocket = nullptr;
    QAbstractSocket* pSendSocket;
    if (socket != nullptr)
    {
        switch (socket->nType) {
        case TCP_SERVER:
            pServer = (TcpServer*)socket->pObj;
            pSocket = pServer->getSocket(szDstIP, nDstPort);
            if (pSocket == nullptr)
                return -1;
            else
            {
                if (pSocket->state() == QTcpSocket::ConnectedState)
                    pSocket->write(szSendBuf, strlen(szSendBuf) + 1);
                else
                    qDebug() << "Socket is disconnected";
            }
            break;
        case TCP_CLIENT:
            pSendSocket = (QAbstractSocket*)socket->pObj;
            if (pSendSocket == nullptr)
                return -1;
            else
            {
                if (pSendSocket->state() == QAbstractSocket::ConnectedState)
                    pSendSocket->write(szSendBuf, strlen(szSendBuf) + 1);
                else
                    qDebug() << "Socket is disconnected";
            }
            break;
        default:
            qDebug() << "Error socket type";
            return -1;
            break;
        }
    }
    return 0;
}


pSocketParam FindSocket(int nId)
{
    if (g_hashSockets.contains(nId))
    {
        return g_hashSockets[nId].data();
    }
    else
    {
        return nullptr;
    }
}


int TCPConnect(int nID, int nTimeoutMs)
{
    pSocketParam pParam = FindSocket(nID);
    if (pParam->nType != TCP_CLIENT)
    {
        qDebug() << "Error in socket type";
        return -1;
    }
    IniConfig config(pParam->szIniPath);
    QString section = QString().sprintf("TcpClient%d", nID);
    QTcpSocket* pSocket = (QTcpSocket*)pParam->pObj;
    pSocket->connectToHost(QHostAddress(config.GetValue(section, "Address", "127.0.0.1").toString()),
                           config.GetValue(section, "Port", 9999).toInt());
    if (pSocket->waitForConnected(nTimeoutMs))
        return 0;
    else
    {
        qDebug() << "connect time timeout";
        return -1;
    }
}

int TCPRecv(int nID, char* szRecvBuf, int nBufLen, int nTimeoutMs)
{
    pSocketParam pParam = FindSocket(nID);
    if (pParam->nType != TCP_CLIENT)
    {
        qDebug() << "Error in socket type";
        return -1;
    }
    QTcpSocket* pSocket = (QTcpSocket*)pParam->pObj;
    if (pSocket->waitForReadyRead(nTimeoutMs))
    {
        QByteArray bytes = pSocket->readAll();
        int nReadSize = (bytes.size() > nBufLen) ? nBufLen : bytes.size();
        memcpy(szRecvBuf, bytes.data(), nReadSize);
        return 0;
    }
    else
    {
        qDebug() << "read time timeout";
        return -1;
    }
}
