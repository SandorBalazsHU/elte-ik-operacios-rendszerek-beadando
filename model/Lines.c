//mallochoz szügséges
#include <stdlib.h>
#include <string.h>
#include "Lines.h"
#include "Line.h"

//Új üres lista
struct Lines* newLines()
{
	struct Lines* _this = malloc(sizeof(struct Lines));
	_this -> size = 0;
	_this -> _realSize = defaultArraySize;
	Line**  mallocLineArray = malloc(_this -> _realSize * sizeof(Line*));
	_this -> lineArray = mallocLineArray;
	return _this;
}


//Járat hozzáadását teszi lehetőve a járatlistához
/*	Ha a listát reprezentáló tömb betelt, akkor dupla méretűt deklarálunk, átmásoljuk az adatokat és a régit töröljük.
(C++ std::Vector szerű működés)*/
//Feladat szerinti műkösés: - Csak a jelenleg a listában lévőnél korábbi indulási idejű járat veheő fel.
int addLineToLines(Lines* lines, Line* line)
{
	int i;
	int insert = -1;
	/*for(i = 0; i < lines->size; ++i)
	{
		if(strcmp(lines->lineArray[i]->destination,line->destination) == 0 )
		{
			if(lines->lineArray[i]->startTime < line->startTime)
			{
				return 1;
			}
			else
			{
				insert = i;
				break;
			}
		}
	}*/
	
	if(lines->_realSize > lines->size)
	{
		if (insert == -1)
		{
			lines->lineArray[lines->size] = line;
		}
		else
		{
			freeLine(lines->lineArray[insert]);
			lines->lineArray[insert] = line;
		}
		lines->size++;
	}
	else
	{
		lines -> _realSize *= 2;
		Line**  mallocLineArray = malloc(lines -> _realSize * sizeof(Line*));
		for(i = 0; i < lines->size; ++i)
		{
			mallocLineArray[i] = lines->lineArray[i];
		}
		Line** arr = lines -> lineArray;
		free(arr);
		lines -> lineArray = mallocLineArray;
		
		if (insert == -1)
		{
			lines->lineArray[lines->size] = line;
		}
		else
		{
			freeLine(lines->lineArray[insert]);
			lines->lineArray[insert] = line;
		}
		lines->size++;
	}
	return 0;
}


//Járat törlése a járatlistából
int deleteLineFromLines(Lines* lines, Line* line)
{
	int i, l = 0;
	Line**  mallocLineArray = malloc(lines -> _realSize * sizeof(Line*));
	for(i = 0; i < lines->size; ++i)
	{
		if(lines->lineArray[i] != line)
		{
			mallocLineArray[l] = lines->lineArray[i];
		}
		else
		{
			l = i-1;
			freeLine(lines->lineArray[i]);
		}
		++l;
	}
	Line** arr = lines -> lineArray;
	free(arr);
	lines -> lineArray = mallocLineArray;
	lines->size--;
	return 0;
}

//Célállomás szerinti keresés
struct Line* getLineFromLinesByDestination(Lines* lines, char* dest)
{
	int i;
	for(i = 0; i < lines->size; ++i)
	{
		if((strcmp(lines->lineArray[i]->destination, dest) == 0 )) return(lines->lineArray[i]);
	}
	return NULL;
}

struct Line* getLineFromLinesById(Lines* lines, int id)
{
    if(id<lines->size)
    {
        return lines->lineArray[id];
    }
    else
    {
        return NULL;
    }
}


//A Lines típus destruktora
/*	Kell destrukfor, mivel a lineArray külön álló egységet képez a memóriában. Törli a tömb által mutatott elemeket is.*/
void freeLines(Lines* lines)
{
	int i;
	for(i = 0; i < lines->size; ++i)
	{
		freeLine(lines->lineArray[i]);
	}
	free(lines->lineArray);
	free(lines);
}