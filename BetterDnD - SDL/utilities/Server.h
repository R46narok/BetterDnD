#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <thread>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "44564"

class Server
{
private:
	WSADATA wsaData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk;

	SOCKET listening;
	SOCKET clientSocket;

	sockaddr_in hint;
	sockaddr_in client;

	fd_set master;
	int clientSize;
public:
	Server();
	~Server();

	char host[NI_MAXHOST]; // clients remote name
	char service[NI_MAXSERV]; // service (port)
	char buf[4096];
	int socketCount;

	void update();
	void init();

	std::thread GetinitThread() {
		return std::thread([=] { init(); });
	}
	std::thread GetUpdateThread() {
		return std::thread([=] { update(); });
	}
};