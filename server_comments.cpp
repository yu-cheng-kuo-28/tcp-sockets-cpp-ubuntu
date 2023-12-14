#include <iostream>          // Include for input/output stream
#include <sys/socket.h>      // Include for socket APIs
#include <netinet/in.h>      // Include for internet protocols
#include <cstring>           // Include for string operations
#include <unistd.h>          // Include for POSIX operating system API

int main() {
    int server_fd, new_socket;           // Declare file descriptors for server and new socket
    struct sockaddr_in address;          // Structure for storing internet address
    int opt = 1;                         // Option value for setsockopt
    int addrlen = sizeof(address);       // Length of the address structure

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");         // Print error if socket creation fails
        exit(EXIT_FAILURE);              // Exit with failure status
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");            // Print error if setting socket options fails
        exit(EXIT_FAILURE);              // Exit with failure status
    }
    address.sin_family = AF_INET;        // Set address family to AF_INET (IPv4)
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
    address.sin_port = htons(8080);      // Set port to 8080 with proper byte order

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");           // Print error if bind fails
        exit(EXIT_FAILURE);              // Exit with failure status
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");                // Print error if listen fails
        exit(EXIT_FAILURE);              // Exit with failure status
    }

    std::cout << "Listening..." << std::endl; // Print message indicating server is listening

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");                // Print error if accept fails
        exit(EXIT_FAILURE);              // Exit with failure status
    }

    // Receive data from the client
    char buffer[1024] = {0};             // Buffer to store data from client
    int valread = read(new_socket, buffer, 1024); // Read data into buffer
    std::cout << "Received message: " << buffer << std::endl; // Print received message

    // Close the socket when done
    close(server_fd);                    // Close the server file descriptor

    return 0;
}
