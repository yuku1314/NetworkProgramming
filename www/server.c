#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUF_SIZE 256

void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}
void common(int sock){
	char buf[BUF_SIZE]; 
	int len_r;
	if((len_r=recv(sock,buf,BUF_SIZE,0))<=0)
		DieWithError("recv()failed");
	buf[len_r]='\0';
	printf("%s\n",buf);
	if(send(sock,buf,strlen(buf),0)!=strlen(buf))
		DieWithError("send()sent a message of unexpected bytes");
}



int main(int argc,char **argv){
	int servSock=socket(PF_INET,SOCK_STREAM,0);
	int cliSock;
	unsigned int szClientAddr;
	struct sockaddr_in servAddress;
	struct sockaddr_in clientAddress;
	servAddress.sin_family=AF_INET;
	servAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddress.sin_port=htons(80);
	bind(servSock,(struct sockaddr*)&servAddress,sizeof(servAddress));
	listen(servSock,5);
	while(1){
		szClientAddr=sizeof(clientAddress);
		cliSock=accept(servSock,(struct sockaddr*)&clientAddress,&szClientAddr);
		common(cliSock);
		close(cliSock);
	}
	close(servSock);
	
	return 0;
}


