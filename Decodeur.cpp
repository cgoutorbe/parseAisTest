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
/*

 * size_t pos = 0;
std::string token;
while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    std::cout << token << std::endl;
    s.erase(0, pos + delimiter.length());
}*/



class Decodeur
{
	private:
		//definition des variables requises
		string trameStr;
	public:
		//definition des méthodes du décodeur
		
		NMEA parse_string(string s){
			//Fonction de découpe de la chaine de caractère reçue 
			//trame est la chaine à parser 
			//On parcourt la chaine et on créer un objet NMEA
			NMEA trame;
			string last;
			string token;
			string delimiter = ",";
			size_t pos =0;
			vector<char> data;
			int i = 0;
			int* adr =(int*)  &trame;

			s.erase(0,s.find(delimiter)+delimiter.length());
			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				cout << token << std::endl;
				//*(adr) =token;
				memcpy(adr,token.c_str(),token.length()/sizeof(char));
				//const char* cs = token.c_str(); //on récup la position mémoire de la string 		
				s.erase(0, pos + delimiter.length());
				adr+=sizeof(int);
			}
			return trame;
		}
		void Decode(){

		}

};
int main()
{
	string trameN = "!AIVDM,2,1,3,B,55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53,0*3E";
	const void* s = (const void*) trameN.c_str();
	for(int i = 0; i < 10; i+=4)
		cout << *((const int*)s+i) << endl;

	Decodeur decodeur;
	cout << decodeur.parse_string(trameN).nbFragment <<endl;
	return 0;
}



