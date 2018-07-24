#include <iostream>
#include <string>
#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/UInt32MultiArray.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "gps_common/GPSFix.h"//GPS data
#include "Message.h"
#include <cmath>
#include "pk_msg/Ais.h" //type message to send Ais infos
#include "pk_msg/AisMultiArray.h"
using namespace std;
//-----------------------------------------------------------------------------------------------
//-----------------------------------------FONCTIONS---------------------------------------------


double lat_bats = 0;
double long_bats = 0;
pk_msg::Ais ais_sub;


//TODO Verifier avec Charlie les type de donnees envoyées

void ChatBack_Coor_Cata(const gps_common::GPSFix::ConstPtr& msg){
	lat_cata = msg->latitude;
	long_cata = msg->longitude;
}
void ChatBack_Ais(const pk_msg::Ais::ConstPtr& msg){
	//ais_sub.header = msg->header
	ais_sub.type = msg->type;
	ais_sub.mmsi = msg->mmsi;
	ais_sub.status = msg->status;
	ais_sub.rate_of_turn = msg->rate_of_turn;
	ais_sub.speed_over_ground = msg->speed_over_ground;
	ais_sub.position_accuracy = msg->position_accuracy;
	ais_sub.longitude = msg->longitude;
	ais_sub.latitude = msg->latitude;
	ais_sub.course_over_ground = msg->course_over_ground;
	ais_sub.heading = msg->heading;
}

double Calcul_dist(double lat_A,double long_A,double lat_B,double long_B){
	double R = 6371000; //Rayon de la terre en metre
	double D = R * acos(sin(lat_A) * sin(lat_B) + cos(lat_A) * cos(lat_B) * cos(long_B - long_A));
	return D;
}

void Maj_tab(Ais tab_ais[], Ais ais_sub, double distance){
	for(int i(0); i < tab_ais.length(); i++){
		if(ais_sub.mmsi == tab_ais[i].mmsi) {t_dist[i].distance = distance;} //Maj de la distance avec nouvelles coordonnees
		else if(tab_ais[i] == 0){
			tab_ais[i] = ais_sub;
			tab_ais[i].distance = distance;
		}
		else {continue;}
	}

}//TODO faire la fonction qui regarde si le nom existe si oui il corrige si non il cree une autre ligne et ajoute la dsitance
//-----------------------------------------------------------------------------------------------
//-----------------------------------MAIN--------------------------------------------------------

int main(int argc, char **argv){
//Init variable
	double distance;
	pk_msg::Ais tab_ais[100];
	pk_msg::Ais ais_null;

//Init Table of Ais Message
for(int i(0); i < 100 ; i++){
	tab_ais[i]= ais_null;
}
//Initialisation ROS
	ros::init(argc, argv, "calc_distance_node");
	ros::NodeHandle n;
	ros::Rate loop_rate(20);
//Publisher & Creation message
	ros::Publisher chat_dist = n.advertise<pk_msg::AisMultiArray>("Ais_tab", 1000);
	pk_msg::AisMultiArray Ais_Table;
//Subscriber
	ros::Subscriber sub_coor_cata = n.subscribe("Ais_infos", 1000, ChatBack_Ais);
	ros::Subscriber sub_coor_bats = n.subscribe("Lat_Long_cata", 1000, ChatBack_Coor_Cata); //TODO changer le nom du message GPS

	while(ros::ok()){
		//Calcul de distance
		distance = Calcul_dist(lat_cata, long_cata, ais_sub.latitude, ais_sub.longitude);
		//mise a jour des tables
		Maj_tab(tab_ais, ais_sub, distance);
		//Remplissage du message & Publication
		for(int i(0); i < 100 ; i++){
			if (tab_ais[i].mmsi != 0){
				Ais_Table.data.push_back(tab_ais[i]); //peut etre faire a la main car ROS n accepte pas ca
			}else
				Ais_Table.data.push_back(ais_null);
		}
		chat_dist.publish(Ais_Table);
		ros::spinOnce();
		loop_rate.sleep();
		}
	return 0;
}

//-----------------------------------------------------------------------------------------------
//---------------------------------------COMMENTAIRES--------------------------------------------
