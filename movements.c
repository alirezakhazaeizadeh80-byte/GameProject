#include "movements.h"
#include "raylib.h"
#include <stdbool.h>
#include "pathfinding.h"
#include <stdio.h>


int isPlayer(int players[][2], int alivePlayers, int x, int y){
    for(int i=0; i<alivePlayers; i++){
        if(players[i][0] == x && players[i][1] == y)return 1;
    }
    return 0;
}
void movePieces(int rows, int cols, int players[][2],int player, int walls[][2], char wallsstates[] ,int wallcount, char move, int *showerror, int isWall[][cols][2], int alivePlayers){
    if(player == -1)return;
    int px = players[player][0];
    int py = players[player][1];
    if (move == 'W' && (px <= 0 || isWall[px - 1][py][0] == 1 || isPlayer(players, alivePlayers, px - 1, py)))
    {
        *showerror = 1;
    }
    else if (move == 'W')
    {
        players[player][0] -= 1;
    }
    if (move == 'A' && (py <= 0 || isWall[px][py - 1][1] == 1 || isPlayer(players, alivePlayers, px, py - 1)))
    {
        *showerror = 1;
    }
    else if (move == 'A')
    {
        players[player][1] -= 1;
    }
    if (move == 'S' && (px >= ( rows - 1) || isWall[px][py][0] == 1 || isPlayer(players, alivePlayers, px + 1, py)))
    {
        *showerror = 1;
    }
    else if (move == 'S')
    {
        players[player][0] += 1;
    }
    if (move == 'D' && (py >= (cols - 1) ||  isWall[px][py][1] == 1 || isPlayer(players, alivePlayers, px, py + 1)))
    {
        *showerror = 1;
    }
    else if (move == 'D')
    {
        players[player][1] += 1;
    }


}

int searchNearestPlayer(int hunter ,int playercount ,int alivePlayers , int huntersCount ,int PlHuDistance[huntersCount][playercount]){
    int min = 30;
    int ans;
    for (int i = 0; i < alivePlayers; i++)
    {
        if (PlHuDistance[hunter][i] < min){
            min = PlHuDistance[hunter][i];
            ans = i;
        }
    }
    return ans;
}

