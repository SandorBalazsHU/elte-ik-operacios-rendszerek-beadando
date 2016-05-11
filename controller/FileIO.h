#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include "../model/Lines.h"

static const int _tokenBufferSize = 150;
static const int _lineBufferSize = 200;

//Képes beolvasni az adatokat egy TXT fájlból. Hiba esetén NULL pointerrel tér vissza.
struct Lines* readDatasFromTXTFile(char*);

//Képes TXT fájlba írni egy Lines struct-ot olvasható formában. Hibajelekkel tér vissza
int writeLinesToTXTFile(Lines*, char*);

char* trim (char*);

#endif
