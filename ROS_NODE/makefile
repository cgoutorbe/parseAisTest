main: NMEA.o check.o parsePoint.cpp
	g++ parsePoint.cpp NMEA.o check.o -o parsePoint 
parsePoint: parsePoint.cpp parsePoint.h NMEA.o check.o
	g++ -c parsePoint.cpp NMEA.o check.o -o parsePoint.o

NMEA.o: NMEA.h NMEA.cpp
	g++ -c NMEA.cpp -o NMEA.o
check.o: check.h check.cpp
	g++ -c check.cpp -o check.o
thread: thread.cpp
	g++ thread.cpp -o thread
recoThread: recoThread.cpp recoThread.h
	g++ -c recoThread.cpp -o recoThread.o -std=c++0x
