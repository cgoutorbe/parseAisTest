#include <iostream>
#include <vector>
using namespace std;

struct NMEA
{
        //Créer un objet trame séparant les différentes infomations
        int nbFragment;  //Field2
        int noFragment;  //Field3
        int seqId; //sequential message ID for multi-sentence message
        char radioChannel; //Field5
        string dataPayload; //Field6
        int fillBit; //Field7
        string suffix; //


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

int create_vector(char *vector,char* p){


	long len=0; //taille entre 2 delimiter
	long maxlen = 50;
	char *pos = vector +9*8;
	printf("adresse vecteur %p, adresse debut de while %p\n\n",vector,pos);
	p = champ_suivant(p); //ON ENLEVE '!AIVDM,'
	while(p != NULL && len < 63){ // IL FAUT trame.length() - (nbDelimiter) - "!AIVDM".length
		printf("-------LEN -------> %ld",len);	
		memcpy(pos+len,p,champ_suivant(p)-p-1); //copy de la chaine entre 2 delimiter

		printf("string copiée --> %s adress %p\n",pos,&pos+len*4);
	//	printf("taille du bloc -> %ld\n",(-1)*(p-champ_suivant(p)));


		len +=champ_suivant(p)-p-1; //on décale a chaque passage le '-' est pour le float
		p = champ_suivant(p);		
	}

	return 0;
}

int chargeNMEA(char *vector,void *NMEA){
	// charge la structure NMEA avec le vecteur contenant la liste parsée sans les delimiters
	
	//IL FAUT CONVERTIR EN INT LES 3 PREMIERS BLOCS
	/* Le vecteur créé précedement n'est chargé que au dessus du 9eme byte donc on a la place
	 * de mettre des ints à la place des char précédents
	 */

	char *p = &(*vector)+9*8; //on se laisse la place pour mettre les ints
	printf("adresse pointée ->  %p contenu -> %c\n",p,*p);
	int nb;
	int*pNb=&nb;
	int i = 0;
	while(p
		&& *p >= 48
		&& *p <= 57){	//test si une valeur numérique -> permet de s'arreter au 3eme bloc
		
		printf(" conversion de %c en %d",*p,(*p-'0'));
		nb  = *p - '0';
		memcpy(vector+sizeof(int)*i,pNb,sizeof(int));
		p++;
		i++;
	}
	

	//maintenant que les ints sont converties on charge dans la structure
	memcpy(NMEA,vector,20*sizeof(char));

		

	return 0;
}



int main(){
		printf("sizeof int ----->>>>>>%lu",sizeof(int));
		string trameN = "!AIVDM,2,1,3,B,55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53,0*3E";
		printf("len trameN %lu",trameN.length());
		char* pointeur = &trameN[0];
		char vector[trameN.length()-7+9-6]; //tableau contenant la trame sans delimiter
		NMEA trameparsed;
		void * pNMEA = &trameparsed;

		char *pVect = &vector[0];
			
		create_vector(pVect,pointeur);
		chargeNMEA(pVect,pNMEA);
		//printf("vector apres parse ---> %d \n",vector);
		cout << "nbFragment :" << trameparsed.nbFragment << endl;
		cout << "noFragment" << trameparsed.noFragment << endl;
		cout << "radioChannel" << trameparsed.radioChannel << endl;
		cout << "data" << trameparsed.dataPayload << endl;
		cout << "data" << trameparsed.dataPayload << endl;

	/*
		cout << pointeur << "devrait etre une adresse non ?" << endl;
		pointeur = champ_suivant(pointeur);
		printf("adresse de p -> %p \n", pointeur);//&trameN[0];


		pointeur = champ_suivant(pointeur);
		printf("adresse de p -> %p \n", pointeur);//&trameN[0];

		printf("adresse de debut de trame -> %p", &trameN[0]);//&trameN[0];
	*/
}

