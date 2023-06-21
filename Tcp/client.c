#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>
#include <sys/socket.h> // for socket(), connect(), send(), recv() functions
#include <netinet/in.h> // for sockaddr_in, inet_addr() functions

int main()
{
    struct sockaddr_in client;
    int sock;
    char buffer[1024];

    // Create a TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP client socket created.\n");

    // Configure server address
    memset(&client, '\0', sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(5566);
    client.sin_addr.s_addr = INADDR_ANY;

    // Connect to the server

    if (connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0)
    {
        perror("[-]Connect error");
        exit(1);
    }

    printf("[+]Connected to server.\n");

    // Send data to the server

    printf("Enter data to send: ");
    fgets(buffer, 1024, stdin);

    int k = send(sock, buffer, strlen(buffer), 0);

    if (k < 0)
    {
        perror("[-]Send error");
        exit(1);
    }
    else
    {
        printf("[+]Data sent.\n");
    }
}