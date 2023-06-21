#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>
#include <sys/socket.h> // for socket(), connect(), send(), recv() functions
#include <netinet/in.h> // for sockaddr_in, inet_addr() functions


int main(){


    struct sockaddr_in client,server;
    socklen_t addr_size;
    int sock;
    char buffer[1024];

    // Create a TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");

    // Configure server address
    memset(&server,'\0',sizeof(server));
    server.sin_port = htons(5566);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    

    // Bind the socket to the server address
    int k = bind(sock,(struct sockaddr *)&server ,sizeof(server));
    if (k < 0)
    {
        perror("[-]Bind error");
        exit(1);
    }

    printf("[+]Bind to port %d\n", 5566);

    // Listen for clients
    listen(sock, 5);
    printf("Listening...\n");

    // Accept a client connection
    addr_size = sizeof(client);
    int client_sock = accept(sock, (struct sockaddr *)&client, &addr_size);
    printf("[+]Client connected.\n");
    // Receive data from the client
    int rec = recv(client_sock,buffer,1024,0);

    if(rec < 0){
        perror("[-]Receive error");
        exit(1);
    }
    else{
        printf("[+]Data received: %s\n",buffer);
    }

    return 0;
    


}