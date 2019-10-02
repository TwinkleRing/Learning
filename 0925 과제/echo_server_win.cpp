#pragma comment(lib,"ws2_32")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024
void ErrorHandling(const char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	char echo_message[BUF_SIZE] = { 0 };
	char message[BUF_SIZE];
	int strLen, i, echo_strLen;

	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSize;

	if (argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	if (bind(hServSock, (SOCKADDR*)& servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	clntAdrSize = sizeof(clntAdr);

	for (i = 0; i < 5; i++)
	{
		hClntSock = accept(hServSock, (SOCKADDR*)& clntAdr, &clntAdrSize);
		if (hClntSock == -1)
			ErrorHandling("accept() error");
		else
			printf("Connected client %d \n", i + 1);

		int j = 0;
		echo_strLen = 0;

		while ((strLen = recv(hClntSock, message, BUF_SIZE, 0)) != 0) {
			message[strLen] = 0;
			printf("message: %s\n", message);
			printf("message size : %d\n", strLen);
			strncat_s(echo_message, message, strLen - 1); /* strLen - 1 :  Enter Á¦°Å */
			printf("echo_message: %s\n", echo_message);
			echo_strLen += strLen;
			j++;
			if (j == 3) {
				send(hClntSock, echo_message, echo_strLen, 0);
				for (int k = 0; k < BUF_SIZE; k++)
					echo_message[k] = 0;
				j = 0;
			}
		}
		closesocket(hClntSock);
	}

	closesocket(hServSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}