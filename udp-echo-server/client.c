#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

void print_err_and_exit(const char *err)
{
    perror(err);
    exit(1);
}

int main(int argc, char *argv[])
{
    int socket_descriptor;
    char buff[1024];
    struct sockaddr_in server_addr;
    socklen_t server_len;
    
    server_len = sizeof(server_addr);
    socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (socket_descriptor < 0)
        print_err_and_exit("Cannot open socket");

    bzero(&server_addr, server_len);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(5669);

    while (1)
    {
        printf("Enter data to be sent > ");

        bzero(buff, sizeof(buff));
        fgets(buff, sizeof(buff), stdin);

        if (sendto(socket_descriptor, buff, sizeof(buff), 0, (struct sockaddr *)&server_addr, server_len) < 0)
            print_err_and_exit("Cannot send data");

        printf("Data sent to UDP server: %s", buff);

        bzero(buff, sizeof(buff));

        if (recvfrom(socket_descriptor, buff, sizeof(buff), 0, (struct sockaddr *)&server_addr, &server_len) < 0)
            print_err_and_exit("Cannot receive data");

        printf("Received data from server: %s\n", buff);
    }

    close(socket_descriptor);
    return 0;
}