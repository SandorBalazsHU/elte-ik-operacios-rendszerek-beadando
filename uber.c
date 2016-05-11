#include <stdio.h>
#include <string.h>
#include "./model/Lines.h"
#include "./model/Line.h"
#include "./model/Passenger.h"
#include "./controller/FileIO.h"
#include "./view/ConsoleIO.h"

int main(int argc, char** argv)
{
    clearScrean();
    printIntro();

    Lines* lines = readDatasFromTXTFile("uber.txt");
    if(lines == NULL)
    {
        printf("HIBA!\n");
        return(1);
    }

    printLinesInTable(lines);

    printMainMenu();

    char slected;
    while((slected = mainMenu()) != '3')
    {
        if(slected == '1')
        {
            clearScrean();
            printIntro();
            getPassengerFromConsol();
            printf("\n      \x1b[32m+\x1b[0m Az adatok felvetele sikeres volt!");
            printf("\n      \x1b[32m+\x1b[0m Uss entert a fomenube valo visszatereshez!");
            clearInputBuffer();
        }
        if(slected == '2')
        {
            clearScrean();
            printIntro();
            printSubMenu();
            while((slected = subMenu()) != '3')
            {
                if(slected == '1')
                {
                }
                if(slected == '2')
                {
                }
            }
        }
        clearScrean();
        printIntro();
        printLinesInTable(lines);
        printMainMenu();
    }

    //freeLines(lines);
    return 0;
}