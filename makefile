main: NMEA.o check.o parsePoint.cpp
	g++ parsePoint.cpp NMEA.o check.o -o parsePoint 

NMEA.o: NMEA.h NMEA.cpp
	g++ -c NMEA.cpp -o NMEA.o
check.o: check.h check.cpp
	g++ -c check.cpp -o check.o
