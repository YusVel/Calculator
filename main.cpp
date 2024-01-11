#include <WinSock2.h>
#include <iphlpapi.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"iphlpapi.lib")


int main()
{
	WSADATA fd;
	
	if (WSAStartup(MAKEWORD(2, 2), &fd))
	{
		return -1;
	}
	DWORD asize = 4000;
	PIP_ADAPTER_ADDRESSES adapters;
	do
	{
		adapters = (PIP_ADAPTER_ADDRESSES)malloc(asize);
		if (!adapters)
		{
			printf("Can not allocate %ld bytes for adapters", asize);
			return -1;
		}
		int r = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, 0, adapters, &asize);
		if (r == ERROR_BUFFER_OVERFLOW)
		{
			printf("GetAdaptersAddresses wantd %ld bytes.\n", asize);
			free(adapters);
		}
		else if (r == ERROR_SUCCESS)
		{
			break;
		}
		else
		{
			printf(" Error from GetAdaptersAddresses: %d\n", r);
			free(adapters);
			WSACleanup();
			return - 1;
		}
	} while (!adapters);
	printf("Adapters name: %s", adapters->FriendlyName);

	return 0;

}
