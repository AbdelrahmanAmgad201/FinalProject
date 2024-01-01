#include "functions.h"
#include "saveLoad.h"
#include "leaderboard.h"

// Compile command: gcc main.c functions.c saveLoad.c leaderboard.c dfs.c undoRedo.c display.c -o DotsAndBoxes

char savefiles[10][14] = {
  "savefile1.bin",
  "savefile2.bin",
  "savefile3.bin",
  "savefile4.bin",
  "savefile5.bin",
  "savefile6.bin",
  "savefile7.bin",
  "savefile8.bin",
  "savefile9.bin",
  "savefile10.bin"
};




int gameLoop(gameState * game, int size, int historySize, int loaded) {
  int mode;
  if (loaded == 0) {
    printf("1) Multiplayer\n2) Vs Computer\n3) Exit\n");

    do {
      if (scanf("%d", & mode) != 1) {
        // Input was not a valid integer, handle accordingly
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n'); // Consume invalid input
      } else {
        system("cls");
        if (mode == 1 || mode == 2 || mode == 3) {
          // Valid command, break out of the loop
          break;
        } else {
          printf("Enter a Valid command (1 for multiplayer, 2 for AI, 3 to Exit): \n");
        }
      }
    } while (1);
  }
  char typeofMove = '8';
  game -> size = size;
  if (loaded == 0) {
    if (mode == 2) {
      game -> flagComp = 1;
    } else {
      game -> flagComp == 0;
    }
    if (loaded == 0) {
      createArr(game, game -> size);
      scanNames(game);
      initializeGameState(game);
    }
  }
  system("cls");
  gameState history[historySize];
  int counter = 0;
  for (int i = 0; i < historySize; i++) {
    initializeGameState( & history[i]);
    strcpy(history[0].player1Name , game->player1Name);
    strcpy(history[0].player2Name , game->player2Name);
    history[i].turn = 0;
    createArr( & history[i], size);
  }
  clock_t startTime = clock();
  while (1) {
    if (typeofMove == '1') {
      updateHistory(game, history, counter);
    }

    int replay = CheckWinner(game);
    if (replay == 1) {
      return 1;
    }
    printf(MAGENTA "   DOTS AND BOXES\n" RESET);
    printBoard(game -> cells, game -> size);
    printData(game);
    printf(CYAN"\n\n1)continue\n2)undo\n3)redo\n4)Save\n5)Exit Game\n"RESET);
    (game -> turn == 1) ? printf(RED"\n%s: "RESET, game -> player1Name): printf(BLUE "\n%s: "RESET, game -> player2Name);
    if(game->turn == 2 && game->flagComp == 1)
    {
      typeofMove = '1';
    }
    else{
       do {
        printf("Enter your choice (1-5): ");
        if (scanf(" %c", &typeofMove) != 1 || typeofMove < '1' || typeofMove > '5') {
            printf("Invalid input. Please enter a valid command (1-5).\n");
            while (getchar() != '\n');  // Clear the buffer
        }

    } while (typeofMove < '1' || typeofMove > '5');

    }
   
    if (typeofMove == '1') {
      currentGameTurn(game, history, counter);
      counter++;
    } else if (typeofMove == '2') {
      undo(game, history, & counter);
    } else if (typeofMove == '3') {
      redo(game, history, & counter);
    } else if (typeofMove == '4') {
      char n_char;
      int n;
      printf(MAGENTA "FILE NUMBER : \n" RESET);
       while (getchar() != '\n');
      scanf("%c", & n_char);
      if (n>=1 && n<=10)
      {
         saveGameState(savefiles[n - 1], game);
      }
      else{
        printf("invalid filename ... returning to the game \n\n");
        continue;
      }
     
    } else if (typeofMove == '5') {
      printf("Exiting :( \n");
      exit(0);
    }
    clock_t endTime = clock();
    game -> time = (endTime - startTime) / CLOCKS_PER_SEC;
    system("cls");

  }
}




int main() {
  while (1) {
    int replay;
    char order = printMenuAndGetCommand();
    system("cls");
    if (order == '1') {
      gameState * game = (gameState * ) malloc(sizeof(gameState));
      game -> flagComp = 0;
      replay = gameLoop(game, 2, 13, 0);
      if (replay == 1) {
        system("cls");
        continue;
      }
      free(game->cells);
      free(game);
    } else if (order == '2') {
      char typeofMove[2];
      gameState * game = (gameState * ) malloc(sizeof(gameState));
      game -> flagComp = 0;
      replay = gameLoop(game, 5, 61, 0);
      if (replay == 1) {
        system("cls");
        continue;
      }
      free(game->cells);
      free(game);
    } else if (order == '3') {
      displayLeaderboard();
    } else if (order == '4') {
      gameState * game = (gameState * ) malloc(sizeof(gameState));
      char n_char ;
      int n;
      do
      {
        printf(YELLOW "File number: \n" RESET);
         while (getchar() != '\n');
        scanf("%c", & n_char);
        n = n_char - '0' ;
        if(n>=1 && n<=10)
        {
          loadGameState(savefiles[n - 1], game);
          replay = gameLoop(game, game -> size, 61, 1);
          free(game->cells);
          free(game);
          break;
        }
        else{
          system("cls");
          printf("Enter a valid number between 1-10\n");
        }
        
      } while (1);
      if (replay == 1) {
        system("cls");
        continue;
      }
      
      free(game);
    } else if (order == '5') {
      printf("Come Again Later <3\n");
      return 0;
    } else {
      printf(RED "invalid Command\n" RESET);
      return 1;
    }

  }
}