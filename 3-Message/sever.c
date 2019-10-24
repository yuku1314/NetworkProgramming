#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256
#define MONEY_DIGIT_SIZE 10
//プロトタイプ宣言
void DieWithError(char *);
int prepare_server_socket(int);
void commun(int); 
void read_until_delim(int, char *, char, int);
int get_current_balance();
void set_current_balance(int);

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

        commun(cliSock);

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

int prepare_server_socket(int port)
{

    int servSock = socket(PF_INET, SOCK_STREAM, 0);
    if (servSock < 0)
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

void read_until_delim(int sock, char *buf, char delimiter, int max_length)
{
    int len_r = 0;
    int index_letter = 0;

    while (index_letter < max_length - 1)
    {
        if ((len_r = recv(sock, buf + index_letter, 1, 0)) <= 0)
        {
            //エラー
            printf("接続が切れました\n");
            return;
        }
        if (buf[index_letter] == delimiter)
        {
            break; //区切り文字を受信→ループを抜ける
        }
        else
        {
            index_letter++;
        }
    }

    buf[index_letter] = '\0';
}

int get_current_balance()
{
    return 1000000;
}

void set_current_balance(int new_balance)
{
    return;
}

void commun(int sock)
{
    char buf[BUF_SIZE];
    int balance = get_current_balance();

    read_until_delim(sock, buf, '_', BUF_SIZE);
    balance += atoi(buf);
    read_until_delim(sock, buf, '_', BUF_SIZE);
    balance -= atoi(buf);

    set_current_balance(balance);

    sprintf(buf, "%d_", balance);
    if (send(sock, buf, strlen(buf), 0) != strlen(buf))
    {
        DieWithError("send() sent a message of unexpected bytes");
    }
}