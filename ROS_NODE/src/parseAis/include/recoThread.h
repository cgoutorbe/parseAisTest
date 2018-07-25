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

#include "ros/ros.h"
#include "std_msgs/String.h"

class recoThread{
	public:
		int connect_socket( struct sockaddr_in* adr,int size,int sock);
		int adr_init(struct sockaddr_in* adr);
		int receive_NMEA(int sock);
		int is_disconnected(int sock);
		int publish_buffer(char* buffer);
		int reception_loop();

		std_msgs::String msg;
		char buffer[1000];
		//int sock;

//	private:
	ros::Publisher NMEAPub;
};
