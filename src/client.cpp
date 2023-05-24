#include <iostream>
#include <string>
#include <cstring>
#include "socket_utils.h"

const std::string SERVER_IP = "127.0.0.1";
const int PORT = 8080;

int main() {
#ifdef _WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "Failed to initialize Winsock." << std::endl;
		return 1;
	}
#endif

	SOCKET_TYPE clientSocket;
	struct sockaddr_in serverAddress;

	// Create socket
	if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		std::cerr << "Failed to create socket." << std::endl;
		return 1;
	}

	// Prepare the sockaddr_in structure
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP.c_str());
	serverAddress.sin_port = htons(PORT);

	// Connect to server
	if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
		std::cerr << "Failed to connect to server." << std::endl;
		return 1;
	}

	std::cout << "Connected to server." << std::endl;

	// Send and receive messages
	std::string message;
	while (true) {
		std::cout << "Enter a message (or 'quit' to exit): ";
		std::getline(std::cin, message);

		// Send the message to the server
		sendMessage(clientSocket, message);

		if (message == "quit") {
			break;
		}

		// Receive the echo message from the server
		std::string receivedMessage = receiveMessage(clientSocket);
		if (!receivedMessage.empty()) {
			std::cout << "Received echo: " << receivedMessage << std::endl;
		}
	}

	std::cout << "Connection closed." << std::endl;

	CLOSE_SOCKET(clientSocket);

#ifdef _WIN32
	WSACleanup();
#endif

	return 0;
}
