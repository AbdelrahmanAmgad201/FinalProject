#include "functions.h"


void scanNames(gameState *game) {
    printf("Player 1 name: ");
    scanf("%19s", game->player1Name);
    while (getchar() != '\n');  // Consume remaining characters in the input buffer

    if (game->flagComp == 0) {
        printf("Player 2 name: ");
        scanf("%19s", game->player2Name);
        while (getchar() != '\n');  // Consume remaining characters in the input buffer
    } else if (game->flagComp == 1) {
        strcpy(game->player2Name, "computer");
    }
    for (int i = 0; game->player1Name[i] != '\0'; i++) {
        game->player1Name[i] = tolower(game->player1Name[i]);
    }

    for (int i = 0; game->player2Name[i] != '\0'; i++) {
        game->player2Name[i] = tolower(game->player2Name[i]);
    }
}



void createArr(gameState *game , int size) { //create 2d array of cells
    game->cells = (cell **)malloc(size * sizeof(cell *));
    for (int i = 0; i < size; i++) {
        // Allocate and initialize memory for each row using calloc
        game->cells[i] = (cell *)calloc(size, sizeof(cell));
    }
}

void initializeGameState(gameState *game) { //initialize the game state at the beginning of each game
    game->score1 = 0;
    game->score2 = 0;
    game->time = 0;
    game->turn = 1;
    game->cellsFilled = 0;
}



int checkCellFull(gameState *currentGame, int i, int j) {
    if (currentGame->cells[i][j].fillCount == 4) {
        (currentGame->turn == 1) ? (currentGame->score1++) : (currentGame->score2++);
        currentGame->cellsFilled++;
        currentGame->cells[i][j].up = currentGame->turn;
        currentGame->cells[i][j].bottom = currentGame->turn;
        currentGame->cells[i][j].left = currentGame->turn;
        currentGame->cells[i][j].right = currentGame->turn;

        // Update neighboring cells
        if (i != 0) {
            currentGame->cells[i - 1][j].bottom = currentGame->turn;
        }
        if (i != currentGame->size - 1) {
            currentGame->cells[i + 1][j].up = currentGame->turn;
        }
        if (j != 0) {
            currentGame->cells[i][j - 1].right = currentGame->turn;
        }
        if (j != currentGame->size - 1 && currentGame->cells[i][j + 1].fillCount!=4) {
            currentGame->cells[i][j + 1].left = currentGame->turn;
        }

        return 1;
    }

    return 0;
}
void updateHistory(gameState * game, gameState history[], int counter) {
  history[counter].flagComp = game -> flagComp;
  history[counter].size = game -> size;
  history[counter].turn = game -> turn;
  history[counter].score1 = game -> score1;
  history[counter].score2 = game -> score2;
  history[counter].cellsFilled = game -> cellsFilled;
  strcpy(history[counter].player1Name, game -> player1Name);
  strcpy(history[counter].player2Name, game -> player2Name);
  for (int i = 0; i < game -> size; i++) {
    for (int j = 0; j < game -> size; j++) {
      history[counter].cells[i][j] = game -> cells[i][j];
    }
  }

}

int CheckWinner(gameState *currentGame) {
    int size = currentGame->size;
    if (currentGame->cellsFilled == size * size) {
        printf(MAGENTA"   DOTS AND BOXES\n"RESET);
        printBoard(currentGame->cells, currentGame->size);
        printf("\n");
        printData(currentGame);
        if (currentGame->score1 > currentGame->score2) {
            printf(RED "%s "RESET"is the Winner !!", currentGame->player1Name);
            saveWinner(currentGame->player1Name, currentGame->score1);
        } else if (currentGame->score1 < currentGame->score2) {
            printf(BLUE "%s "RESET"is the Winner !!", currentGame->player2Name);
            saveWinner(currentGame->player2Name, currentGame->score2);
        } else {
            printf(RED"DR"BLUE"AW"RESET" :(");
        }

        printf("\n1) Play Again\n2) Exit Game\n");
        char input;
        scanf(" %c", &input);
        if (input == '1') {
            return (1);
        } else if (input == '2') {
            
            exit(0);
        } else {
            // Invalid input, handle accordingly
            printf("Invalid input. Exiting game.\n");
            exit(1);
        }
    }
   
}
void checkValidity(gameState* currentGame, int* i, int* j, char* k)
{
    int size = currentGame->size;

    while (*i > size - 1 || *i < 0 || *j > size - 1 || *j < 0 ||
           (*k != 'u' && *k != 'b' && *k != 'r' && *k != 'l') ||
           (*k == 'u' && currentGame->cells[*i][*j].up != 0) ||
           (*k == 'b' && currentGame->cells[*i][*j].bottom != 0) ||
           (*k == 'r' && currentGame->cells[*i][*j].right != 0) ||
           (*k == 'l' && currentGame->cells[*i][*j].left != 0))
    {
        printf(RED"Please enter a valid command: "RESET);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        char newMove[5];
        fgets(newMove, sizeof(newMove), stdin);
        *i = (newMove[0] - '0') - 1;
        *j = (newMove[1] - '0') - 1;
        *k = newMove[2];
    }
}




