#include "dfs.h"
#include "functions.h"


int chainChecker(gameState*currentGame , int i , int j , char k)
{
    int **visited;
    visited = (int**)malloc(currentGame->size * sizeof(int*));
    for (int i = 0; i < currentGame->size; i++)
    {
        visited[i] = (int *)calloc(currentGame->size, sizeof(int));
    }
    //                        up      down    left     right
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int stop  = 0 ;

    dfs(currentGame,i,j,visited,-1,&stop,directions);
    for(int w = 0 ; w<currentGame->size ; w++)
    {
        for(int r = 0 ; r<currentGame->size ; r++ )
        {
            printf("%d",visited[w][r]);
        }
        printf("\n");
    }
    printf("%d",stop);
    
    if(stop != 1)
    {
         for(int x = 0 ; x<currentGame->size ; x++)
         {
            for(int y = 0 ; y<currentGame->size ; y++)
            {
                if(visited[x][y] == 1)
                {
                    if(currentGame->cells[x][y].up == 0)
                    {
                    placeLine(currentGame,x,y,'u');
                    }
                    else if(currentGame->cells[x][y].bottom == 0)
                    {
                    placeLine(currentGame,x,y,'b');
                    }
                    else if(currentGame->cells[x][y].left == 0)
                    {
                        placeLine(currentGame,x,y,'l');    
                    }
                    else if(currentGame->cells[x][y].right == 0){
                        placeLine(currentGame,x,y,'r');  
                    }
                    
                }
            }
         }
    }
   
    for (int i = 0; i < currentGame->size; i++)
        {
        free(visited[i]);
        }
    free(visited);
    return stop;
}
void dfs(gameState*currentGame , int i , int j , int **visited , int cameFrom , int *stop , int directions[4][2])
{

    if (*stop == 1)
    {
        return;
    }

    visited[i][j] = 1 ;

    for(int d = 0 ; d<4 ; d++)
    {
        if(d == cameFrom)
            continue;
        if(d == 0 && currentGame->cells[i][j].up != 0)
            continue;
        if(d == 1 && currentGame->cells[i][j].bottom != 0)
            continue;
        if(d == 2 && currentGame->cells[i][j].left != 0)
            continue;
        if(d == 3 && currentGame->cells[i][j].right != 0)
            continue;
        int newI = i+directions[d][0];
        int newJ = j+directions[d][1];
        if((newI >= 0 && newI<=(currentGame->size)-1) && (newJ >= 0 && newJ<=(currentGame->size)-1) && !(visited[newI][newJ]))
        {
            int newCameFrom = -1 ;

            if(d == 0) newCameFrom = 1 ;
            else if(d == 1) newCameFrom = 0 ;
            else if(d == 2) newCameFrom = 3 ;
            else if(d == 3) newCameFrom = 2 ;
            dfs(currentGame,newI,newJ,visited,newCameFrom,stop,directions);
            
        }
        else 
        {
            *stop = 1 ;
            return ;
        }     
    }

}    