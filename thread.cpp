#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>


int create_socket(){

	//creer une socket permettant de communiquer avec l'antenne au port
	//127.0.0.1::10110
	int sock;
	int port = 10110;
	struct hostent *hote;
	struct sockaddr_in adr; //definition du socket

	if ( (sock= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ) //AF_INET for IPv4 
	{
		perror("client socket");
		exit(1);
	}
	adr.sin_family=AF_INET;
	adr.sin_port=htons(port);


	if (connect(sock, (struct sockaddr *)&adr, sizeof(adr))==-1)
	{
		//connect to the socket
		perror("connect");
		exit(1);
	}
	char c;
	/*
	do
	{
		c = EOF;
		read(sock, &c, 1);
		recv(sock)
		printf("%c \n",c);
		//putchar(c);
	}
	while (c!=EOF);
	*/

	return sock;
}

int fetchUDP(){

	//recoit une trame sur la socket créée précédemment 
	


	return 0;
}

int main(){

	create_socket();



	return 0;
}
