#include "check.h"

int nmea_checksum(unsigned char* checksum, char *p){

        //fonction calculant le checksum d'une trame
/*      while(*p != 0 && *p !='*'){

                *checksum ^=*p;
                p++;

        }*/
        int i=0;
        *checksum = 0;
        while( (*p != 0) && (*p != '*') && !((*p == '!') || (*p == '$')) )
    {
        *checksum ^= *p;
        cout << *p <<endl;
        p++;
        i++;
    }
        return 0;
}

int check_nmea_checksum(char* read, char *p){

        //variable stockant la valeur calculée du checksum
        unsigned char calcSum[4] = "abc";
        unsigned char* pcalcSum = calcSum;

        cout <<"calcsum --->>" << calcSum << endl;
        nmea_checksum(pcalcSum,p);
        cout <<"calcsum --->>" << calcSum << endl;
        printf("check calc -> %s\n",calcSum);

/*
        //convert char from read checksum to hexa
        sum = ahextobin(p) << 4; //first convert to binary then move 4bits then convert
        sum += ahextobin(p+1);

        readSum =ahextobin(read) <<4;
        readSum +=ahextobin(read+1);

        if(readSum == sum){return 0;}
*/      return 1;
}
