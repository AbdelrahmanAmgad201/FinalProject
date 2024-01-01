#ifndef DFS_H
#define DFS_H
#include <stdio.h>
#include "dataStructure.h"

void dfs(gameState*currentGame , int i , int j , int **visited , int cameFrom , int *stop , int directions[4][2]);
int chainChecker(gameState*currentGame , int i , int j , char k);


#endif

