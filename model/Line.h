#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include "Passenger.h"

//A járatot modellező adatszerkezet
/*
+--------------------------------+
|              Line              |
|     +--------------------+     |
|     | char* destination  |     |
|     +--------------------+     |
|     +--------------------+     |
|     | char* startTime    |     |
|     +--------------------+     |
|     +--------------------+     |
|     | int size           |     |
|     +--------------------+     |
|     +--------------------+     |
|     | int _realSize      |     |
|     +--------------------+     |
|                                |
| +----------------------------+ |          +--------------------+
| | Passenger** PassengerArray |===========>| PassengerArray[]   |
| +----------------------------+ |          | +----------------+ |
|                                |          | |   Passenger*   | |
|                                |          | +----------------+ |
|                                |          | +----------------+ |
|                                |          | |   Passenger*   | |
|                                |          | +----------------+ |
|                                |          | +----------------+ |
|                                |          | |   Passenger*   | |
|                                |          | +----------------+ |
|                                |          |         ...        |
+--------------------------------+          +--------------------+
*/

typedef struct Line
{
	//Uticél
	char destination[100];
	//Indulás ideje. Formátum: YYYYMMDDhhmm
        char startTime[20];
	//Felvett utasok száma
	int size;
	//A tároló tömb valós mérete
	int _realSize;
	//Az utasokra mutató pointerek tömbje
	Passenger** passengerArray;
}Line;

//Az alapértelmezett tároló tömb mérete
static const int _lineDefaultArraySize = 5;

//Új üres járat létrehozásához
struct Line* newLine(char*, char*);

//Utas hozzáadását teszi lehetőve egy járathoz
/*	Ha az utaslistát reprezentáló tömb betelt, akkor dupla méretűt deklarálunk, átmásoljuk az adatokat és a régit töröljük a C++ Vector mintájára.*/
int addPassengerToLine(Line*, Passenger*);

//Utas törlése az utaslistáról
int deletePassengerFromLine(Line*, Passenger*);

//Adott nevű utas keresése
struct Passenger* getPassengerFromLineByName(Line*, char*);

//Adott ID-jú utas keresése
struct Passenger* getPassengerFromLineByID(Line*, int);

//A Line típus destruktora
/*	Kell destrukfor, mivel a passengerArray külön álló egységet képez a memóriában*/
void freeLine(Line*);

#endif