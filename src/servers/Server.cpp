#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    // 1. establish socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr{};
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (sockaddr *)&server_addr, sizeof(server_addr));

    listen(server_fd, 5);

    std::cout << "Server running on port 8080\n";

    int client_fd = accept(server_fd, nullptr, nullptr);

    char buffer[1024];
    read(client_fd, buffer, sizeof(buffer));
    write(client_fd, "Hello from server", 17); // 发送

    close(client_fd);

    close(server_fd);

    
}