/*
Compile using "g++ -o client client.cpp -lws2_32"
*/

#include <iostream>      // Include for input/output stream
#include <winsock2.h>    // Include for Windows socket programming
#include <ws2tcpip.h>    // Include for Windows socket programming
using namespace std;
#pragma comment(lib, "Ws2_32.lib")  // Link with Ws2_32.lib for socket functions

int main() {
    WSADATA wsaData;                 // Structure to hold Winsock data
    SOCKET sock = INVALID_SOCKET;    // Declare a SOCKET variable
    struct sockaddr_in serv_addr;    // Structure for storing server address
    const char* hello = "Hello from client";  // Message to send

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        cout << "Winsock initialization failed.\n"; // Print error if Winsock initialization fails
        return 1;
    }

    // Create a socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cout << "Socket creation failed with error: " << WSAGetLastError() << endl; // Print error if socket creation fails
        WSACleanup();  // Clean up Winsock
        return 1;
    }

    serv_addr.sin_family = AF_INET;  // Set address family to IPv4
    serv_addr.sin_port = htons(8080);  // Set port to 8080 with proper byte order

    // Set IP address of the server
    serv_addr.sin_addr.s_addr = inet_addr("XXX.XXX.XX.XX"); // Replace with server IP address

    // Check if IP address is valid
    if (serv_addr.sin_addr.s_addr == INADDR_NONE) {
        cout << "Invalid address/ Address not supported.\n"; // Print error if address is invalid
        closesocket(sock);  // Close the socket
        WSACleanup();  // Clean up Winsock
        return 1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << "Connection Failed with error: " << WSAGetLastError() << endl; // Print error if connection fails
        closesocket(sock);  // Close the socket
        WSACleanup();  // Clean up Winsock
        return 1;
    }

    // Send a message to the server
    send(sock, hello, strlen(hello), 0);
    cout << "Hello message sent\n";  // Print confirmation of message sent

    // Close the socket
    closesocket(sock);  // Close the socket
    WSACleanup();  // Clean up Winsock

    return 0;
}
