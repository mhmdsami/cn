#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>

void print_err_and_exit(const char *err)
{
    perror(err);
    exit(1);
}

int main(int argc, char *argv[])
{
    int socket_descriptor;
    char buff[1024];
    struct sockaddr_in client_addr, server_addr;
    socklen_t client_len;

    client_len = sizeof(client_addr);
    socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);

    if (socket_descriptor < 0)
        print_err_and_exit("[err] Cannot open socket");

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(5669);

    printf("[server] Server running at port %d\n", server_addr.sin_port);

    if (bind(socket_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        print_err_and_exit("[err] Error in binding the port");

    while (1)
    {
        bzero(&buff, sizeof(buff));

        if (recvfrom(socket_descriptor, buff, sizeof(buff), 0, (struct sockaddr *)&client_addr, &client_len) < 0)
            print_err_and_exit("Cannot receive data");

        printf("Message is received: %s", buff);

        if (sendto(socket_descriptor, buff, sizeof(buff), 0, (struct sockadddr *)&client_addr, client_len) < 0)
            print_err_and_exit("[err] Cannot send data to client");

        printf("Sent data to UDP Client: %s\n", buff);
    }

    close(socket_descriptor);
    return 0;
}