#pragma comment(lib,"ws2_32")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
void ErrorHandling(const char* message);

int main(int argc, char* argv[])
{
	char* strAddr = (char *)"203.211.218.102:9190";

	char strAddrBuf[50];
	SOCKADDR_IN servAddr;
	int size;

	WSADATA	wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	size = sizeof(servAddr);
	WSAStringToAddress(
		strAddr, AF_INET, NULL, (SOCKADDR*)& servAddr, &size);

	size = sizeof(strAddrBuf);
	WSAAddressToString(
		(SOCKADDR*)& servAddr, sizeof(servAddr), NULL, strAddrBuf,(LPDWORD) &size);

	printf("Second conv result: %s \n", strAddrBuf);
	WSACleanup();
	return 0;
}

void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}