#include <iostream>
#include <vector>
#include <string>
#include "NMEA.h"
#include "check.h"

using namespace std;

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

int main(){
		string trameN = "!AIVDM,2,1,3,B,55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53,7*3E";
		string trameN2 = "!AIVDM,1,1,,A,15N;<J0P00Jro1<H>bAP0?vL00Rb,0*1B";

		string trameN1 = "!AIVDM,1,1,,A,19NWoq000Wrt<RJHEuuqiWlN061d,0*5F";
		/********************************************************
		 * 							*
		 * 		DEROULEMENT DU PROGRAMME 		*
		 * 							*
		 ********************************************************/

		char *pointeur = &trameN[0];
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

		//printf(" avant -> %c",checksum);
	        //nmea_checksum(pchecksum,pointeur);
		//printf(" apres-> %c",checksum);
		cout << check_nmea_checksum(pCheck,pointeur) << endl;



		return 0;
}

