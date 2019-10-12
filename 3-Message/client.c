#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256
#define MONEY_DIGIT_SIZE 10

void DieWithError(char *);
int prepare_client_socket(int);
void my_scanf(char *,int);
void commun(int);

int main(int argc, char *argv[])
{
    if (argc != 3)
        DieWithError("usage: ./client ip_address port");

    int sock = prepare_server_socket(argv[1]), atoi(argv[2]);

    commun sock;

    return 0;
}

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

int prepare_client_socket(char *ipaddr,int port)
{
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        DieWithError("socket()faild");
    }
    struct sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr(ipaddr);
    target.sin_port = htons(port);
    if (connect(sock, (struct sockaddr*)&target, sizeof(target)) < 0)
    {
        DieWithError("connect()failed");
    }

    return sock;
}