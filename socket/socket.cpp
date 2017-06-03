#include "socket.h"
#include <QHash>
#include <QCoreApplication>
#include "iniconfig.h"
#include "tcpserver.h"

int _argc = 1;
QSharedPointer<QCoreApplication> app(new QCoreApplication(_argc, nullptr));

QHash<int, QPair<QSharedPointer<QObject>, int>> g_hashSockets;
QObject* FindSocket(int nId);

void DeleteTcpServer(QObject* pObj)
{
    TcpServer* pServer = (TcpServer*)pObj;
    pServer->close();
    pObj->deleteLater();
}

int InitSocket(int nID, int nType, const char* szIniPath, RecvCallback pCallback)
{
    qDebug() << __FUNCTION__;

    g_hashSockets.remove(nID);

    IniConfig config(szIniPath);
    QString section;
    TcpServer* pServer;

    switch (nType)
    {
    case TCP_SERVER:
        g_hashSockets.insert(nID, qMakePair(QSharedPointer<QObject>(new TcpServer(pCallback), DeleteTcpServer), nType));
        pServer = (TcpServer*)g_hashSockets[nID].first.data();
        section = QString().sprintf("TcpServer%d", nID);
        pServer->listen(QHostAddress(config.GetValue(section, "Address", "127.0.0.1").toString()),
                        config.GetValue(section, "Port", 9999).toInt());
        break;
    default:
        break;
    }
    return 0;
}


QObject *FindSocket(int nId)
{
    if (g_hashSockets.contains(nId))
    {
        return g_hashSockets[nId].first.data();
    }
    else
    {
        return nullptr;
    }
}
