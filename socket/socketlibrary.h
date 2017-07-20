#ifndef SOCKETLIBRARY_H
#define SOCKETLIBRARY_H

#define TCP_SERVER		0
#define TCP_CLIENT		1
#define UDP             2

#define RECV_ERROR		0
#define RECV_CLOSE		1
#define RECV_DATA		2
#define RECV_SOCKET		3

#define SOCK_SUCCESS	0
#define SOCK_ERROR		-1
#define SOCK_TIMEOUT	-2
#define SOCK_CLOSED		-3

typedef int(*RecvCallback)(int nType, const char* szIP, int nPort, int nSize, const char* szRecv);

typedef int(*fInitSocket)(int nID, int nType, const char* szIniPath, RecvCallback pCallback);
typedef void(*fUninitSocket)(int nID);
typedef int(*fTCPConnect)(int nID, int nTimeoutMs);
typedef int(*fTCPSend)(int nID, const char* szSendBuf, int nlen, const char* szDstIP, int nDstPort);  //server给指定的client发消息时，
                                                                                            //client的地址为addr
                                                                                            //client发送给sever时，IP和port为空
typedef int(*fTCPRecv)(int nID, char* szRecvBuf, int nBufLen, int nTimeoutMs, const char* szDstIP, int nDstPort);
typedef int(*fUDPSend)(int nID, const char* szSendBuf, const char* szDstIP, int nDstPort);
typedef int(*fUDPRecv)(int nID, char* szRecvBuf, int nBufLen, int nTimeoutMs, char* szDstIP, int* pnDstPort);

#endif // SOCKETLIBRARY_H
