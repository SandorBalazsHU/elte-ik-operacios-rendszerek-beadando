#ifndef LINES_H
#define LINES_H

#include <stdio.h>
#include "Line.h"

//A járatlistát modellező adatszerkezet
/*
+------------------------+
|          Lines         |
| +--------------------+ |
| |    int size        | |
| +--------------------+ |
| +--------------------+ |
| |    int _realSize   | |
| +--------------------+ |
|                        |
| +--------------------+ |          +--------------------+
| |  Line** lineArray  |===========>|     lineArray[]    |
| +--------------------+ |          | +----------------+ |
|                        |          | |      Line*     | |
|                        |          | +----------------+ |
|                        |          | +----------------+ |
|                        |          | |      Line*     | |
|                        |          | +----------------+ |
|                        |          | +----------------+ |
|                        |          | |      Line*     | |
|                        |          | +----------------+ |
|                        |          |         ...        |
+------------------------+          +--------------------+
*/

typedef struct Lines
{
	//Felvett uticélok száma
	int size;
	//A tároló tömb valós mérete
	int _realSize;
	//Járatokra mutató pointerek tömbje
	Line** lineArray;
}Lines;

//Az alapértelmezett tároló tömb mérete
static const int defaultArraySize = 5;

//Új üres járatlista létrehozásához
struct Lines* newLines();

//Járat hozzáadását teszi lehetőve a járatlistához
/*	Ha a listát reprezentáló tömb betelt, akkor dupla méretűt deklarálunk, átmásoljuk az adatokat és a régit töröljük a C++ Vector mintájára.*/
int addLineToLines(Lines*, Line*);

//Járat törlése a járatlistából
int deleteLineFromLines(Lines*, Line*);

//Célállomás szerinti keresés
struct Line* getLineFromLines(Lines*, char*);

//A Lines típus destruktora
/*	Kell destrukfor, mivel a lineArray külön álló egységet képez a memóriában*/
void freeLines(Lines*);

#endif