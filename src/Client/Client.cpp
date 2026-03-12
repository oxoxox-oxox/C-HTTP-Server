#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed\n";
        return 1;
    }

    const char* msg = "Hello server from C++ client";
    write(sock, msg, strlen(msg));

    char buffer[1024] = {0};
    read(sock, buffer, sizeof(buffer));
    std::cout << "Server says: " << buffer << "\n";

    close(sock);
    return 0;
}