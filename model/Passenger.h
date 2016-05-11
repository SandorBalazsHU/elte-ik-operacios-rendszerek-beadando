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
| |     char name[]    | |
| +--------------------+ |
|                        |
| +--------------------+ |
| |   char phoneNum[]  | |
| +--------------------+ |
|                        |
| +--------------------+ |
| |    char date[]     | |
| +--------------------+ |
|                        |
+------------------------+
*/
typedef struct Passenger
{
	//név
	char name[30];
	//telefonszám
	char phoneNum[30];
	//Jelentkezés ideje. Formátum: YYYYMMDDhhmm
	char date[20];
} Passenger;

//új utas létrehozása
struct Passenger* newPassenger(char*, char*, char*);

/*/Heapra másol stringeket.?????????????????????????????????????????????????????????
char* charCopyByValueToHeap(char*);*/
#endif