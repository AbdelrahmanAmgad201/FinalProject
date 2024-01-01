#ifndef FUNTIONS_H
#define FUNTIONS_H
#include<ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dataStructure.h"
#include "colors.h"
#include "dfs.h"
#include "undoRedo.h"
#include "display.h"
#include "saveLoad.h"
#include "leaderboard.h"

void updateHistory(gameState * game, gameState history[], int counter);

int computerTurn(gameState * currentGame, int target);

void placeLine(gameState * currentGame, int i, int j, char k);


void scanNames(gameState * game);

void createArr(gameState * game, int size);

void initializeGameState(gameState * game);

int checkCellFull(gameState * currentGame, int i, int j);

int CheckWinner(gameState * currentGame);

void checkValidity(gameState * currentGame, int * i, int * j, char * k);

void currentGameTurn(gameState * currentGame, gameState history[], int count);

#endif

