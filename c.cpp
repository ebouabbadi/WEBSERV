#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>

#define PORT 8080
#define MAX_CLIENTS 10

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    struct pollfd poll_fd[MAX_CLIENTS];
    int poll_count = 0;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    // Initialize pollfd structures
    poll_fd[0].fd = server_fd;
    poll_fd[0].events = POLLIN;
    poll_count++;

    while (true) {
        // Poll for events
        int poll_result = poll(poll_fd, poll_count, -1);
        if (poll_result == -1) {
            perror("Poll failed");
            exit(EXIT_FAILURE);
        }

        // Check for server_fd events
        if (poll_fd[0].revents & POLLIN) {
            // Accept a new client connection
            socklen_t client_addr_len = sizeof(client_addr);
            if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
                perror("Accept failed");
                exit(EXIT_FAILURE);
            }

            // Add the new client_fd to pollfd structures
            poll_fd[poll_count].fd = client_fd;
            poll_fd[poll_count].events = POLLIN;
            poll_count++;

            // Send a welcome message to the new client
            char message[] = "Welcome to the server!\n";
            send(client_fd, message, strlen(message), 0);

            std::cout << "New client connected: " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;
        }

        // Check for client_fd events
        for (int i = 1; i < poll_count; i++) {
            if (poll_fd[i].revents & POLLIN) {
                char buffer[1024] = {0};
                int bytes_received = recv(poll_fd[i].fd, buffer, sizeof(buffer), 0);

                if (bytes_received <= 0) {
                    // Connection closed or error occurred
                    std::cout << "Client disconnected" << std::endl;

                    // Remove the client_fd from pollfd structures
                    close(poll_fd[i].fd);
                    poll_count--;
                    poll_fd[i] = poll_fd[poll_count];
                    i--;
                } else {
                    // Echo the received message back to the client
                    send(poll_fd[i].fd, buffer, bytes_received, 0);
                }
            }
        }
    }
}
