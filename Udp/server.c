
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <time.h>
int main(int argc, char *argv[])
{
    int s, t, cp;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024];
    time_t ct;
    if (argc != 2)
    {
        printf("\n usage:client<server-adr><port>");
        exit(0);
    }
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("error in socket creation");
        exit(0);
    }
    bzero((char *)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons((short)atoi(argv[1]));
    servaddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(s, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind");
        exit(0);
    }
    t = sizeof(cliaddr);
    memset(buffer, 0, 100);
   while (1) {
        if (recvfrom(s, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &t) < 0) {
            perror("error in recvfrom");
            exit(0);
        }

        ct = time(NULL);
        sprintf(buffer, "%s", ctime(&ct));

        if (sendto(s, buffer, strlen(buffer), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) < 0) {
            perror("error in sendto");
            exit(0);
        }
        memset(buffer, 0, sizeof(buffer));
    }

    close(s);
    return 0;
}