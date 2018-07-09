#include <iostream>
#include <vector>
#include <string>
#include "NMEA.h"

using namespace std;

char* champ_suivant(char* p){
	
	while(p 
	      && *p != 0
	      && *p !=','
	      && *p !='*'){
		
		p++; //tant que on tombe pas sur un délimiteur on incrémente	
			
	}
	if(p!=0){ return p+1;}
	cout << "champ_suivant" << endl;
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
int create_vector(char* vector, char *p){

	int i=0;
	long len =0;
	int res;
	int sizeField = 0;
	cout << "avant le while" << endl;
	while(p != NULL)
	{
	
		//on va construire le vecteur a mettre dans l'objet NMEA
		cout << "avant champsuivant" << endl;
		p = champ_suivant(p);
		if(i<3){
			res = nmea_uint(p);
			memcpy(vector+i*sizeof(int),&res,sizeof(int));
			//on ajoute les 3 ints à la structure
			len+=sizeof(int);
		}
		else
		{
		sizeField = champ_suivant(p)-p;
		memcpy(vector+len,p,sizeField);

		len +=sizeField; //perte de temps 
		p++;
		i++; //elimine les 3 ints
	}
	
	}
	return 0;
	}

/*
int create_vector(char *vector,char* p, int size){

	long len=0; //taille entre 2 delimiter
	char *pos;
       	pos = vector;// +9*8;
	size = size -(champ_suivant(p) - p);
	p = champ_suivant(p); //ON ENLEVE '!AIVDM,'

	
	while(p != NULL && len < size){ // IL FAUT trame.length() - (nbDelimiter) - "!AIVDM".length
		memcpy(pos+len,p,champ_suivant(p)-p-1); //copy de la chaine entre 2 delimiter
		len +=champ_suivant(p)-p-1; //on décale d'un delimiter
		p = champ_suivant(p);		
		size--;
	}
	printf("size avant envoi -> %d\n",size);
	return size;//renvoi la taille des éléments après parsing 
}
*/

int convertInt(char *vector){
	
	//IL FAUT CONVERTIR EN INT LES 3 PREMIERS BLOCS
	/* Le vecteur créé précedement n'est chargé que au dessus du 9eme byte donc on a la place
	 * de mettre des ints à la place des char précédents
	 */

	char* p =  &(*(vector+9)); //pointe sur vector[9]  

	int nb;
	int*pNb=&nb;
	int i = 0;
	while(p
		&& *p >= 48
		&& *p <= 57){	//test si une valeur numérique -> permet de s'arreter au 3eme bloc

		nb  = *p - '0';
		memcpy(vector+sizeof(int)*i,pNb,sizeof(int));
		p++;
		i++;
	}
	//i représente maintenant le nombre de chiffre int -> permet de déterminer la taille de la trame 
	return i;
}

int chargeNMEA(char *vector,void *NMEA,unsigned long size){
	// charge la structure NMEA avec le vecteur contenant la liste parsée sans les delimiters
	memcpy(NMEA,vector,size*sizeof(char)); //charge l'objet NMEA

	return 0;
}
int main(){
		string trameN = "!AIVDM,2,1,3,B,55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53,7*3E";
		/*
		char* pointeur = &trameN[0];
		unsigned long size = trameN.length();
		printf("TAILLE DEPART -> %ld \n",size);

		int sizeInt;
		int sizeDataPayload;
		char vector[trameN.length()-7+9-6]; //tableau contenant la trame sans delimiter
		char *pVect = &vector[9];//on pointe le 10eme byte pour laisser la place a la conversion des ints 
		*/
		/********************************************************
		 * 							*
		 * 		DEROULEMENT DU PROGRAMME 		*
		 *
		 ********************************************************/
		char *pointeur = &trameN[0];
		NMEA trameStruct;
		char* pTrame =(char*) &trameStruct;	
		cout << "creation pointeur" << endl;
		create_vector(pTrame,pointeur); // on travaille directement sur l'objet trame


		/*
		sizeDataPayload = create_vector(pVect,pointeur,size); //avec les int
		size = sizeDataPayload +9;
		pVect = vector; //cettte fois on se place des le début de vetcor 
		sizeInt = convertInt(pVect);
		
		sizeDataPayload = detect_size(sizeDataPayload,sizeInt);
		// -------------------------------> ICI CREATION DE L'OBJET NMEA
		NMEA trameparsed(sizeDataPayload);
		void* pNMEA = (void*) &trameparsed;
		
		chargeNMEA(pVect,pNMEA,size);
		for(int i=0;i<=size;i++){
			printf("case %d ---> %c\n",i,vector[i]);
		}
		trameparsed.represent();
		*/
		return 0;
}

