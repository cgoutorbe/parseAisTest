#include <iostream>
#include <vector>
#include <string>
#include "NMEA.h"
#include "check.h"
#include "parsePoint.h"
#include "ros/ros.h"
#include "std_msgs/String.h"

using namespace std;
char *pointeur;

char* champ_suivant(char* p){
	
	while(p 
	      && *p != 0
	      && *p !=','
	      && *p !='*'){
		
		p++; //tant que on tombe pas sur un délimiteur on incrémente	
			
	}
	if(p!=0){ return p+1;}
	return NULL;

}

unsigned int  nmea_uint( char *p )
{

    // code frome bcl/aisparser on github

    unsigned int i = 0;

    while (   p 
           && (*p != 0) 
           && (*p != ',') 
           && (*p != '*') )
    {
        i *= 10;
        i += *p - '0';
        p++;
    }

    return i;    
}

int end_trame(char* p,int i){

	if(*(p-1) == ','){ return i-1;}
	
	return i;

}

char* create_vector(char* vector, char *p){

	int i=0;
	long len =0;
	int res;
	int sizeField = 0;
	int y=4; //nombre de ',' 
	while(p != NULL && y)
	{
		y=end_trame(p,y);
		//on va construire le vecteur a mettre dans l'objet NMEA
		p = champ_suivant(p);
		if(i<3){
			res = nmea_uint(p);
			memcpy(vector+i*sizeof(int),&res,sizeof(int));
			len+=sizeof(int);
		}
		else
		{
		sizeField = champ_suivant(p)-p-1;
		memcpy(vector+len,p,sizeField);
		len +=sizeField; //perte de temps 
	}
		i++; //elimine les 3 ints
	}
	p = champ_suivant(p); //decale de dataPayload
	return champ_suivant(p); //decale du FillBit on a le checksum direct
	}
void chat_back(const std_msgs::String::ConstPtr& msg,const std_msgs::String& data_msg){
	
	// init of pointer to the newly received buffer 	
	unsigned char checksum;
	unsigned char* pchecksum = &checksum;
	pointeur = &msg
	char* pCheck;
	NMEA trameStruct;
	char* pTrame = (char*) &trameStruct;
	pCheck = create_vector(pTrame,msg);
	if( check_nmea_checksum(pCheck,msg)){
		//data_msg = trameStruct.dataPayload;
		data_msg.data = std::string(trameStruct.dataPayload);
		//memcpy(data_msg,(char*) trameStruct.dataPayload,83*sizeof(char));
	}
	else{
		//erreur de checksum on remet le msg a 0 
		memset(data_msg,'0',83);

	}
}

int main(char *pointeur){ //rename into main to test

		string trame;
		std_msgs::String msg;

		ros::init(argc,argv,"ais_parser_node");
		ros::Nodehandle n;
	
		ros::Subscriber trameNMEA = n.subscribe("NMEA",1000,chat_back((void*) &msg);
		ros::Publisher Data = n.advertise<std_msgs::String>("DataPayload", 83);
		
		char *pCheck;
		NMEA trameStruct;
		char* pTrame =(char*) &trameStruct;	

		pCheck = create_vector(pTrame,pointeur);
		trameStruct.represent();
		
		/********************************************************
		 * 							*
		 * 		     AVEC CHECKSUM                      * 
		 * 							*
		 ********************************************************/
		
		unsigned char checksum;
		unsigned char* pchecksum = &checksum;

		cout << check_nmea_checksum(pCheck,pointeur) << endl;

		ros::Rate loop_rate(20);
		while(ros::ok()){
			
		//	msg = trameStruct.dataPayload;
			Data.publish(msg);

			ros::spinOnce();
			loop_rate.sleep();

		}



		return 0;
}

