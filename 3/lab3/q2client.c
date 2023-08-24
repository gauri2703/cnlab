#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_IP "172.217.168.46"
#define SERVER_PORT 80

int main() {
    int socket_id = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    connect(socket_id, (struct sockaddr*)&server_addr, sizeof(server_addr));
    char request[] = "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
    send(socket_id, request, strlen(request), 0);

    char response[4096];
    recv(socket_id, response, sizeof(response), 0);

    printf("Received HTTP Response:\n%s\n", response);

    close(socket_id);
    return 0;
}