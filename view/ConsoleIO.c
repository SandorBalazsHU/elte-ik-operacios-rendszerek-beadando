//time_t-hez szügséges
#include <time.h>
//strcpyhoz szügséges
#include <string.h>
#include <stdio.h>
#include "ConsoleIO.h"
#include <sys/ioctl.h>
#include <unistd.h>
/*#include "../model/Gift.h"
#include "../model/GiftPack.h"*/

//Kiírja a saját dátum reprezentációt a képernyőre
void dateOut(int date)
{
	/*struct tm tm = *localtime(&date);
	printf("%d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);*/
}

//Megadja a képernyő jelenlegi szélességét
int getConsoleWindowWidth()
{
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
}

//Kiírja a köszöntő szöveget
inline void printIntro()
{
	printf("\n");
	int i, position = (int) (getConsoleWindowWidth()/2)-21;
	char spacer[position];
	char line[position]; 
	for(i = 0; i < position; ++i)
	{
		spacer[i] = ' ';
		line[i] = '-'; 
	}
	printf("%s\x1b[32m +-----------------------------------+\x1b[0m\n",spacer);
	printf("+%s\x1b[32m|  Best of UBER telekocsi rendszer  |\x1b[0m%s+\n",line,line);
	printf("%s\x1b[32m +-----------------------------------+\x1b[0m\n",spacer);
}

//A főmeü kirajzolása
inline void printMainMenu()
{
	printf("          +-------------------+ \n");
	printf("      \x1b[32m1.)\x1b[0m | Utazni szeretnék! | \n");
	printf("          +-------------------+ \n");
	printf("          +-------------------+ \n");
	printf("      \x1b[32m2.)\x1b[0m | Adminisztráció    | \n");
	printf("          +-------------------+ \n");
	printf("          +-------------------+ \n");
	printf("      \x1b[32m3.)\x1b[0m | Kilépés           | \n");
	printf("          +-------------------+ \n");
	printf("      \x1b[32m+\x1b[0m Valassz funkciot: ");
}

//Az első almenü kirajzolása
inline void printSubMenu()
{
	printf("          +-----------------+ \n");
	printf("      \x1b[32m1.)\x1b[0m | Utak kezelése   | \n");
	printf("          +-----------------+ \n");
	printf("          +-----------------+ \n");
	printf("      \x1b[32m2.)\x1b[0m | Utasok kezelése | \n");
	printf("          +-----------------+ \n");
	printf("          +-----------------+ \n");
	printf("      \x1b[32m3.)\x1b[0m | Kilépés         | \n");
	printf("          +-----------------+ \n");
	printf("      \x1b[32m+\x1b[0m Valassz funkciot: ");
}

//A menük logika
char mainMenu()
{
	char selectedMenuPoint = ' ';
	while( !((selectedMenuPoint == '1') || (selectedMenuPoint == '2') || (selectedMenuPoint == '3')) )
	{
		if ((selectedMenuPoint != ' ') && ( selectedMenuPoint != '\n')) printf("      \x1b[32m+\x1b[0m Hibas ertek! Add meg újra: ");
		selectedMenuPoint = getchar();
	}
	return selectedMenuPoint;
}

//A menük logika
char subMenu()
{
	char selectedMenuPoint = ' ';
	while( !((selectedMenuPoint == '1') || (selectedMenuPoint == '2') || (selectedMenuPoint == '3') || (selectedMenuPoint == '4')) )
	{
		if ((selectedMenuPoint != ' ') && ( selectedMenuPoint != '\n')) printf("      \x1b[32m+\x1b[0m Hibas ertek! Add meg újra: ");
		selectedMenuPoint = getchar();
	}
	return selectedMenuPoint;
}


//Képernyő töröl
inline void clearScrean()
{
	printf("\033[H\033[J");
}





/*
void readFromConsole(char* text, char ender, char* label, int l)
{
	printf("\x1b[32m + %s  \x1b[0m\n",label);
	if(l == 1) printf(" \x1b[32m+\x1b[0m Gépeld be az üzeneted (%c -ig):\n",ender);
	size_t i = 0;
	char c;
	while ((c = getchar()) != ender && c != EOF)
	{
		if(c != '\n')
		{
			text[i] = c;
			++i;
		}
	}
	text[i] = '\0';
}
	
void printRecord(Gift* gift)
{
	printf("\n + ID: %d | Dátum: ",(int) gift->id);
	dateOut(gift->date);
	printf(" | Név: %s | Város: %s | Cím: %s  | Ajándék: " ,gift->name, gift->city, gift->address);
	switch(gift->giftType)
	{
		case BABY         : printf("Baba"); break;
		case BALL         : printf("Labda"); break;
		case CAR          : printf("Autó"); break;
		case COLORINGBOOK : printf("Színező"); break;
		case PUZZLE       : printf("Puzzle"); break;
		case BOOK         : printf("Könyv"); break;
	}
	printf("\n   Üzenet: %s\n", gift->text);
}

inline void printGiftPack(GiftPack* gifts)
{
	size_t i;
	for(i = 0; i<gifts->size; ++i)
	{
		printRecord(gifts->giftArray[i]);
	}
	printf("\n Összes levél: %d\n",(int) gifts->size);
}

inline giftTypes getGiftTypeFromConsole()
{
	printf("\n baba = 1, Labda = 2, autó = 3, színező = 4, puzzle = 5, könyv = 6\nMiyen ajándékot szeretnél(*): ");
	char giftTypeChar;
	giftTypes giftType = BABY;
	while ((giftTypeChar = getchar()) != '*')
	{
		switch(giftTypeChar)
		{
			case '1': giftType = BABY; break;
			case '2': giftType = BALL; break;
			case '3': giftType = CAR; break;
			case '4': giftType = COLORINGBOOK; break;
			case '5': giftType = PUZZLE; break;
			case '6': giftType = BOOK; break;
		}
	}
	return(giftType);
}
inline void vaitFromToken(char token)
{
	char c;
	while ((c = getchar()) != token && c != EOF);
}
*/