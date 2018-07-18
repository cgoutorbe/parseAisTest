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
#include <thread>
#include <mutex>
#include <time.h>
#include <fcntl.h>

int connect_socket(int sock,struct sockaddr_in* adr,int sizeAdr) {
	

       	if((connect(sock,(struct sockaddr*) adr,sizeAdr) ==-1))
        {
                perror("failed to connect");
                exit(1);
        }
        return sock;
}

int main(){


        //int sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP );
        struct sockaddr_in adr;
        adr.sin_port = htons(10110);
        adr.sin_family = AF_INET;
	int sizeAdr = sizeof(adr);

	struct timeval timeout;
	timeout.tv_sec = 10;//SOCKET_READ_TIMEOUT_SEC;
	timeout.tv_usec = 0;

	char buffer[100];
	while(1){
        	int sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP );
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
	
		sock = connect_socket(sock,&adr,sizeAdr);
		std::cout << sock << std::endl;
		//fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK);
		int b = recv(sock,buffer,100,0);
		//std::cout << "fr " << b << std::endl;
		printf("%s\n",buffer);
		memset(buffer,'\0',100);

		shutdown(sock,SHUT_RDWR);
		sleep(10); // 3 supposed to be enough 10 is more robust
		close(sock);
	}


	return 0;
}
