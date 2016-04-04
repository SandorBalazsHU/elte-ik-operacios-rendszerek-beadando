//mallochoz szügséges
#include <stdlib.h>
#include <string.h>
#include "Passenger.h"

//új utas létrehozása
struct Passenger* newPassenger(Passenger* pas, char* inName, char* inPhoneNum, int inDate)
{
	strcpy(pas->name, inName);
	strcpy(pas->phoneNum, inPhoneNum);
	pas->date = inDate;
}