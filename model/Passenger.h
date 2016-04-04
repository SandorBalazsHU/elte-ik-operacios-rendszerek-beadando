#ifndef PASSENGER_H
#define PASSENGER_H

//time_t-hez szügséges
#include <time.h>

//Egy utas modellezésére szolgáló szerkezet
/*
+------------------------+
|        Passenger       |
|                        |
| +--------------------+ |
| |       name[]       | |
| | +----------------+ | |
| | |      Char      | | |
| | +----------------+ | |
| | +----------------+ | |
| | |      Char      | | |
| | +----------------+ | |
| |         ...        | |
| +--------------------+ |
|                        |
| +--------------------+ |
| |    int phoneNum    | |
| +--------------------+ |
|                        |
| +--------------------+ |
| |      int date      | |
| +--------------------+ |
|                        |
+------------------------+
*/
typedef struct Passenger
{
	//név
	char name[30];
	//telefonszám
	char phoneNum[12];
	//Jelentkezés ideje. Formátum: YYYYMMDDhhmm
	int date;
} Passenger;

//új utas létrehozása
struct Passenger* newPassenger(Passenger*, char*, char*, int);

/*/Heapra másol stringeket.?????????????????????????????????????????????????????????
char* charCopyByValueToHeap(char*);*/
#endif