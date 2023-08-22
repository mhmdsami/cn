#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT 5214
#define MAX 1000

void print_err_and_exit(const char *err)
{
    perror(err);
    exit(1);
}

int main()
{
    char buff[MAX], server_response[MAX];
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    char hostname[MAX], ipaddress[MAX];
    struct hostent *host;

    if (gethostname(hostname, sizeof(hostname)) == 0)
    {
        host = gethostbyname(hostname);
    }
    else
    {
        print_err_and_exit("[err] IP Address Not Found");
    }

    struct sockaddr_in server_addr;
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    connect(socket_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    while (1)
    {
        recv(socket_descriptor, server_response, sizeof(server_response), 0);
        printf("[server] %s\n", server_response);
        printf("client> ");
        fgets(buff, sizeof(buff), stdin);
        send(socket_descriptor, buff, sizeof(buff), 0);
    }

    close(socket_descriptor);
    return 0;
}