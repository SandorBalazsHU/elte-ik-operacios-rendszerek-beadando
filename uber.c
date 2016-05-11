#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
            Passenger* newPass = getPassengerFromConsol();
            char ids [256];
            getRowFromConsol("      \x1b[32m+\x1b[0m Kerem adja meg a valsztott ut sorszamat: ", ids);
            if(numbersOnly(ids))
            {
                int id = atoi(ids);
                if((id>0) && (id<lines->size+1))
                {
                    addPassengerToLine(getLineFromLinesById(lines,id-1), newPass);
                    writeLinesToTXTFile(lines, "uber.txt");
                    printf("\n      \x1b[32m+\x1b[0m Az adatok felvetele sikeres volt!");
                }
                else
                {
                    printf("\n      \x1b[31m+ Ilyen ut nem letezik!\x1b[0m \n");
                }
            }
            else
            {
                printf("\n      \x1b[31m+ Ilyen ut nem letezik!\x1b[0m \n");
            }
            
            printf("\n      \x1b[32m+\x1b[0m Uss entert a fomenube valo visszatereshez!");
            clearInputBuffer();
        }
        if(slected == '2')
        {
            clearScrean();
            printIntro();
            printLinesInTable(lines);
            printSubMenu();
            while((slected = subMenu()) != '6')
            {
                if(slected == '1')
                {
                    clearScrean();
                    printIntro();
                    Line* newLine = getLineFromConsol();
                    if(addLineToLines(lines, newLine) != -1)
                    {
                        writeLinesToTXTFile(lines, "uber.txt");
                        printf("\n      \x1b[32m+\x1b[0m Az adatok felvetele sikeres volt!");
                    }
                    else
                    {
                        printf("\n      \x1b[31m+ IEnnél a dátumnál van közelebbi!\x1b[0m \n");
                    }
                    printf("\n      \x1b[32m+\x1b[0m Uss entert a fomenube valo visszatereshez!");
                    clearInputBuffer();
                }
                if(slected == '2')
                {
                }
                if(slected == '3')
                {
                }
                if(slected == '4')
                {
                }
                if(slected == '5')
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