#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256
#define MONEY_DIGIT_SIZE 10

void DieWithError(char *);
int prepare_server_socket(int);
void commun(int); //プロトタイプ宣言

int main(int argc, char *argv[])
{
    struct sockaddr_in clientAddress;
    unsigned int szClientAddr;
    int cliSock;

    int servSock = prepare_server_socket(10001);

    listen(servSock, 5);

    while (1)
    {
        szClientAddr = sizeof(clientAddress);
        cliSock = accept(servSock, (struct sockaddr *)&clientAddress, &szClientAddr);

        common(cliSock);

        close(cliSock);
    }
    close(cliSock);

    return 0;
}

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

int prepare_sever_socket(int port)
{

    int servSock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        DieWithError("socket()faild");
    }
    struct sockaddr_in severAddress;
    severAddress.sin_family = AF_INET;
    severAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    severAddress.sin_port = htons(port);

    bind(servSock, (struct sockaddr *)&severAddress, sizeof(severAddress));

    return servSock;
}