#include <stdio.h>
#include <string.h>
//mallochoz szügséges
#include <stdlib.h>
#include "FileIO.h"
#include "../model/Lines.h"
#include "../model/Line.h"
#include "../model/Passenger.h"

/*/Tokenekre darabol egy szöveget
char** tokenizer(char* str, char* delimiter)
{
	char* tokens[_tokenBufferSize];
	char* token;
	int i = 0;
	while ((token = strsep(&string, ",")) != NULL)
	{
		strcpy(tokens[i], token);
		++i;
	}
}*/

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
	char* _lineBuffer = lineBuffer;
	int i = 0;
	Line* theNewLine;
	
	while (!feof(f))
	{
		fgets(lineBuffer,sizeof(lineBuffer),f);
		int j; for(j = 0; j < sizeof(lineBuffer); ++j) if(lineBuffer[j] == '\n') lineBuffer[j] = '\0';
		if((lineBuffer[0] != '-') && (lineBuffer[1] != '-'))
		{
			char* tokens[_tokenBufferSize];
			int j; for(j = 0; j < _tokenBufferSize; ++j) tokens[j] = "";
			char* token;
			int i = 0;
			while ((token = strsep(&_lineBuffer, ",")) != NULL)
			{
				strcpy(tokens[i], token);
				++i;
			}
			theNewLine = newLine();
			strcpy(theNewLine->destination,tokens[0]);
			theNewLine->startTime = atoi(tokens[1]);
			addLineToLines(returnLines, theNewLine);
		}
		else
		{
			char* tokens[_tokenBufferSize];
			int j; for(j = 0; j < _tokenBufferSize; ++j) tokens[j] = malloc(sizeof(char)*50);
			char* token;
			int i = 0;
			while ((token = strsep(&_lineBuffer, ",")) != NULL)
			{
				strcpy(tokens[i], token);
				++i;
			}
			Passenger* newPass = (struct Passenger*) malloc(sizeof (struct Passenger));
			//newPassenger(newPass, tokens[0], tokens[2], atoi(tokens[1]));
			addPassengerToLine(theNewLine,newPass);
		}
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
		fprintf(f, "%s,%d\n", lines->lineArray[i]->destination, lines->lineArray[i]->startTime);
		
		for(j = 0; j < lines->lineArray[i]->size; ++j)
		{
			fprintf(f, "--%s,%d,%s\n",lines->lineArray[i]->passengerArray[j]->name,lines->lineArray[i]->passengerArray[j]->date,lines->lineArray[j]->passengerArray[i]->phoneNum);
		}
	}
	fclose(f);
	return 0;
}