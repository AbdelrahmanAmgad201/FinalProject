#ifndef UNDO_H
#define UNDO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dataStructure.h"



void undo(gameState * currentGame, gameState history[], int * count);

void redo(gameState * currentGame, gameState history[], int * count);



#endif

