#include <iostream>
#include <WS2tcpip.h>
using namespace std;

#pragma comment (lib, "WS2_32.LIB")

#include "..\..\SpaceCoin_Server\SpaceCoin_Server\protocol.h"

int main()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	SOCKET client_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);
	
	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT_NUM);
	inet_pton(AF_INET, "127.0.0.11", &server_addr.sin_addr);
	int ret = connect(client_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
	if (0 != ret) {
		cout << "err\n";
	}

	CS_LOGIN_PACKET packet;
	packet.size = sizeof(CS_LOGIN_PACKET);
	packet.type = CS_LOGIN;
	strcpy_s(packet.id, "test");
	strcpy_s(packet.pw, "1q2w3e4r");	
	send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	cout << "send() 통과\n";
	char recv_buf[BUF_SIZE];
	recv(client_socket, recv_buf, BUF_SIZE, 0);
	SC_LOGIN_INFO_PACKET* p = reinterpret_cast<SC_LOGIN_INFO_PACKET*>(recv_buf);
	cout << "recv() 통과\n";

	while (true);
}