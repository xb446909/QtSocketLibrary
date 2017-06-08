#ifndef SOCKET_H
#define SOCKET_H

#include "socket_global.h"
#include "socketlibrary.h"

extern "C" int InitSocket(int nID, int nType, const char* szIniPath = nullptr, RecvCallback pCallback = nullptr);
extern "C" void UninitSocket(int nID);
extern "C" int TCPConnect(int nID, int nTimeoutMs);
extern "C" int TCPSend(int nID, const char* szSendBuf, const char* szDstIP = nullptr, int nDstPort = 0);
extern "C" int TCPRecv(int nID, char* szRecvBuf, int nBufLen, int nTimeoutMs, const char* szDstIP = nullptr, int nDstPort = 0);
extern "C" int UDPSend(int nID, const char* szSendBuf, const char* szDstIP, int nDstPort);
extern "C" int UDPRecv(int nID, char* szRecvBuf, int nBufLen, int nTimeoutMs, char* szDstIP, int* pnDstPort);

#endif // SOCKET_H
