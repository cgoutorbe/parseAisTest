#ifndef NMEA_H
#define NMEA_H

class NMEA{

	
	public:
		NMEA(const int size);
		
		//Pour l'instant les attributs sont public
		//il faudra ajouter getter et setter et les décaler en private
		// commentaire test branche
	
		int nbFragment;  //Field2
		int noFragment;  //Field3
		int seqId; //sequential message ID for multi-sentence message
		char radioChannel; //Field5
		int fillBit; //Field7
		char suffix[2]; //
		char dataPayload[83]; //Field6

		NMEA surcharge(); 
		void represent();
};
#endif
