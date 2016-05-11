
#include <stdlib.h>
#include <string.h>
#include "Passenger.h"

//új utas létrehozása
struct Passenger* newPassenger(char* inName, char* inDate, char* inPhoneNum)
{
    Passenger* newPass = (struct Passenger*) malloc(sizeof (struct Passenger));
    strcpy(newPass->name, inName);
    strcpy(newPass->phoneNum, inPhoneNum);
    strcpy(newPass->date, inDate);
    return newPass;
}