#include "movements.h"

/*int checkWall(int walls[][2], int wallsCount,char wallStates[] ,char state, int wallx, int wally){
    if (state == 'H')
    {
        for (int i = 0; i < wallsCount; i++)
        {
            if (walls[i][0] == wallx && walls[i][1] == wally && wallStates[i] == 'H')
            {
                return 1;
            }
            
        }
        
    }    
    else if (state == 'V')
    {
        for (int i = 0; i < wallsCount; i++)
        {
            if (walls[i][0] == wallx && walls[i][1] == wally && wallStates[i] == 'V')
            {
                return 1;
            }
            
        }

        
    }
    return 0;
}*/
/*int hitWalls(int rows, int cols, int players[][2],int player, int walls[][2], int wallcount, char wallsstates[] , char move){
    int px = players[player][0];
    int py = players[player][1];
    if (move == 'W')
    {    
        for (int i = 0; i < wallcount; i++)
        {
            if (wallsstates[i] == 'H'){
                if ( walls[i][0] == px - 1 && walls[i][1] == py)
                {
                    return 1;
                }
            }
            
        }
    }    
    else if (move == 'S')
    {
        for(int i = 0; i < wallcount; i++){
            if(wallsstates[i] == 'H'){
               if ( walls[i][0] == px && walls[i][1] == py)
                {
                    return 1;
                }
        }        
        }
    }
    else if (move == 'A')
    {
        for(int i = 0; i < wallcount; i++){
            if(wallsstates[i] == 'V'){
                if ( walls[i][0] == px && walls[i][1] == py - 1)
                {
                    return 1;
                }
            }
        }
    }
    else if (move == 'D')
    {
        for(int i = 0; i < wallcount; i++){
            if(wallsstates[i] == 'V'){
                if ( walls[i][0] == px && walls[i][1] == py)
                {
                    return 1;
                }
            }    
        }
    }


    
    
}*/



void movePieces(int rows, int cols, int players[][2],int player, int walls[][2], char wallsstates[] ,int wallcount, char move, int *showerror, int isWall[][cols][2]){
    int px = players[player][0];
    int py = players[player][1];
    if (move == 'W' && (px <= 0 || isWall[px - 1][py][0] == 1))
    {
        *showerror = 1;
    }
    else if (move == 'W')
    {
        players[player][0] -= 1;
    }
    if (move == 'A' && (py <= 0 || isWall[px][py - 1][1] == 1))
    {
        *showerror = 1;
    }
    else if (move == 'A')
    {
        players[player][1] -= 1;
    }
    if (move == 'S' && (px >= ( rows - 1) || isWall[px][py][0] == 1) )
    {
        *showerror = 1;
    }
    else if (move == 'S')
    {
        players[player][0] += 1;
    }
    if (move == 'D' && (py >= (cols - 1) ||  isWall[px][py][1] == 1))
    {
        *showerror = 1;
    }
    else if (move == 'D')
    {
        players[player][1] += 1;
    }



}



void updateShadowWatchers(int row, int cols, int shadowWatcher[][2], int shadowWatcherCount, int players[][2], int player, int walls[][2], char wallStates[],int wallsCount, int isWall[][cols][2]){
    for (int i = 0; i < shadowWatcherCount; i++)
    {
        int px = players[player][0];
        int py = players[player][1];

        int shx = shadowWatcher[i][0];
        int shy = shadowWatcher[i][1]; 
        if (shy - py > 0 && isWall[shx][shy - 1][1] == 0 && isWall[shx][shy - 2][1] == 0 )
        {
            shadowWatcher[i][1] -= 2;
        }
        else if (shy - py < 0 && isWall[shx][shy][1] == 0 && isWall[shx][shy + 1][1] == 0)
        {
            shadowWatcher[i][1] += 2;
        }
        else if (shy - py > 0 && isWall[shx][shy - 1][1] == 0)
        {
            shadowWatcher[i][1] -= 1;
            if(shx - px > 0 && isWall[shx - 1][shy][0] == 0)
            {
                shadowWatcher[i][0] -= 1;
            }
        }
        else if(shy - py < 0 && isWall[shx][shy][1] == 0)
        {
            shadowWatcher[i][1] += 1;
            if (shx - px < 0 && isWall[shx][shy][0] == 0)
            {
                shadowWatcher[i][0] += 1;
            
            }
        }
        else {
            if (shx - px > 0 && isWall[shx - 1][shy][0] == 0 && isWall[shx - 2][shy][0] == 0 )
            {
                shadowWatcher[i][0] -= 2;
            }
            else if (shx - px < 0 && isWall[shx][shy][0] == 0 && isWall[shx + 1][shy][0] == 0)
            {
                shadowWatcher[i][0] += 2;
            
            }
            else if (shx - px > 0 && isWall[shx - 1][shy][0] == 0 )
            {
                shadowWatcher[i][0] -= 1;
            }
            else if (shx - px < 0 && isWall[shx][shy][0] == 0)
            {
                shadowWatcher[i][0] += 1;
            
            } 
        }
        
        
        
        
        
    }
    
}





