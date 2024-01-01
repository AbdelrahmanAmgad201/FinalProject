#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include "dataStructure.h"
#include "colors.h"


void printData(gameState * currentGame);


char printMenuAndGetCommand();


void printBoard(cell ** cells, int size);


#endif

