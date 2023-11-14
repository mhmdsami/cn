#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    struct sockaddr_in server_addr, client_addr;
    int socket_descriptor, client_descriptor;
    char str[100];
    time_t tick;
    socklen_t client_len;
    
    client_len = sizeof(client_addr);

    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_port = htons(5600);
    server_addr.sin_addr.s_addr = htonl(0);

    bind(socket_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(socket_descriptor, 50);

    while (1)
    {
        client_descriptor = accept(socket_descriptor, (struct sockaddr *)&client_addr, &client_len);
        tick = time(NULL);
        snprintf(str, sizeof(str), "%s", ctime(&tick));
        printf("%s", str);
        send(client_descriptor, str, sizeof(str), 0);
    }
}