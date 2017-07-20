#ifndef SOCKET_H
#define SOCKET_H

#include "socketlibrary.h"
#include <QtGlobal>

extern "C" Q_DECL_EXPORT int InitSocket(int nID, int nType, const char* szIniPath = nullptr, RecvCallback pCallback = nullptr);
extern "C" Q_DECL_EXPORT void UninitSocket(int nID);
extern "C" Q_DECL_EXPORT int TCPConnect(int nID, int nTimeoutMs);
extern "C" Q_DECL_EXPORT int TCPSend(int nID, const char* szSendBuf, const char* szDstIP = nullptr, int nDstPort = 0);
extern "C" Q_DECL_EXPORT int TCPRecv(int nID, char* szRecvBuf, int nBufLen, int nTimeoutMs, const char* szDstIP = nullptr, int nDstPort = 0);
extern "C" Q_DECL_EXPORT int UDPSend(int nID, const char* szSendBuf, const char* szDstIP, int nDstPort);
extern "C" Q_DECL_EXPORT int UDPRecv(int nID, char* szRecvBuf, int nBufLen, int nTimeoutMs, char* szDstIP, int* pnDstPort);

#endif // SOCKET_H
