#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    struct sockaddr_in server_addr;
    int n, socket_descriptor;
    int len;
    char buff[100];
    
    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5600);
    
    connect(socket_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr));

    recv(socket_descriptor, buff, sizeof(buff), 0);
    printf("\nMessage: %s", buff);
}