void updateHunters(int row, int cols, int playercount, int hunters[][2], int huntersCount, int players[][2],int alivePlayers, int PlHuDistance[][playercount] ,int walls[][2], char wallStates[],int wallsCount, int isWall[][cols][2], int isHunter[][cols], Pair *path, int *pathcount, int isBonus[][cols]){
    int moved = 0;
    // int ignore[alivePlayers];
    // for(int j = 0; j < alivePlayers; j++)ignore[j] = 0;
    for (int i = 0; i < huntersCount; i++)
    {
        int player = searchNearestPlayer(i, playercount, alivePlayers, huntersCount, PlHuDistance);
        // if (player == -1){ // means no player that hunter gets nearer to it
        //     for(int j = 0; j < alivePlayers; j++)ignore[j] = 0; // modify ignore[] for next hunter
        //     continue;
        // }
        int px = players[player][0];
        int py = players[player][1];
        int shx = hunters[i][0];
        int shy = hunters[i][1];
        aStar(row, cols, isWall, (Pair){shx,shy}, (Pair){px,py}, path, pathcount, isBonus);
        printf("%d\n", *pathcount);
        if(*pathcount != 0){
            isHunter[shx][shy] = 0;
            int r = path[*pathcount-2].row;
            int c = path[*pathcount-2].col;

            if(*pathcount >= 2 && isHunter[r][c] == 0){
                isHunter[r][c] = 1;
                hunters[i][0] = r;
                hunters[i][1] = c;
            }

            else{
                r = path[*pathcount-1].row;
                c = path[*pathcount-1].col;            
                if(isHunter[r][c] == 0){
                    isHunter[r][c] = 1;
                    hunters[i][0] = r;
                    hunters[i][1] = c;
                }
            }
        }

        // if (shy - py > 1 && isWall[shx][shy - 1][1] == 0 && isWall[shx][shy - 2][1] == 0 && isHunter[shx][shy - 2] == 0)
        // {
        //     isHunter[shx][shy] = 0;
        //     isHunter[shx][shy - 2] = 1;
        //     hunters[i][1] -= 2;
        //     moved = 1;
        // }
        // else if (shy - py < -1 && isWall[shx][shy][1] == 0 && isWall[shx][shy + 1][1] == 0 && isHunter[shx][shy + 2] == 0)
        // {
        //     isHunter[shx][shy] = 0;
        //     isHunter[shx][shy + 2] = 1;
        //     hunters[i][1] += 2;
        //     moved = 1;
        // }
        // else if (shy - py > 0 && isWall[shx][shy - 1][1] == 0 && isHunter[shx][shy - 1] == 0)
        // {
        //     isHunter[shx][shy] = 0;
        //     isHunter[shx][shy - 1] = 1;
        //     hunters[i][1] -= 1;
        //     moved = 1;
        //     if(shx - px > 0 && isWall[shx - 1][shy - 1][0] == 0 && isHunter[shx - 1][shy - 1] == 0)
        //     {
        //         isHunter[shx][shy - 1] = 0;
        //         isHunter[shx - 1][shy - 1] = 1;
        //         hunters[i][0] -= 1;
        //         moved = 1;
        //     }
        //     else if(shx - px < 0 && isWall[shx][shy - 1][0] == 0 && isHunter[shx + 1][shy - 1] == 0)
        //     {
        //         isHunter[shx][shy - 1] = 0;
        //         isHunter[shx + 1][shy - 1] = 1;
        //         hunters[i][0] += 1;
        //         moved = 1;
        //     }

        // }
        // else if(shy - py < 0 && isWall[shx][shy][1] == 0 && isHunter[shx][shy + 1] == 0)
        // {
        //     isHunter[shx][shy] = 0;
        //     isHunter[shx][shy + 1] = 1;
        //     hunters[i][1] += 1;
        //     moved = 1;
        //     if(shx - px > 0 && isWall[shx - 1][shy + 1][0] == 0 && isHunter[shx - 1][shy + 1] == 0)
        //     {
        //         isHunter[shx][shy + 1] = 0;
        //         isHunter[shx - 1][shy + 1] = 1;
        //         hunters[i][0] -= 1;
        //         moved = 1;
        //     }
        //     else if(shx - px < 0 && isWall[shx][shy + 1][0] == 0 && isHunter[shx + 1][shy + 1] == 0)
        //     {
        //         isHunter[shx][shy + 1] = 0;
        //         isHunter[shx + 1][shy + 1] = 1;
        //         hunters[i][0] += 1;
        //         moved = 1;
        //     }
        // }
        // else {
        //     if (shx - px > 1 && isWall[shx - 1][shy][0] == 0 && isWall[shx - 2][shy][0] == 0 && isHunter[shx - 2][shy] == 0)
        //     {
        //         isHunter[shx][shy] = 0;
        //         isHunter[shx - 2][shy] = 1;
        //         hunters[i][0] -= 2;
        //         moved = 1;
        //     }
        //     else if (shx - px < -1 && isWall[shx][shy][0] == 0 && isWall[shx + 1][shy][0] == 0 && isHunter[shx + 2][shy] == 0)
        //     {
        //         isHunter[shx][shy] = 0;
        //         isHunter[shx + 2][shy] = 1;
        //         hunters[i][0] += 2;
        //         moved = 1;
        //     }
        //     else if (shx - px > 0 && isWall[shx - 1][shy][0] == 0 && isHunter[shx - 1][shy] == 0)
        //     {
        //         isHunter[shx][shy] = 0;
        //         isHunter[shx - 1][shy] = 1;
        //         hunters[i][0] -= 1;
        //         moved = 1;
        //     }
        //     else if (shx - px < 0 && isWall[shx][shy][0] == 0 && isHunter[shx + 1][shy] == 0)
        //     {
        //         isHunter[shx][shy] = 0;
        //         isHunter[shx + 1][shy] = 1;
        //         hunters[i][0] += 1;
        //         moved = 1;
        //     } 
        // }
        // if(moved == 0){
        //     ignore[player] = 1;
        //     i--; // update this hunter again
        // }else{
        //     for(int j = 0; j < alivePlayers; j++)ignore[j] = 0; // modify ignore[] for next hunter
        //     moved = 0;
        // }
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

void Lose(int height, int width, int cols,int players[][2], int *alivePlayers, int hunters[][2], int isHunter[][cols], float *fontsize,float maxsize, float speed , Font f, int *GameStoppage, int LightcoreH, int LightcoreW){
    for (int i = 0; i < *alivePlayers; i++)
    {
        int px = players[i][0];
        int py = players[i][1];
        if (isHunter[px][py] == 1 && (px!=LightcoreH || py!=LightcoreW))
        {
            if(*alivePlayers == 1){
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
            else{
                for(int j=i+1; j<*alivePlayers; j++){
                    players[j-1][0] = players[j][0];
                    players[j-1][1] = players[j][1];
                }
                (*alivePlayers) -= 1;
            }
        }
        
    }
}
// void AnimatePlayers(char dir, float *currX, float *currY, int targetX, int targetY, int players[][2], int player){
//     if(dir == 'R'){
//         if(*currY < targetY)*currY += GetFrameTime() / 3;
//     }
//     if(dir == 'L'){
//         if(*currY > targetY)*currY -= GetFrameTime() / 3;
//     }
//     if(dir == 'D'){
//         if(*currX < targetY)*currX += GetFrameTime() / 3;
//     }
//     if(dir == 'U'){
//         if(*currY > targetY)*currX -= GetFrameTime() / 3;
//     }
//     players[player][0] = *currX;
//     players[player][1] = *currY;
// }





