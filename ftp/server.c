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
#define BACKLOG 5

int main()
{
    int size;
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    char buffer[100], file[1000];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    struct stat stat_var;
    FILE *fp;
    
    bzero(&server_addr, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);
    
    bind(socket_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(socket_descriptor, BACKLOG);
    
    printf("%s\n", "Server is running ...");
    
    int client_socket_descriptor = accept(socket_descriptor, (struct sockaddr *)&client_addr, &client_len);
    
    while (1)
    {
        bzero(buffer, sizeof(buffer));
        bzero(file, sizeof(file));
        recv(client_socket_descriptor, buffer, sizeof(buffer), 0);
        fp = fopen(buffer, "r");
        stat(buffer, &stat_var);
        size = stat_var.st_size;
        fread(file, sizeof(file), 1, fp);
        send(client_socket_descriptor, file, sizeof(file), 0);
    }
    
    return 0;
}
