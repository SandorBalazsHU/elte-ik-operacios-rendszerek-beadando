//mallochoz szügséges
#include <stdlib.h>
#include <string.h>
#include "Line.h"
#include "Passenger.h"

//Új üres járat létrehozásához
struct Line* newLine(char* destination, char* startTime)
{
	struct Line* _this = malloc(sizeof(struct Line));
        strcpy(_this -> destination, destination);
        strcpy(_this -> startTime, startTime);
	_this -> size = 0;
	_this -> _realSize = _lineDefaultArraySize;
	Passenger**  mallocPassengerArray = malloc(_this -> _realSize * sizeof(Passenger*));
	_this -> passengerArray = mallocPassengerArray;
	return _this;
}

//Utas hozzáadását teszi lehetőve egy járathoz
/*	Ha az utaslistát reprezentáló tömb betelt, akkor dupla méretűt deklarálunk, átmásoljuk az adatokat és a régit töröljük a C++ Vector mintájára.*/
int addPassengerToLine(Line* line, Passenger* passenger)
{
	int i;
	
	if(line->_realSize > line->size)
	{
		line->passengerArray[line->size] = passenger;
		line->size++;
	}
	else
	{
		line -> _realSize *= 2;
		Passenger**  mallocpassengerArray = malloc(line -> _realSize * sizeof(Passenger*));
		for(i = 0; i < line->size; ++i)
		{
			mallocpassengerArray[i] = line->passengerArray[i];
		}
		Passenger** arr = line -> passengerArray;
		free(arr);
		line -> passengerArray = mallocpassengerArray;
		line->passengerArray[line->size] = passenger;
		line->size++;
	}
}

//Utas törlése az utaslistáról
int deletePassengerFromLine(Line* line, Passenger* passenger)
{
	int i, l = 0;
	Passenger**  mallocpassengerArray = malloc(line -> _realSize * sizeof(Passenger*));
	for(i = 0; i < line->size; ++i)
	{
		if(line->passengerArray[i] != passenger)
		{
			mallocpassengerArray[l] = line->passengerArray[i];
		}
		else
		{
			l = i-1;
			free(line->passengerArray[i]);
		}
		++l;
	}
	Passenger** arr = line -> passengerArray;
	free(arr);
	line -> passengerArray = mallocpassengerArray;
	line->size--;
	return 0;
}

//Adott nevű utas keresése
struct Passenger* getPassengerFromLine(Line* line, char* name)
{
	int i;
	for(i = 0; i < line->size; ++i)
	{
		if((strcmp(line->passengerArray[i]->name, name) == 0 )) return(line->passengerArray[i]);
	}
	return NULL;
}

//A Line típus destruktora
/*	Kell destrukfor, mivel a passengerArray külön álló egységet képez a memóriában*/
void freeLine(Line* line)
{
	int i;
	for(i = 0; i < line->size; ++i)
	{
		free(line->passengerArray[i]);
	}
	free(line->passengerArray);
	free(line);
}