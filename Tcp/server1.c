#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>
#include <sys/socket.h> // for socket(), connect(), send(), recv() functions
#include <netinet/in.h> // for sockaddr_in, inet_addr() functions

int main(){

    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(socket<0){
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP client socket created.\n");

    struct sockaddr_in client,server;

    memset(&client,'\0',sizeof(client));
    server.sin_family = AF_INET;
    server.sin_port = htons(5526);
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(sock,(struct sockaddr *)&server,sizeof(server))<0){
        perror("[-]Bind error");
        exit(1);
    }

    printf("[+]Bind to port 5566.\n");

    if(listen(sock,5)<0){
        perror("[-]Listen error");
        exit(1);
    }

    printf("Listening...\n");


    socklen_t addr_size;
    addr_size = sizeof(client);
    int client_sock = accept(sock,(struct sockaddr *)&client,&addr_size);
    printf("[+]Client connected.\n");

    char buffer[1024];
    int rec = recv(client_sock,buffer,1024,0);

    if(rec<0){
        perror("[-]Receive error");
        exit(1);
    }
    else{
        printf("[+]Data received: %s\n",buffer);
    }

    close(sock);
    close(client_sock);
    


}