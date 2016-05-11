#ifndef CONSOLEIO_H
#define CONSOLEIO_H

#include "../model/Passenger.h"
#include "../model/Lines.h"
#include "../model/Line.h"
#include "../model/Passenger.h"

//Kiírja a saját dátum reprezentációt a képernyőre
void dateOut(int);

//Megadja a képernyő jelenlegi szélességét
int getConsoleWindowWidth();

//Kiírja a köszöntő szöveget
void printIntro();

//A főmeü kirajzolása
void printMainMenu();

char mainMenu();


Passenger* getPassengerFromConsol();

void clearInputBuffer();

void getDate(char*);

void getRowFromConsol(char*, char*);

static int getLine (char*, char*, size_t);

int numbersOnly(const char*);

Line* getLineFromConsol();

//Az első almenü kirajzolása
void printSubMenu();

//A menük logikája
char subMenu();


//Képernyő töröl
void clearScrean();

void printLinesInTable(Lines*);



/*
void readFromConsole(char*, char, char*, int);
void printRecord(Gift*);


inline void printGiftPack(GiftPack*);
inline giftTypes getGiftTypeFromConsole();
inline void vaitFromToken(char token);
*/

#endif