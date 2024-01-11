#include <WinSock2.h>
#include <iphlpapi.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"iphlpapi.lid")


int main()
{
	WSADATA fd;
	
	if (WSAStartup(MAKEWORD(2, 2), &fd))
	{
		return -1;
	}
	WSACleanup();
	printf("OK!\n");
	return 0;

}
