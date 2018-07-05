main: NMEA.o parsePoint.cpp
	g++ parsePoint.cpp NMEA.o -o parsePoint 

NMEA.o: NMEA.h NMEA.cpp
	g++ -c NMEA.cpp -o NMEA.o

