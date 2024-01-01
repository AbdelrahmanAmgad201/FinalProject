#include "display.h"


void printData(gameState*currentGame)
{
    printf("\n");
    printf(RED"%s score: %d\n"RESET,currentGame->player1Name,currentGame->score1);
    printf(BLUE"%s score: %d\n"RESET,currentGame->player2Name,currentGame->score2);
    printf(YELLOW"Cells Left: %d\n"RESET,currentGame->size*currentGame->size-currentGame->cellsFilled);
    printf(YELLOW"Time Passed: %d\n"RESET,currentGame->time);
}


char printMenuAndGetCommand() {
    char command;
    printf(MAGENTA"   DOTS AND BOXES\n"RESET CYAN"\n1)2X2\n2)5x5\n3)leaderboard\n4)Load\n5)Exit Game\n"RESET);
    scanf(" %c", &command);
    return command;
}

void printBoard(cell **cells, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("+");
            if (cells[i][j].up == 1) {
                printf( RED "---------" RESET );
            } else if (cells[i][j].up == 2) {
                printf( BLUE "---------" RESET );
            } else {
                printf("         ");
            }
        }
        printf("+\n");
        for(int x = 0 ; x<3 ; x++)
        {
            for (int j = 0; j < size; j++) {
            if (cells[i][j].left == 1) {
                if(cells[i][j].fillCount == 4)
                {
                    printf(RED "|"RESET  RED_BACKGROUND"         " COLOR_RESET);
                }
                else
                {
                    printf(RED "|         " RESET);
                }
                
            } else if (cells[i][j].left == 2) {
                if(cells[i][j].fillCount == 4)
                {
                    printf(BLUE "|"RESET  BLUE_BACKGROUND"         " COLOR_RESET);
                }
                else
                {
                    printf(BLUE "|         " RESET);
                }
                
            } else {
                printf("          ");
            }

            if (cells[i][j].right == 1 && j == size - 1) {
                printf(RED "|" RESET);
            } else if (cells[i][j].right == 2 && j == size - 1) {
                printf(BLUE "|" RESET);
            } 
        }

        printf("\n");
        }
        if (i == size - 1) {
            for (int j = 0; j < size; j++) {
                printf("+");
                if (cells[i][j].bottom == 1) {
                    printf(RED "---------" RESET);
                } else if (cells[i][j].bottom == 2) {
                    printf(BLUE "---------" RESET);
                }
                else{
                    printf("         ");
                }
            }
            printf("+");
        }
    }
}