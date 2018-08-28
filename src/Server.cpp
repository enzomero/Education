#include <iostream>
#include <sstream>
#include <string>

//#define _WIN32_WINNT 0x501

#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define IP "127.0.0.1"
#define PORT "8000"
#define CLOSE_PROGRAMM 1;
#define BUFFER_SIZE 1024
using std::cerr;



int main()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cerr << "WSAS load fail\n";
		return CLOSE_PROGRAMM;
	}

	struct addrinfo* addr = NULL; //listner socket
	struct addrinfo hints;			//template for client
	ZeroMemory(&hints, sizeof(hints)); //setter for all members of struct to 0

	hints = { AI_PASSIVE, AF_INET, SOCK_STREAM, IPPROTO_TCP };

	//set socket lsitner on addres
	int result = getaddrinfo(IP, PORT, &hints, &addr);
	if ( result != 0)
	{
		cerr << "Can't get info from addres: " << IP << ":" << PORT << "\n";
		WSACleanup();
		return CLOSE_PROGRAMM;
	}

	//set listner for addres
	int listner_socket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

	if (listner_socket == INVALID_SOCKET)
	{
		cerr << "Listner down!" << listner_socket << "\n";
		//need to clean
		freeaddrinfo(addr);
		WSACleanup();
		return CLOSE_PROGRAMM;
	}

	//======================================
	// binding of socket

	result = bind(listner_socket, addr->ai_addr, addr->ai_addrlen);
	if (result == SOCKET_ERROR)
	{
		cerr << "Bing faild:" << result << "\n";
		freeaddrinfo(addr);
		closesocket(listner_socket);
		WSACleanup();
		return CLOSE_PROGRAMM;
	}

	//======================================
	// preparing for listen

	if (listen(listner_socket, 2^31) == SOCKET_ERROR)
	{
		cerr << "Preparing listner faild " << "\n";
		closesocket(listner_socket);
		WSACleanup();
		return CLOSE_PROGRAMM;
	}

	//======================================
	// waiting incomming msg

	int client_socket = accept(listner_socket, NULL, NULL);
	if (client_socket == SOCKET_ERROR)
	{
		cerr << " Can't wait socket" << "\n ";
		closesocket(listner_socket);
		WSACleanup();
		return CLOSE_PROGRAMM;
	}

	//======================================
	// request handler 

	char buf[BUFFER_SIZE];
	result = recv(client_socket, buf, BUFFER_SIZE, 0);

	std::stringstream response; //Header of responce
	std::stringstream response_body; // body of responce

	if (result == SOCKET_ERROR)
	{
		cerr << "Can't receive any answer" << "\n";
		closesocket(client_socket);
	}
	else if (result == 0)
	{
		cerr << "Connection close" << "\n";
	}
	else if (result > 0)
	{
		buf[result] = '\0';

		response_body << "<title>Was created bby C++</>"
			<< "<h1>This page is testing env</>"
			<< "<pre>OUTPUT:" << result << "</>";

		response << "HTTP/1.1 201 TEST\r\n"
			<< "Version: HTTP/1.1\r\n"
			<< "Content-type: text/html; charset=utf-8\r\n"
			<< "\r\n\r\n"
			<< response_body.str();

		result = send(client_socket, response.str().c_str(), response.str().length(), 0);

		if (result == SOCKET_ERROR)
		{
			cerr << "Cant't to sent message!" << "\n";
		}

		closesocket(client_socket);
	}

	closesocket(listner_socket);
	freeaddrinfo(addr);
	WSACleanup();
	return 0;
}
