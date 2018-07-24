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
#include "recoThread.h"

#include "ros/ros.h"
#include "std_msgs/String.h"

int connect_socket(int sock,struct sockaddr_in* adr, int size) {


	std::cout << "CONNECTION DU SOCKET\n\n"<< std::endl;

	if(connect(sock,(struct sockaddr*) adr,size) ==-1)
	{
		perror("failed to connect");
		exit(1);
	}
	return sock;
}

int adr_init(struct sockaddr_in* adr){
	//initializes a socket 	
	
	(*adr).sin_port = htons(10110);
	(*adr).sin_family = AF_INET;
	return 0;
}

int receive_NMEA(int sock, char* buffer){
	// receives NMEA Strings from rtl_ais via TCP
	// the recv runs for 5 seconds 
	time_t start,end;
	double elapsed = 0;
	start = time(NULL);
	int b;
	std::cout << "5 SECONDES DE RECEPTION\n" << std::endl;
	while(elapsed <= 5){ //while 5 seconds 
		
		b = recv(sock,(void*) buffer,1000,MSG_DONTWAIT);
		if(b != 0 && b != -1){publish_buffer(buffer);}// calls		
		
		end = time(NULL);
		elapsed = difftime(end,start);;
	}
	std::cout << "FIN DE RECEPTION" << std::endl;
	shutdown(sock,SHUT_RDWR);
	close(sock);

	return 0;
}

int is_disconnected(int sock){
	char temp;
	//test whether the socket is connected or not 
	

	if(recv(sock,&temp,1,MSG_DONTWAIT)==0){
	
		std::cout << "SOCKET DECONNECTE" << std::endl;
		return 1;
	}
	else {
		return 0;
	}

}

int publish_buffer(char* buffer){
	

	NMEA.publish(buffer);
	//std::cout << buffer << std::endl;

	//memset((void*) buffer,'\0',1000);//set buffer back to empty

	//sends strings to parser 
	return 0;
}

int main(){
	
	//init variables
	
	struct sockaddr_in adr;
	char buffer[1000];
	char *p = &buffer[0];
	struct sockaddr_in* pAdr = &adr;

	adr_init(&adr); 
	int size = sizeof(adr);

	ros::init(argc,argv, "get_nmea_strings");
	ros::NodeHandle n;
	
	ros::Publisher NMEA = n.advertise<std_msgs::String>("NMEA:",1000);
	ros::Rate loop_rate(20); //TODO find the right frequency

	while(ros::ok()){
		
		
		int sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP );
		sock = connect_socket(sock,pAdr,size);

		std::thread rec (receive_NMEA, sock, p);
		rec.join();
		std::thread use (use_buffer,p);
		use.join();

		ros::spinOnce();
		loop_rate.sleep();

		
	}

	return 0;
}
