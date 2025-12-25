#include "movements.h"
#include "raylib.h"
#include <stdbool.h>




void movePieces(int rows, int cols, int players[][2],int player, int walls[][2], char wallsstates[] ,int wallcount, char move, int *showerror, int isWall[][cols][2]){
    if(player == -1)return;
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

int searchNearestPlayer(int hunter ,int playerCount , int huntersCount ,int PlHuDistance[huntersCount][playerCount]  ){
    int min = 30;
    int ans;
    for (int i = 0; i < playerCount; i++)
    {
        if (PlHuDistance[hunter][i] < min){
            min = PlHuDistance[hunter][i];
            ans = i;
        
        }
    }
    return ans;

    

}

void updateHunters(int row, int cols, int hunters[][2], int huntersCount, int players[][2],int playerCount, int PlHuDistance[huntersCount][playerCount] ,int walls[][2], char wallStates[],int wallsCount, int isWall[][cols][2], int isHunter[][cols]){
    
    for (int i = 0; i < huntersCount; i++)
    {
        int player = searchNearestPlayer(i, playerCount, huntersCount, PlHuDistance);
        int px = players[player][0];
        int py = players[player][1];

        int shx = hunters[i][0];
        int shy = hunters[i][1]; 
        if (shy - py > 1 && isWall[shx][shy - 1][1] == 0 && isWall[shx][shy - 2][1] == 0 && isHunter[shx][shy - 2] == 0)
        {
            isHunter[shx][shy] = 0;
            isHunter[shx][shy - 2] = 1;
            hunters[i][1] -= 2;
        }
        else if (shy - py < -1 && isWall[shx][shy][1] == 0 && isWall[shx][shy + 1][1] == 0 && isHunter[shx][shy + 2] == 0)
        {
            isHunter[shx][shy] = 0;
            isHunter[shx][shy + 2] = 1;
            hunters[i][1] += 2;
        }
        else if (shy - py > 0 && isWall[shx][shy - 1][1] == 0 && isHunter[shx][shy - 1] == 0)
        {
            isHunter[shx][shy] = 0;
            isHunter[shx][shy - 1] = 1;
            hunters[i][1] -= 1;
            if(shx - px > 0 && isWall[shx - 1][shy - 1][0] == 0 && isHunter[shx - 1][shy - 1] == 0)
            {
                isHunter[shx][shy - 1] = 0;
                isHunter[shx - 1][shy - 1] = 1;
                hunters[i][0] -= 1;
            }
            else if(shx - px < 0 && isWall[shx][shy - 1][0] == 0 && isHunter[shx + 1][shy - 1] == 0)
            {
                isHunter[shx][shy - 1] = 0;
                isHunter[shx + 1][shy - 1] = 1;
                hunters[i][0] += 1;
            }

        }
        else if(shy - py < 0 && isWall[shx][shy][1] == 0 && isHunter[shx][shy + 1] == 0)
        {
            isHunter[shx][shy] = 0;
            isHunter[shx][shy + 1] = 1;
            hunters[i][1] += 1;
            if(shx - px > 0 && isWall[shx - 1][shy + 1][0] == 0 && isHunter[shx - 1][shy + 1] == 0)
            {
                isHunter[shx][shy + 1] = 0;
                isHunter[shx - 1][shy + 1] = 1;
                hunters[i][0] -= 1;
            }
            else if(shx - px < 0 && isWall[shx][shy + 1][0] == 0 && isHunter[shx + 1][shy + 1] == 0)
            {
                isHunter[shx][shy + 1] = 0;
                isHunter[shx + 1][shy + 1] = 1;
                hunters[i][0] += 1;
            }
        }
        else {
            if (shx - px > 1 && isWall[shx - 1][shy][0] == 0 && isWall[shx - 2][shy][0] == 0 && isHunter[shx - 2][shy] == 0)
            {
                isHunter[shx][shy] = 0;
                isHunter[shx - 2][shy] = 1;
                hunters[i][0] -= 2;
            }
            else if (shx - px < -1 && isWall[shx][shy][0] == 0 && isWall[shx + 1][shy][0] == 0 && isHunter[shx + 2][shy] == 0)
            {
                isHunter[shx][shy] = 0;
                isHunter[shx + 2][shy] = 1;
                hunters[i][0] += 2;
            
            }
            else if (shx - px > 0 && isWall[shx - 1][shy][0] == 0 && isHunter[shx - 1][shy] == 0)
            {
                isHunter[shx][shy] = 0;
                isHunter[shx - 1][shy] = 1;
                hunters[i][0] -= 1;
            }
            else if (shx - px < 0 && isWall[shx][shy][0] == 0 && isHunter[shx + 1][shy] == 0)
            {
                isHunter[shx][shy] = 0;
                isHunter[shx + 1][shy] = 1;
                hunters[i][0] += 1;
            
            } 
        }
        
        
        
        
        
    }
    
}


void Win(int height, int width,int lightcoreX, int lightcoreY, int players[][2], int playerCount, Font f, float *fontsize, float maxsize, float speed, int *GameStoppage){
    for(int i = 0; i < playerCount; i++){
        if (players[i][0] == lightcoreX && players[i][1] == lightcoreY)
        {
            if (*fontsize < maxsize)
            {
                *fontsize += speed * GetFrameTime();
            }
            char str[15] = "You Won!";
            Color color = {0,194,50,255};
            
            
            Vector2 textSize = MeasureTextEx(f, str, *fontsize, 2);
            Vector2 pos = {width/2 , height/2};
            Vector2 origin = {textSize.x / 2, textSize.y/2};
            DrawTextPro(f, str, pos, origin, 0.0f, *fontsize, 2, color);
            *GameStoppage=1;
        }
        

    }
}

void Lose(int height, int width, int cols,int players[][2], int playerCount , int hunters[][2], int isHunter[][cols], float *fontsize,float maxsize, float speed , Font f, int *GameStoppage, int LightcoreH, int LightcoreW){
    for (int i = 0; i < playerCount; i++)
    {
        int px = players[i][0];
        int py = players[i][1];
        if (isHunter[px][py] == 1 && (px!=LightcoreH || py!=LightcoreW))
        {
            if (*fontsize < maxsize)
            {
                *fontsize += speed * GetFrameTime();
            }

            char str[15] = "You Lost!";
            Color color = {255,0,0,255};
            
            
            Vector2 textSize = MeasureTextEx(f, str, *fontsize, 2);
            Vector2 pos = {width/2 , height/2};
            Vector2 origin = {textSize.x / 2, textSize.y/2};
            DrawTextPro(f, str, pos, origin, 0.0f, *fontsize, 2, color);
            *GameStoppage=1;
        }
        
    }
}







