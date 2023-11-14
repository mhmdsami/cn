#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAX 1000

int main()
{
    int socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    int size;
    char buffer[MAX], message[] = "Command executed successfully!";
    struct sockaddr_in client_addr, server_addr;
    socklen_t client_len = sizeof(client_addr);

    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8079);

    bind(socket_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr));

    while (1)
    {
        bzero(buffer, sizeof(buffer));
        recvfrom(socket_descriptor, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr,
                 &client_len);
        printf("command executed: %s", buffer);
        system(buffer);
        sendto(socket_descriptor, message, sizeof(message), 0, (struct sockaddr *)&client_addr,
               client_len);
    }
    close(socket_descriptor);
    return 0;
}