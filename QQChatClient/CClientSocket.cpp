#include "pch.h"
#include "CClientSocket.h"

CClientSocket::CClientSocket()
{
    // Implementation of the constructor
    // Initialization code here
}
CClientSocket::~CClientSocket()
{
    // Implementation of the constructor
    // Initialization code here
}

void CClientSocket::OnReceive(int nErrorCode) {

    //接受客户端发送来的消息
    wchar_t szRecvMsg[100] = { 0 };
    Receive(szRecvMsg, sizeof(szRecvMsg));

    

    CSocket::OnReceive(nErrorCode);
}
