#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#define PORT 3000

int main()
{
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    char buffer[100], file[1000];
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);
    connect(socket_descriptor, (struct sockaddr *)&server_address, sizeof(server_address));
    while (1)
    {
        printf("File: ");
        scanf("%s", buffer);
        send(socket_descriptor, buffer, strlen(buffer) + 1, 0);
        printf("File content: \n");
        recv(socket_descriptor, &file, sizeof(file), 0);
        printf("%s\n", file);
    }
    close(socket_descriptor);
    return 0;
}