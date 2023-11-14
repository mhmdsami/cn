#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string.h>
#include <stdio.h>

int main()
{
    int socket_descriptor, client_descriptor;
    char buff[1024];
    struct sockaddr_in client_addr, server_addr;
    socklen_t client_len;
    
    client_len = sizeof(client_addr);
    
    bzero(&server_addr, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(3000);
    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    
    bind(socket_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(socket_descriptor, 5);
    
    printf("Server is running...\n");
    
    client_descriptor = accept(socket_descriptor, (struct sockaddr *)&client_addr, &client_len);
    
    while (1)
    {
        bzero(&buff, sizeof(buff));
        recv(client_descriptor, buff, sizeof(buff), 0);
        printf("Message received is %s\n", buff);
    }
}
