#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
    int socket_descriptor;
    char buff[1024];
    struct sockaddr_in server_addr;

    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(3000);
    
    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    connect(socket_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr));

    while (1)
    {
        printf("Enter the message: ");
        fgets(buff, 100, stdin);
        send(socket_descriptor, buff, sizeof(buff) + 1, 0);
        printf("Data sent: %s", buff);
    }
}
