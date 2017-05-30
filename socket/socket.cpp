#include "socket.h"
#include <QHash>
#include <QApplication>
#include "iniconfig.h"
#include "tcpserver.h"

int _argc = 1;
QSharedPointer<QApplication> app(new QApplication(_argc, nullptr));

QHash<int, QSharedPointer<QObject>> g_hashSockets;
QSharedPointer<QObject> FindSocket(int nId);

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
        g_hashSockets.insert(nID, QSharedPointer<QObject>(new TcpServer(pCallback)));
        pServer = (TcpServer*)g_hashSockets[nID].data();
        section = QString().sprintf("TcpServer%d", nID);
        pServer->listen(QHostAddress(config.GetValue(section, "Address", "127.0.0.1").toString()),
                        config.GetValue(section, "Port", 9999).toInt());
        break;
    default:
        break;
    }
    return 0;
}

void UninitSocket(int nID)
{

}


QSharedPointer<QObject> FindSocket(int nId)
{
    if (g_hashSockets.contains(nId))
    {
        return g_hashSockets[nId];
    }
    else
    {
        return nullptr;
    }
}
