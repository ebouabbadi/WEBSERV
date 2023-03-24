#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main()
{
    // Create a TCP socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Bind the socket to a port
    sockaddr_in server_address;
    std::memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    if (bind(server_socket, (sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        std::cerr << "Error binding socket to port" << std::endl;
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) < 0)
    {
        std::cerr << "Error listening for connections" << std::endl;
        return 1;
    }

    std::cout << "Server started" << std::endl;

    // Accept incoming connections and handle requests
    while (true)
    {
        sockaddr_in client_address;
        socklen_t client_address_len = sizeof(client_address);
        int client_socket = accept(server_socket, (sockaddr*)&client_address, &client_address_len);
        if (client_socket < 0)
        {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }

        // Read and handle client request here

        close(client_socket);
    }

    return 0;
}
