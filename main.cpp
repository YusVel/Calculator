#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#include <WinSock2.h>
#include <iphlpapi.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>



#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"iphlpapi.lib")


int main()
{
	setlocale(LC_ALL, "ru");
	
	WSADATA fd;
	
	if (WSAStartup(MAKEWORD(2, 2), &fd))
	{
		return -1;
	}
	
	DWORD asize = 20000;
	PIP_ADAPTER_ADDRESSES adapters;
	do
	{
		adapters = (PIP_ADAPTER_ADDRESSES)malloc(asize);
		if (!adapters)
		{
			printf("Can not allocate %ld bytes for adapters", asize);
			WSACleanup();
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

	PIP_ADAPTER_ADDRESSES adapter = adapters;
	while (adapter)
	{
		printf("\nAdapters name: %S\n", adapters->FriendlyName);
		PIP_ADAPTER_UNICAST_ADDRESS adress = adapter->FirstUnicastAddress;
		while (adress)
		{
			printf("\t%s", adress->Address.lpSockaddr->sa_family == AF_INET ? "Ipv4" : "Ipv6");

			char ap[100];
			getnameinfo(adress->Address.lpSockaddr, adress->Address.iSockaddrLength, ap, sizeof(ap), 0, 0, NI_NUMERICHOST);
			printf("\t%s\n", ap);
			adress = adress->Next;
		}
		adapter = adapter->Next;
	}

	return 0;

}
