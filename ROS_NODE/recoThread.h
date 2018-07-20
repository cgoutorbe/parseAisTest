int connect_socket(int sock, struct sockaddr_in* adr,int size);
int adr_init(struct sockaddr_in* adr);
int receive_NMEA(int sock, char* buffer);
int is_disconnected(int sock);
int use_buffer(char* buffer);
int reception_loop();
