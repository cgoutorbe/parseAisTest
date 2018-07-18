#include <iostream>
#include <string>
#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/UInt32MultiArray.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "gps_common/GPSFix.h"//GPS data
#include <cmath>

using namespace std;
//-----------------------------------------------------------------------------------------------
//-----------------------------------------FONCTIONS---------------------------------------------

string nom_bat = "";
double lat_bats = 0;
double long_bats = 0;
double lat_cata = 0;
double long_cata = 0;

//TODO Verifier avec Charlie les type de donnees envoyées

void ChatBack_Coor_Cata(const gps_common::GPSFix::ConstPtr& msg){
	lat_cata = msg->latitude;
	long_cata = msg->longitude;
}

void ChatBack_Nom_Bat(const std_msgs::String::ConstPtr& msg){
	nom_bat = msg->data;
}

void ChatBack_Coor_Bats(const std_msgs::Float64MultiArray::ConstPtr& msg){
	lat_bats = msg->data[0];
	long_bats = msg->data[1];
}

double Calcul_dist(double lat_A,double lon_A,double lat_B,double lon_B){
	R = 6371000; //Rayon de la terre en metre
	D = R * arcos(sin(lat_A) * sin(lat_B) + cos(lat_A) * cos(lat_B) * cos(long_B - long_A));
	return D;
}

void Maj_tab(double dist[], string nom[], string nom_B, double distance){
	for(int i(0); i<dist; i++){
		elif(nom_B = nom[i]){dist[i] = distance} //Maj de la distance avec nouvelles coordonnees
		elif(nom[i] = "NOM#"){
			nom[i] = nom_B;
			dist[i] = distance;}
		else
			continue;
	}

}//TODO faire la fonction qui regarde si le nom existe si oui il corrige si non il cree une autre ligne et ajoute la dsitance
//-----------------------------------------------------------------------------------------------
//-----------------------------------MAIN--------------------------------------------------------

int main(int argc, char **argv){
//Init variable
	double dist;
	string nom_bats[100];
	float dist[100];
	for(int i(0); i<nom; ++i){
		dist[i] = pow(10,100);
		nom_bats = "NOM#";
	}
//Initialisation ROS
	ros::init(argc, argv, "calc_distance_node");
	ros::NodeHandle n;
//Publisher
	//ros::Publisher chat_tram = n.advertise<std_msgs::UInt32MultiArray>("Nom_bats", 1000);
	ros::Publisher chat_dist = n.advertise<std_msgs::Float64MultiArray>("Dist_bats", 1000);
	//ros::Publisher chat_dist = n.advertise<std_msgs::Float64MultiArray>("Dist", 1000);
//Creation message
	std_msgs::Float64Float64MultiArray dist_bateau;
//Subscriber
	ros::Subscriber sub_nom_cata = n.subscribe("ID", 1000, ChatBack_Nom_Bat);
	ros::Subscriber sub__coor_cata = n.subscribe("Lat_Long_Cata", 1000, ChatBack_Coor_Cata);
	ros::Subscriber sub_coor_bats = n.subscribe("Lat_Long_Bat", 1000, ChatBack_Coor_Bats);

	ros::Rate loop_rate(20);
	while(ROS::ok()){
		//Calcul de distance
		dist = Calcul_dist(lat_cata,long_cata,lat_bats,long_bats); //TODO a voir si l'on ne met pas dans la fonction
		//Remplissage & Publication
		for(int i(0); i<nom; ++i){
			dist_bateau.data[i] = dist[i]; //peut etre faire a la main car ROS n accepte pas ca
		}
		chat_dist.publish(dist_bateau);
		ros::spinOnce();
		loop_rate.sleep();
		}
	return 0;
}

//-----------------------------------------------------------------------------------------------
//---------------------------------------COMMENTAIRES--------------------------------------------
