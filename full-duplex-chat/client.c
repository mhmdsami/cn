#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
    int socket_descriptor;
    struct sockaddr_in server_addr;
    char send_buf[8000], recv_buf[8000];
    
    bzero(&server_addr, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(9652);
    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    
    connect(socket_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    if (fork() == 0)
    {
        while (1)
        {
            bzero(&send_buf, sizeof(send_buf));
            printf("\n[client]> ");
            fgets(send_buf, sizeof(send_buf), stdin);
            send(socket_descriptor, send_buf, strlen(send_buf) + 1, 0);
        }
    }
    else
    {
        while (1)
        {
            bzero(&recv_buf, sizeof(recv_buf));
            recv(socket_descriptor, recv_buf, sizeof(recv_buf), 0);
            printf("\n[server] %s", recv_buf);
        }
    }
    return 0;
}