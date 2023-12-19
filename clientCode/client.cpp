/*
Compile using "g++ -o client client.cpp -lws2_32"
*/
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in serv_addr;
    const char* hello = "Hello from client";

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cout << "Winsock initialization failed.\n";
        return 1;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cout << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Set IP address of the server
    serv_addr.sin_addr.s_addr = inet_addr("XXX.XXX.XX.XX"); // Set your IP of the server here

    if (serv_addr.sin_addr.s_addr == INADDR_NONE) {
        std::cout << "Invalid address/ Address not supported.\n";
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "Connection Failed with error: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    send(sock, hello, strlen(hello), 0);
    std::cout << "Hello message sent\n";

    // Close the socket
    closesocket(sock);
    WSACleanup();

    return 0;
}
