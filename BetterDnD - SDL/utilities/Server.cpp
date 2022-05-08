#include "Server.h"
#include <string>
#include <fstream>

bool initDone = false;
Server::Server()
{
	

}

Server::~Server()
{
	// Close the socket
	closesocket(clientSocket);

	// Clean WinSock

	WSACleanup();
}

void Server::init()
{
	// Initialize WinSock

	wsOk = WSAStartup(ver, &wsaData);
	if (wsOk != 0)
	{
		std::cout << "Cant init winsock" << std::endl;
	}

	// Create a socket
	listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		std::cout << "Cant create a socket" << std::endl;
	}

	// Bind IP and port to a socket
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell WinSock the socket type is listening
	listen(listening, SOMAXCONN);


	FD_ZERO(&master);
	FD_SET(listening, &master);
	
	initDone = true;
	std::cout << "u" << std::endl;
}

void Server::update()
{
	while (true)
	{
		// Messages
		if (initDone == true)
		{

			//std::cout << "updating" << std::endl;
			fd_set copy = master;
			socketCount = select(0, &copy, nullptr, nullptr, nullptr);

			for (int i = 0; i < socketCount; i++)
			{
				SOCKET sock = copy.fd_array[i];

				if (sock == listening)
				{
					//accept new connection
					SOCKET client = accept(listening, nullptr, nullptr);
					// Add the new connection to the list
					FD_SET(client, &master);
					std::cout << "Connected" << std::endl;
				}
				else
				{
					// accept new message 
					ZeroMemory(buf, 4096);

					int bytesIn = recv(sock, buf, 4096, 0);
					if (bytesIn <= 0)
					{
						//drop the client
						closesocket(sock);
						FD_CLR(sock, &master);
					}
					else
					{
						//HANDLE MESSAGE
						//buf = ;

						//SEND A MESSAGE

						std::string str_buf(buf);
						if (str_buf.find("hi") != std::string::npos)
						{
							std::cout << 1 << std::endl;
						}

						std::cout << buf << std::endl;
						

						for (int i = 0; i < master.fd_count; i++)
						{
							SOCKET outSock = master.fd_array[i];
							if (outSock != listening && outSock != sock)
							{
								send(outSock, buf, bytesIn, 0);
							}
						}
					}

				}

			}
		}
		else
		{
			std::cout << "Init Not Done" << std::endl;
		}
	}
}

