#include "NMEA.h"
#include <iostream>

NMEA::NMEA(){

	//Constructeur de la classe NMEA 	
	// Il permet de définir la taille du tableau de DATA PAYLOAD
	// Le constructeur ne sert a rien en l'état
	
	int nbFragment;  //Field2
        int noFragment;  //Field3
        int seqId; //sequential message ID for multi-sentence message
        char radioChannel; //Field5
        char suffix[2]; //
        int fillBit; //Field7
        char dataPayload[83]; //Field6
	std::cout << "creation trame" << std::endl;

};
NMEA NMEA::surcharge(){
	// ajoute un payload a un autre si le message est trop grand 
	NMEA test;

	return test;
};
void NMEA::represent(){

	//printf("%d\n,%d\n,%d\n,%c,   %c  \n",fillBit,nbFragment,seqId,radioChannel,dataPayload[54]);


}

