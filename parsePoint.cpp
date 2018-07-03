#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct NMEA
{
        //Créer un objet trame séparant les différentes infomations
        int nbFragment;  //Field2
        int noFragment;  //Field3
        int seqId; //sequential message ID for multi-sentence message
        char radioChannel; //Field5
	char dataPayload[60]; //Field6
        int fillBit; //Field7
        char suffix[2]; //

}nmea;

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

int create_vector(char *vector,char* p, int size){

	long len=0; //taille entre 2 delimiter
	long maxlen = 50;
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

	return size; //on eleve une virgule de trop au debut
}
int detectSuffix(){
	//permet 



	return 0;
}

int chargeNMEA(char *vector,void *NMEA,unsigned long size){
	// charge la structure NMEA avec le vecteur contenant la liste parsée sans les delimiters
	
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
	
	memcpy(NMEA,vector,size*sizeof(char));

	return 0;
}

int main(){
		string trameN = "!AIVDM,2,1,3,B,55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53,0*3E";
		char* pointeur = &trameN[0];
		unsigned long size = trameN.length();
		char vector[trameN.length()-7+9-6]; //tableau contenant la trame sans delimiter
		NMEA trameparsed;
		void * pNMEA = &trameparsed;

		char *pVect = &vector[9];//on pointe le 10eme byte pour laisser la place a la conversion des ints 
		printf("adresse du vecteur: %p, adresse de case 9:%p\n\n",vector,pVect);

		size = create_vector(pVect,pointeur,size)+9; //avec les int
		pVect = vector; //cettte fois on se place des le début de vetcor 
		chargeNMEA(pVect,pNMEA,size);

		for(int i=0;i<size;i++){
			printf("case %d ---> %c\n",i,vector[i]);
		}

		cout << "nbFragment : " << trameparsed.nbFragment << endl;
		cout << "noFragment: " << trameparsed.noFragment << endl;
		cout << "radioChannel: " << trameparsed.radioChannel << endl;
		cout << "dataPayload: " << trameparsed.dataPayload<< endl;
	
		return 0;
}

