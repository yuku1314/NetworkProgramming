#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <regex.h>

#define BUF_SIZE 256

void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}
void common(int sock){
	char buf[BUF_SIZE]; 
	char buf_old[BUF_SIZE]; 
	char buf2[2*BUF_SIZE]; 
	int len_r;
	char response[BUF_SIZE];
	regex_t regBuf;
	regmatch_t regMatch[1];
	buf_old[0]='\0'; 
	char *uri;
	char result[100];	
	result[0]='\0';
	
	const char *pattern="GET[^\\n]+HTTP";
	
	if(regcomp(&regBuf,pattern,REG_EXTENDED | REG_NEWLINE)!=0){
		DieWithError("regcomp failed");
	}
	
	while((len_r=recv(sock,buf,BUF_SIZE,0))>0){
		buf[len_r]='\0';
		sprintf(buf2,"%s%s",buf_old,buf);
		printf("%s\n",buf); //←リクエストを表示
		
		if(regexec(&regBuf,buf2,1,regMatch,0)!=0){
			int startIndex=regMatch[0].rm_so;
			int endIndex=regMatch[0].rm_eo;
			strncpy(result,buf2+startIndex,endIndex-startIndex);
		}
		
		if(strstr(buf2,"\r\n\r\n")){
			break;
		}
		sprintf(buf_old,"%s",buf);
	}
	regfree(&regBuf);
	
	if (result[0] != '\0') {
		uri = strtok(result, " ");
		uri = strtok(NULL, " ");
		printf("%s\n",uri);
	} else {
		DieWithError("No URI");
	}
	if(len_r<=0){
	DieWithError("recv()failed");
	}
	printf("recived HTTP request.\n");//受け取ったことを表示
	
	sprintf(response,"HTTP/1.1 200 OK\r\n");
	if(send(sock, response, strlen(response), 0) != strlen(response))
	DieWithError("send() sent a message of unexpected bytes");
    
    sprintf(response, "Content-Type: text/html; charset=utf-8\r\n");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
        
    sprintf(response, "\r\n");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
    
    sprintf(response, "<!DOCTYPE html><html><head><title>");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
    
    sprintf(response, "ネットワークプログラミングのwebサイト");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
    
    sprintf(response, "</title></head><body>ネットワークダイスキ</body></html>");
    if(send(sock, response, strlen(response), 0) != strlen(response))
        DieWithError("send() sent a message of unexpected bytes");
	
}


int main(int argc,char **argv){
	struct sockaddr_in clientAddress;
	unsigned int szClientAddr;
	int cliSock;
	int servSock=socket(PF_INET,SOCK_STREAM,0);
	if (servSock < 0){
        DieWithError("socket() failed");
	}
	
	struct sockaddr_in servAddress;
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

//10.13.64.39
