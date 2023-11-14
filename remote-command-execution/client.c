#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define MAX 1000

int main()
{
    int socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    char buffer[MAX], message[MAX];
    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8079);
    bind(socket_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr));
    while (1)
    {
        printf("\nCommand for execution:");
        fgets(buffer, sizeof(buffer), stdin);
        sendto(socket_descriptor, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr,
               server_len);
        recvfrom(socket_descriptor, message, sizeof(message), 0, (struct sockaddr *)&server_addr, &server_len);
        printf("\nserver> %s", message);
    }
    return 0;
}