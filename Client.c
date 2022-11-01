// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8300

#include <unistd.h>
#include <arpa/inet.h>
#define _OPEN_SYS_SOCK_IPV6

int inet_pton(int a_inet, const char *sr_address, void *ds_address);

int main(int argd, char const *argdv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in server_add;
    char *hello = "Hello, from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&server_add, '0', sizeof(server_add));

    server_add.sin_family = AF_INET;
    server_add.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_add.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&server_add, sizeof(server_add)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);
    return 0;
}
