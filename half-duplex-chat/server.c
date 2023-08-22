#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAX 1000
#define BACKLOG 5

int main()
{
    char buff[MAX];
    char client_msg[MAX];
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5214);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    printf("Server running...\n");
    bind(socket_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(socket_descriptor, BACKLOG);
    
    int client_socket_descriptor = accept(socket_descriptor, NULL, NULL);

    while (1)
    {
        printf("server> ");
        fgets(buff, sizeof(buff), stdin);
        send(client_socket_descriptor, buff, sizeof(buff), 0);
        recv(client_socket_descriptor, &client_msg, sizeof(client_msg), 0);
        printf("[client] %s\n", client_msg);
    }
    close(socket_descriptor);
    return 0;
}