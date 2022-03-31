#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;	//서버의 소켓~ 굳이 서버/클라이언트 저장할 이유 없음

	struct sockaddr_in serv_addr;
	char message[30];	//서버에서 보낸 메세지를 저장
	int str_len;

	if(argc!=3)	//매개변수 검증~~
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0); //pf_inet : ipv4 형식 지정 / sock_stream : TCP 사용

	if(sock == -1)
		error_handling("socket() error");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)	//connect
		error_handling("socket() error");
	str_len=read(sock,message,sizeof(message)-1);	//recieve	read()= 0성공 / -1실패 반환
	if(str_len==-1)
		error_handling("read() error!");
	printf("Message from server : %s \n", message);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
