#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#define PORT 8300


int main(int argd, char const *argdv[])
{
    int serv_fd, new_socket, value_read;
    struct sockaddr_in add;
    struct passwd* pd; //
    int opt = 1;
    int addrlen = sizeof(add);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    pid_t pr_id;
    char *user = "nobody";


    printf("execve=0x%p\n", execve);


    // Creating socket file descriptor
    if ((serv_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }


    // Forcefully attaching socket to the port 8080
    if (setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
  
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = INADDR_ANY;
    add.sin_port = htons( PORT );


    // Forcefully attaching socket to the port 8080
    if (bind(serv_fd, (struct sockaddr *)&add, sizeof(add))<0)
    {
        perror("Bind Failed");
        exit(EXIT_FAILURE);
    }
    if (listen(serv_fd, 3) < 0)
    {
        perror("Listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(serv_fd, (struct sockaddr *)&add,(socklen_t*)&addrlen))<0)
    {
        perror("Accept");
        exit(EXIT_FAILURE);
    }    
    pr_id = fork();
    if (pr_id == 0) {
        if ((pd = getpwnam(user)) == NULL) {
            perror("No UID found for the user nobody");
        }
        setuid(pd->pw_uid);
        value_read = read(new_socket , buffer, 1024);
        printf("%s\n", buffer);
        send(new_socket , hello , strlen(hello) , 0);
        printf("Hello message sent\n");
        exit(0);
    }
    wait(NULL);
    return 0;
}