void currentGameTurn(gameState *currentGame,gameState history[], int count ) {
        for(int i = count+1 ; history[i].turn != 0 ;i++)
        {
            history[i].turn = 0 ;
        }
        if((currentGame->flagComp) == 1 && (currentGame->turn == 2))
        {
            int x = 1;
            int targets[] = {3,1,0,2};
            int played = 0;
            while(x == 1)
            {
                played = 0;
                for(int i = 0 ; i<4 && !played; i++)
                {
                    
                    x=computerTurn(currentGame , targets[i]);
                    printf("%d ",x);
                    played = (x!=0)? 1 : 0;
                }

            }
        }
        else{
            int size = currentGame->size ;
            printf("Enter Your Move:");
            char move[5];
            scanf(" %3s", move);    
            int i = (move[0] - '0') - 1;
            int j = (move[1] - '0') - 1;
            char k = move[2];
            checkValidity(currentGame,&i,&j,&k);
            if(chainChecker(currentGame, i ,j ,k) == 1)
            {
            placeLine(currentGame,i,j,k);
            }

        }
      

    }
void placeLine (gameState*currentGame, int i , int j , char k )
{
    int flag = 0;
    int size = currentGame->size ;
    if (k == 'u') {
        currentGame->cells[i][j].up = currentGame->turn;
        if (i != 0) {
            currentGame->cells[i - 1][j].bottom = currentGame->turn;
            currentGame->cells[i - 1][j].fillCount++;
            flag = checkCellFull(currentGame,i-1,j);
            
        }
    } else if (k == 'b') {
        currentGame->cells[i][j].bottom = currentGame->turn;
        if (i != size - 1) {
            currentGame->cells[i + 1][j].up = currentGame->turn;
            currentGame->cells[i + 1][j].fillCount++;
            flag = checkCellFull(currentGame,i+1,j);
        }
    } else if (k == 'r') {
        currentGame->cells[i][j].right = currentGame->turn;
        if (j != size - 1) {
            currentGame->cells[i][j + 1].left = currentGame->turn;
            currentGame->cells[i][j + 1].fillCount++;
            flag = checkCellFull(currentGame,i,j+1);
        }
    } else if (k == 'l') {
        currentGame->cells[i][j].left = currentGame->turn;
        if (j != 0) {  // Fix: Check if j is not at the beginning of the row
            currentGame->cells[i][j - 1].right = currentGame->turn;
            currentGame->cells[i][j - 1].fillCount++;
            flag = checkCellFull(currentGame,i,j-1);
        }
    }
    currentGame->cells[i][j].fillCount++;
    if (!(checkCellFull(currentGame, i, j) || flag )) {
        currentGame->turn = (currentGame->turn == 1) ? 2 : 1;
    }

}

int computerTurn(gameState*currentGame, int target)
{
    int size = currentGame->size ;
    char move[4];
    int flag = 0;
    int placed = 0 ;
    for(int i = 0 ; i <size && !placed ; i++)
    {
        for(int j = 0 ; j<size && !placed ;j++)
        {
            if(currentGame->cells[i][j].fillCount == target)
            {
                placed = 1;
                if(target == 3) {flag = 1;}
                else { flag = 2;}
                if(currentGame->cells[i][j].up == 0)
                {
                   placeLine(currentGame,i,j,'u');
                }
                else if(currentGame->cells[i][j].bottom == 0)
                {
                   placeLine(currentGame,i,j,'b');
                }
                else if(currentGame->cells[i][j].left == 0)
                {
                    placeLine(currentGame,i,j,'l');    
                }
                else if(currentGame->cells[i][j].right == 0){
                    placeLine(currentGame,i,j,'r');  
                }
            }
        }
    }
    return flag;
}


    