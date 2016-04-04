#ifndef CONSOLEIO_H
#define CONSOLEIO_H

/*#include "../model/Gift.h"
#include "../model/GiftPack.h"*/

//Kiírja a saját dátum reprezentációt a képernyőre
void dateOut(int);

//Megadja a képernyő jelenlegi szélességét
int getConsoleWindowWidth();

//Kiírja a köszöntő szöveget
inline void printIntro();

//A főmeü kirajzolása
inline void printMainMenu();

//Az első almenü kirajzolása
inline void printSubMenu();

//A menük logika
char subMenu();
char mainMenu();

//Képernyő töröl
inline void clearScrean();

/*
void readFromConsole(char*, char, char*, int);
void printRecord(Gift*);


inline void printGiftPack(GiftPack*);
inline giftTypes getGiftTypeFromConsole();
inline void vaitFromToken(char token);
*/

#endif