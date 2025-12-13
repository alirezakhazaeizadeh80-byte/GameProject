#include "movements.h"



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



void updateShadowWatchers(int row, int cols, int shadowWatcher[][2], int shadowWatcherCount, int players[][2], int player, int walls[][2], char wallStates[],int wallsCount, int isWall[][cols][2], int isShadowWatcher[][cols]){
    for (int i = 0; i < shadowWatcherCount; i++)
    {
        int px = players[player][0];
        int py = players[player][1];

        int shx = shadowWatcher[i][0];
        int shy = shadowWatcher[i][1]; 
        if (shy - py > 1 && isWall[shx][shy - 1][1] == 0 && isWall[shx][shy - 2][1] == 0 && isShadowWatcher[shx][shy - 2] == 0)
        {
            isShadowWatcher[shx][shy] = 0;
            isShadowWatcher[shx][shy-2] = 1;
            shadowWatcher[i][1] -= 2;
        }
        else if (shy - py < -1 && isWall[shx][shy][1] == 0 && isWall[shx][shy + 1][1] == 0 && isShadowWatcher[shx][shy + 2] == 0)
        {
            isShadowWatcher[shx][shy] = 0;
            isShadowWatcher[shx][shy + 2] = 1;
            shadowWatcher[i][1] += 2;
        }
        else if (shy - py > 0 && isWall[shx][shy - 1][1] == 0 && isShadowWatcher[shx][shy - 1] == 0)
        {
            isShadowWatcher[shx][shy] = 0;
            isShadowWatcher[shx][shy - 1] = 1;
            shadowWatcher[i][1] -= 1;
            shy-=1;
            if(shx - px > 0 && isWall[shx - 1][shy][0] == 0 && isShadowWatcher[shx - 1][shy] == 0)
            {
                isShadowWatcher[shx][shy] = 0;
                isShadowWatcher[shx][shy - 1] = 1;
                shadowWatcher[i][0] -= 1;
            }
            else if(shx - px < 0 && isWall[shx][shy][0] == 0 && isShadowWatcher[shx + 1][shy] == 0)
            {
                isShadowWatcher[shx][shy] = 0;
                isShadowWatcher[shx][shy + 1] = 1;
                shadowWatcher[i][0] += 1;
            }

        }
        else if(shy - py < 0 && isWall[shx][shy][1] == 0 && isShadowWatcher[shx][shy + 1] == 0)
        {
            isShadowWatcher[shx][shy] = 0;
            isShadowWatcher[shx][shy + 1] = 1;
            shadowWatcher[i][1] += 1;
            shy+=1;
            if(shx - px > 0 && isWall[shx - 1][shy][0] == 0 && isShadowWatcher[shx - 1][shy] == 0)
            {
                isShadowWatcher[shx][shy] = 0;
                isShadowWatcher[shx][shy - 1] = 1;
                shadowWatcher[i][0] -= 1;
            }
            else if(shx - px < 0 && isWall[shx][shy][0] == 0 && isShadowWatcher[shx + 1][shy] == 0)
            {
                isShadowWatcher[shx][shy] = 0;
                isShadowWatcher[shx][shy + 1] = 1;
                shadowWatcher[i][0] += 1;
            }
        }
        else {
            if (shx - px > 1 && isWall[shx - 1][shy][0] == 0 && isWall[shx - 2][shy][0] == 0 && isShadowWatcher[shx - 2][shy] == 0)
            {
                isShadowWatcher[shx][shy] = 0;
                isShadowWatcher[shx][shy - 2] = 1;
                shadowWatcher[i][0] -= 2;
            }
            else if (shx - px < -1 && isWall[shx][shy][0] == 0 && isWall[shx + 1][shy][0] == 0 && isShadowWatcher[shx + 2][shy] == 0)
            {
                isShadowWatcher[shx][shy] = 0;
                isShadowWatcher[shx][shy + 2] = 1;
                shadowWatcher[i][0] += 2;
            
            }
            else if (shx - px > 0 && isWall[shx - 1][shy][0] == 0 && isShadowWatcher[shx - 1][shy] == 0)
            {
                isShadowWatcher[shx][shy] = 0;
                isShadowWatcher[shx][shy - 1] = 1;
                shadowWatcher[i][0] -= 1;
            }
            else if (shx - px < 0 && isWall[shx][shy][0] == 0 && isShadowWatcher[shx + 1][shy] == 0)
            {
                isShadowWatcher[shx][shy] = 0;
                isShadowWatcher[shx][shy + 1] = 1;
                shadowWatcher[i][0] += 1;
            
            } 
        }
        
        
        
        
        
    }
    
}





