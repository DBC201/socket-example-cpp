#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

#include <iostream>
#include <string>
#include <cstring>

#ifdef _WIN32
	#include <winsock2.h>
	#pragma comment(lib, "ws2_32.lib")
	#define SOCKET_TYPE SOCKET
	#define CLOSE_SOCKET closesocket
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#define SOCKET_TYPE int
	#define CLOSE_SOCKET close
#endif

#ifndef socklen_t
	typedef int socklen_t;
#endif

void sendMessage(SOCKET_TYPE socket, const std::string& message) {
	int messageSize = message.size();
	if (send(socket, reinterpret_cast<const char*>(&messageSize), sizeof(messageSize), 0) == -1) {
		std::cerr << "Failed to send message size." << std::endl;
		return;
	}
	
	if (send(socket, message.c_str(), messageSize, 0) == -1) {
		std::cerr << "Failed to send message." << std::endl;
	}
}

std::string receiveMessage(SOCKET_TYPE socket) {
	int messageSize = 0;
	if (recv(socket, reinterpret_cast<char*>(&messageSize), sizeof(messageSize), 0) == -1) {
		std::cerr << "Failed to receive message size." << std::endl;
		return "";
	}
	
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	
	if (recv(socket, buffer, messageSize, 0) == -1) {
		std::cerr << "Failed to receive message." << std::endl;
		return "";
	}
	
	return std::string(buffer);
}

#endif // SOCKET_UTILS_H
