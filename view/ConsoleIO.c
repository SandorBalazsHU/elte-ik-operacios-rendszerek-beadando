#include <time.h>
#include <string.h>
#include <stdio.h>
#include "ConsoleIO.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "../model/Lines.h"
#include "../model/Line.h"
#include "../model/Passenger.h"

#define GETLINE_OK       0
#define GETLINE_NO_INPUT 1
#define GETLINE_TOO_LONG 2

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
void printIntro()
{
	printf("\n");
	int i, position = (int) (getConsoleWindowWidth()/2)-21;
	char spacer[position+1];
	char line[position+1];
        spacer[position+1] = '\0';
	line[position+1] = '\0'; 
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
void printMainMenu()
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

//Képernyő töröl
void clearScrean()
{
    //printf("\033[H\033[J");
    int r = system("clear");
}

void printLinesInTable(Lines* lines)
{
    printf("\n");
    int i, position = (int) getConsoleWindowWidth();
    
    char bigLine[(position/2)-21+1];
    char spacer[(position/2)-21+1];
    bigLine[(position/2)-21+1] = '\0';
    spacer[(position/2)-21+1] = '\0';
    for(i = 0; i < (position/2)-21; ++i)
    {
        bigLine[i] = '-';
        spacer[i] = ' ';
    }

    printf("+%s\x1b[32m+-----------------------------------+\x1b[0m%s+\n",bigLine,bigLine);
    printf("|%s\x1b[32m|      Jelenleg induló járataink    |\x1b[0m%s|\n",spacer,spacer);
    printf("+%s\x1b[32m+-----------------------------------+\x1b[0m%s+\n",bigLine,bigLine);
    
    char spacer2[position-5+1];
    spacer2[position-5+1] = '\0';
    for(i = 0; i < (position-5); ++i)
    {
        spacer2[i] = ' ';
    }
    printf("|%s|\n",spacer2);
    
    char bigLine2[((position-7)/3)+1];
    bigLine2[((position-7)/3)+1] = '\0';
    for(i = 0; i < (position-7)/3; ++i)
    {
        bigLine2[i] = '-';
    }
    printf("+%s+%s+%s+\n",bigLine2,bigLine2,bigLine2);
    
   for(i = 0; i < lines->size; ++i)
    {
        Line* line = getLineFromLinesById(lines, i);
        if(strcmp(line->destination,"00Trash"))
        {
            printf("| %d, %s, %s \n", i+1, line->destination, line->startTime);
            printf("+%s+%s+%s+\n",bigLine2,bigLine2,bigLine2);
        }
    }
}

Passenger* getPassengerFromConsol()
{
    printf("      \x1b[32m+\x1b[0m Kerem toltse ki az alabbi urlapot az utazasra valo jelentkezeshez:\n");
    clearInputBuffer();
    char nev [256];
    getRowFromConsol("      \x1b[32m+\x1b[0m Kerem adja meg a teljes nevet: ", nev);
    char tel [256];
    getRowFromConsol("      \x1b[32m+\x1b[0m Kerem adja meg a telefonszamat: ",tel);
    char date [256];
    getDate(date);
    printf("      \x1b[32m+\x1b[0m A datum: %s \n",date);
    
    return newPassenger(nev, tel, date);
}


Line* getLineFromConsol()
{
    printf("      \x1b[32m+\x1b[0m Kerem toltse ki az alabbi urlapot uj jarat letrehozasahoz:\n");
    clearInputBuffer();
    char dest [256];
    getRowFromConsol("      \x1b[32m+\x1b[0m Kerem adja meg az uticélt: ", dest);
    char date [256];
    getRowFromConsol("      \x1b[32m+\x1b[0m Kerem adja meg az indulás idejét (yyyy-MM-dd-hh:mm): ",date);
    
    return newLine(dest, date);
}

void getRowFromConsol(char* text, char* str)
{

    char buff[256];

    int rc = getLine (text , buff, sizeof(buff));
    
    if (rc == GETLINE_NO_INPUT) {
        printf ("\n Nem adtál meg bemenetet! \n");
        exit(1);
    }

    if (rc == GETLINE_TOO_LONG) {
        printf ("Tul hosszu bemenet! \n");
        exit(1);
    }
    strcpy(str, buff);
}

void clearInputBuffer()
{
    while(getchar() != '\n');
}


static int getLine (char *prmpt, char *buff, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }

    if (fgets (buff, sz, stdin) == NULL)
        return GETLINE_NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? GETLINE_TOO_LONG : GETLINE_OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return GETLINE_OK;
}

void getDate(char* date){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char str[15];
    sprintf(str, "%d", tm.tm_year + 1900);
    strcpy(date, str);
    strcat(date, "-");
    
    memset(str,0,strlen(str));
    sprintf(str, "%d", tm.tm_mon + 1);
    strcat(date, str);
    strcat(date, "-");
    
    memset(str,0,strlen(str));
    sprintf(str, "%d", tm.tm_mday);
    strcat(date, str);
    strcat(date, "-");
    
    memset(str,0,strlen(str));
    sprintf(str, "%d", tm.tm_hour);
    strcat(date, str);
    strcat(date, ":");
    
    memset(str,0,strlen(str));
    sprintf(str, "%d", tm.tm_min);
    strcat(date, str);
}



//Az első almenü kirajzolása
void printSubMenu()
{
	printf("          +--------------------+ \n");
	printf("      \x1b[32m1.)\x1b[0m | Járat hozzáadása   | \n");
	printf("          +--------------------+ \n");
	printf("          +--------------------+ \n");
	printf("      \x1b[32m2.)\x1b[0m | járat törlése      | \n");
	printf("          +--------------------+ \n");
	printf("          +--------------------+ \n");
	printf("      \x1b[32m3.)\x1b[0m | Járat információk  | \n");
	printf("          +--------------------+ \n");
        printf("          +--------------------+ \n");
	printf("      \x1b[32m4.)\x1b[0m | Utas törlése       | \n");
	printf("          +--------------------+ \n");
	printf("          +--------------------+ \n");
	printf("      \x1b[32m5.)\x1b[0m | Utas módosítása    | \n");
	printf("          +--------------------+ \n");
	printf("          +--------------------+ \n");
	printf("      \x1b[32m6.)\x1b[0m | Vissza             | \n");
	printf("          +--------------------+ \n");
	printf("      \x1b[32m+\x1b[0m Valassz funkciot: ");
}

//A menük logika
char subMenu()
{
	char selectedMenuPoint = ' ';
	while( !((selectedMenuPoint == '1') || (selectedMenuPoint == '2') || (selectedMenuPoint == '3') || (selectedMenuPoint == '4') || (selectedMenuPoint == '5') || (selectedMenuPoint == '6')) )
	{
		if ((selectedMenuPoint != ' ') && ( selectedMenuPoint != '\n')) printf("      \x1b[32m+\x1b[0m Hibas ertek! Add meg újra: ");
		selectedMenuPoint = getchar();
	}
	return selectedMenuPoint;
}

int numbersOnly(const char* s)
{
    while (*s) {
        if (isdigit(*s++) == 0) return 0;
    }

    return 1;
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
	text[i] = '\0';*
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