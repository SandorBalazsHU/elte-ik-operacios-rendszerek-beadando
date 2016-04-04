#include <stdio.h>
#include <string.h>
#include "model/Lines.h"
#include "model/Line.h"
#include "model/Passenger.h"
#include "controller/FileIO.h"
#include "view/ConsoleIO.h"

int main(int argc, char** argv)
{
	clearScrean();
	printIntro();
	printMainMenu();
	
	//Lines* lines = readDatasFromTXTFile("uber.txt");
	
	char slected;
	while((slected = mainMenu()) != '3')
	{
		if(slected == '1')
		{
			clearScrean();
			printIntro();
		}
		if(slected == '2')
		{
			clearScrean();
			printIntro();
		}
		clearScrean();
		printIntro();
		printMainMenu();
	}
	
	//freeLines(lines);
	return 0;
}