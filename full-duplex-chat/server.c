#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc,char *argv[])
{
    int client_socket_descriptor, socket_descriptor;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char recv_buf[8000], send_buf[8000];
    
    bzero(&server_addr, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(9652);
    
    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    
    bind(socket_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(socket_descriptor, 5);
    printf("Server is running...\n");
    
    client_socket_descriptor = accept(socket_descriptor, (struct sockaddr *)&client_addr, &client_len);

    if (fork() == 0)
    {
        while (1)
        {
            bzero(&recv_buf, sizeof(recv_buf));
            recv(client_socket_descriptor, recv_buf, sizeof(recv_buf), 0);
            printf("\n[client] %s", recv_buf);
        }
    }
    else
    {
        while (1)
        {
            bzero(&send_buf, sizeof(send_buf));
            printf("\n[server]> ");
            fgets(send_buf, sizeof(send_buf), stdin);
            send(client_socket_descriptor, send_buf, strlen(send_buf) + 1, 0);
        }
    }
    return 0;
}