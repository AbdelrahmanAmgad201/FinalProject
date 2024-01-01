#include "undoRedo.h"

void undo(gameState *currentGame, gameState history[], int *count)
{
    if ((*count) > 0 )
    {
                (*count)--;
                printf("UNDOO");
                currentGame->score1 = history[*count].score1;
                currentGame->score2 = history[*count].score2;
                currentGame->cellsFilled = history[*count].cellsFilled;
                strcpy(currentGame->player1Name , history[*count].player1Name);
                strcpy(currentGame->player2Name , history[*count].player2Name);
                for(int i = 0 ; i<currentGame->size ; i++)
                {
                    for(int j = 0 ; j<currentGame->size ; j++)
                    {
                        currentGame->cells[i][j] = history[*count].cells[i][j];
                    }
                }
    }
    else{
        printf("No valid Undo");
    }

}

void redo(gameState *currentGame, gameState history[], int *count)
{
    if (history[(*count) + 1].turn != 0)
    {
        (*count)++;
        currentGame->score1 = history[*count].score1;
        currentGame->score2 = history[*count].score2;
        currentGame->cellsFilled = history[*count].cellsFilled;
        strcpy(currentGame->player1Name , history[*count].player1Name);
        strcpy(currentGame->player2Name , history[*count].player2Name);
        for(int i = 0 ; i<currentGame->size ; i++)
        {
            for(int j = 0 ; j<currentGame->size ; j++)
            {
                currentGame->cells[i][j] = history[*count].cells[i][j];
            }
        }
        

    }
}