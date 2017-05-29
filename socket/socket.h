#ifndef SOCKET_H
#define SOCKET_H

#include "socket_global.h"
#include "socketlibrary.h"

extern "C" int InitSocket(int nID, int nType, const char* szIniPath = nullptr, RecvCallback pCallback = nullptr);
extern "C" void UninitSocket(int nID);
extern "C" int TCPConnect(int nID, int nTimeoutMs);
extern "C" int TCPSend(int nID, char* szSendBuf, char* szDstIP = nullptr, int nDstPort = 0);
extern "C" int TCPRecv(int nID, char* szRecvBuf, int nBufLen, int nTimeoutMs);

#endif // SOCKET_H
