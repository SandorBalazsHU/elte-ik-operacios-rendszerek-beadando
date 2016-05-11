#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FileIO.h"
#include "../model/Lines.h"
#include "../model/Line.h"
#include "../model/Passenger.h"

//Képes beolvasni az adatokat egy TXT fájlból. Hiba esetén NULL pointerrel tér vissza.
struct Lines* readDatasFromTXTFile(char* fname)
{
    Lines* returnLines = newLines();
    FILE* f = fopen(fname,"r");
    if (f==NULL)
    {
        perror("File opening error!\n");
        return NULL;
    }

    char lineBuffer[_lineBufferSize];
    Line* theNewLine;
    while (!feof(f))
    {
        char* r = fgets(lineBuffer,sizeof(lineBuffer),f);
        trim(lineBuffer);
        char* tokens[_tokenBufferSize];
        int j; for(j = 0; j < _tokenBufferSize-1; ++j) tokens[j] = malloc(sizeof(char)*50);
        int i = 0;
        char* token = strtok(lineBuffer, ",");
        while (token) {
            strcpy(tokens[i], token);
            token = strtok(NULL, ",");
            ++i;
        }
        if((lineBuffer[0] != '-') && (lineBuffer[1] != '-'))
        {
            theNewLine = newLine(tokens[0], tokens[1]);
            addLineToLines(returnLines, theNewLine);
        }
        else
        {
            Passenger* newPass = newPassenger(tokens[1], tokens[3], tokens[2]);
            addPassengerToLine(theNewLine,newPass);
        }
        for(j = 0; j < _tokenBufferSize-1; ++j) free(tokens[j]);
    } 
    fclose(f);
    return returnLines;
}

//Képes TXT fájlba írni egy Lines struct-ot olvasható formában. Hibajelekkel tér vissza
int writeLinesToTXTFile(Lines* lines, char* fname)
{
    FILE* f = fopen(fname, "w");
    if (f == NULL)
    {
        perror("File opening error!\n");
        return 1;
    }
    int i, j;
    for(i = 0; i < lines->size; ++i)
    {
        fprintf(f, "%s,%s\n", lines->lineArray[i]->destination, lines->lineArray[i]->startTime);
        for(j = 0; j < lines->lineArray[i]->size; ++j)
        {
            fprintf(f, "--%s,%s,%s\n",lines->lineArray[i]->passengerArray[j]->name,lines->lineArray[i]->passengerArray[j]->date,lines->lineArray[j]->passengerArray[i]->phoneNum);
        }
    }
    fclose(f);
    return 0;
}

char* trim(char* s)
{
    int i = strlen(s)-1;
    if ((i > 0) && (s[i] == '\n')) s[i] = '\0';
    return s;
}