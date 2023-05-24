#include <iostream>
#include <string>
#include <cstring>
#include "socket_utils.h"

const int PORT = 8080;

int main() {
#ifdef _WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "Failed to initialize Winsock." << std::endl;
		return 1;
	}
#endif

	SOCKET_TYPE serverSocket;
	struct sockaddr_in serverAddress;

	// Create socket
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		std::cerr << "Failed to create socket." << std::endl;
		return 1;
	}

	// Prepare the sockaddr_in structure
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(PORT);

	// Bind
	if (bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
		std::cerr << "Failed to bind." << std::endl;
		return 1;
	}

	// Listen
	if (listen(serverSocket, 1) == -1) {
		std::cerr << "Failed to listen." << std::endl;
		return 1;
	}

	std::cout << "Server started. Listening on port " << PORT << std::endl;

	// Accept connection
	SOCKET_TYPE clientSocket;
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLength = sizeof(clientAddress);
	if ((clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr*>(&clientAddress),
							   &clientAddressLength)) == -1) {
		std::cerr << "Failed to accept connection." << std::endl;
		return 1;
	}

	std::cout << "Client connected. Waiting for messages..." << std::endl;

	// Receive and send messages
	std::string message;
	while (true) {
		message = receiveMessage(clientSocket);
		if (message.empty()) {
			break;
		}
		std::cout << "Received message: " << message << std::endl;

		// Echo the received message back to the client
		sendMessage(clientSocket, message);
	}

	std::cout << "Connection closed." << std::endl;

	CLOSE_SOCKET(clientSocket);
	CLOSE_SOCKET(serverSocket);

#ifdef _WIN32
	WSACleanup();
#endif

	return 0;
}
