#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dataStructure.h"
#include "colors.h"


char printMenuAndGetCommand() {
    char command;
    printf("   DOTS AND BOXES\n\n 1)2X2\n 2)5x5\n 3)leaderboard\n 4)End Game\n");
    scanf(" %c", &command);
    return command;
}

void createArr(gameState *game, int size) {
    game->cells = (cell **)malloc(size * sizeof(cell *));
    for (int i = 0; i < size; i++) {
        // Allocate and initialize memory for each row using calloc
        game->cells[i] = (cell *)calloc(size, sizeof(cell));
    }
}

void initializeGameState(gameState *game) {
    game->score1 = 0;
    game->score2 = 0;
    game->time = 0;
    game->turn = 1;
    game->cellsFilled = 0;
}

void printBoard(cell **cells, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("+");
            if (cells[i][j].up == 1) {
                printf( RED "--" RESET );
            } else if (cells[i][j].up == 2) {
                printf( BLUE "--" RESET );
            } else {
                printf("  ");
            }
        }
        printf("+\n");

        for (int j = 0; j < size; j++) {
            if (cells[i][j].left == 1) {
                printf(RED "|  " RESET);
            } else if (cells[i][j].left == 2) {
                printf(BLUE "|  " RESET);
            } else {
                printf("   ");
            }

            if (cells[i][j].right == 1 && j == size - 1) {
                printf(RED "|" RESET);
            } else if (cells[i][j].right == 2 && j == size - 1) {
                printf(BLUE "|" RESET);
            } 
        }

        printf("\n");
        if (i == size - 1) {
            for (int j = 0; j < size; j++) {
                printf("+");
                if (cells[i][j].bottom == 1) {
                    printf(RED "--" RESET);
                } else if (cells[i][j].bottom == 2) {
                    printf(BLUE "--" RESET);
                }
                else{
                    printf("  ");
                }
            }
            printf("+");
        }
    }
}

int checkCellFull(gameState *currentGame, int i, int j) {
    if (currentGame->cells[i][j].fillCount == 4) {
        (currentGame->turn == 1) ? (currentGame->score1++) : (currentGame->score2++);
        currentGame->cellsFilled++;
        return 1;
    }

    return 0;
}
void CheckWinner(gameState *currentGame , int size) {
    if(currentGame->cellsFilled == size*size)
    {
        if(currentGame->score1 > currentGame->score2)
        {
            printf(RED "%s "RESET"is the Winner !!",currentGame->player1Name);
            exit(0);
            
        }
        else if(currentGame->score1 < currentGame->score2){
            printf(BLUE "%s "RESET"is the Winner !!",currentGame->player2Name);
            exit(0);

        }
        else{
            printf(RED"DR"BLUE"AW"RESET" :(");
            exit(0);
        }

    }
   
}

void currentGameTurn(gameState *currentGame, char *move, int size) {
    int i = (move[0] - '0') - 1;
    int j = (move[1] - '0') - 1;
    char k = move[2];
    if (k == 'u') {
        currentGame->cells[i][j].up = currentGame->turn;
        if (i != 0) {
            currentGame->cells[i - 1][j].bottom = currentGame->turn;
            currentGame->cells[i - 1][j].fillCount++;
        }
    } else if (k == 'b') {
        currentGame->cells[i][j].bottom = currentGame->turn;
        if (i != size - 1) {
            currentGame->cells[i + 1][j].up = currentGame->turn;
            currentGame->cells[i + 1][j].fillCount++;
        }
    } else if (k == 'r') {
        currentGame->cells[i][j].right = currentGame->turn;
        if (j != size - 1) {
            currentGame->cells[i][j + 1].left = currentGame->turn;
            currentGame->cells[i][j + 1].fillCount++;
        }
    } else if (k == 'l') {
        currentGame->cells[i][j].left = currentGame->turn;
        if (j != 0) {  // Fix: Check if j is not at the beginning of the row
            currentGame->cells[i][j - 1].right = currentGame->turn;
            currentGame->cells[i][j - 1].fillCount++;
        }
    }
    currentGame->cells[i][j].fillCount++;
    if (!checkCellFull(currentGame, i, j)) {
        currentGame->turn = (currentGame->turn == 1) ? 2 : 1;
    }
}

int main() {
    char order = printMenuAndGetCommand();
    if (order == '1') {
        int size = 2;
        char move[4];
        gameState *game = (gameState *)malloc(sizeof(gameState));
        createArr(game, size);
        printf("player 1 name: ");
        scanf("%s",game->player1Name);
        printf("player 2 name: ");
        scanf("%s",game->player2Name);
        initializeGameState(game);

        while (1) {
            CheckWinner(game , size);
            printf("%s:%d %s:%d\n", game->player1Name , game->score1 ,game->player2Name ,game->score2);
            printBoard(game->cells, size);
            (game->turn == 1) ? printf("\n%s: ", game->player1Name) : printf("\n%s: ", game->player2Name);
            scanf("%s", move);
            currentGameTurn(game, move, size);
            system("cls");
            
        }
    } else if (order == '2') {
        int size = 5;
        char move[4];
        gameState *game = (gameState *)malloc(sizeof(gameState));
        createArr(game, size);
        printf("player 1 name: ");
        scanf("%s",game->player1Name);
        printf("player 2 name: ");
        scanf("%s",game->player2Name);
        initializeGameState(game);

        while (1) {
            CheckWinner(game , size);
            printf("%s:%d %s:%d\n", game->player1Name , game->score1 ,game->player2Name ,game->score2);
            printBoard(game->cells, size);
            (game->turn == 1) ? printf("\n%s: ", game->player1Name) : printf("\n%s: ", game->player2Name);
            scanf("%s", move);
            currentGameTurn(game, move, size);
            system("cls");
            
        }
    } else if (order == '3') {
        printf("leaderboard\n");
    } else if (order == '4') {
        printf("Come Again Later <3\n");
        return 0;
    } else {
        printf("invalid Command\n");
        return 1;
    }
}
