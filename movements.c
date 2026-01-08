#include "movements.h"
#include "raylib.h"
#include <stdbool.h>
#include "bonus.h"


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
    for (int i = 0; i < huntersCount; i++)
    {
        int player = searchNearestPlayer(i, playercount, alivePlayers, huntersCount, PlHuDistance);
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
            TextOutline(pos, origin, *fontsize, str, f);
            DrawTextPro(f, str, pos, origin, 0.0f, *fontsize, 2, color);
            *GameStoppage=1;
        }
        

    }
}

void Lose(int height, int width, int cols,int players[][2], int *alivePlayers, int hunters[][2], int huntersCount, int isHunter[][cols], float *fontsize,float maxsize, float speed , Font f, int *GameStoppage, int LightcoreH, int LightcoreW, float oldPlayers[][2], float oldHunters[][2]){
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
                TextOutline(pos, origin, *fontsize, str, f);
                DrawTextPro(f, str, pos, origin, 0.0f, *fontsize, 2, color);
                *GameStoppage=1;
            }
            else{
                int ind = FindIndex(hunters, huntersCount, px, py);
                if(fabs(oldHunters[ind][0] - hunters[ind][0]) <= 0.02 && fabs(oldHunters[ind][1] - hunters[ind][1]) <= 0.02){
                    for(int j=i+1; j<*alivePlayers; j++){
                        players[j-1][0] = players[j][0];
                        players[j-1][1] = players[j][1];
                    }
                    for(int k = 0; k < *alivePlayers; k++){
                        oldPlayers[k][0]  = (float)players[k][0];
                        oldPlayers[k][1]  = (float)players[k][1];
                    }
                    (*alivePlayers) -= 1;
                }
            }
        }
        
    }
}
 void AnimatePieces(float old[][2], int pieces[][2], int piecesCount, float speed){
    float targetX, targetY;
    for(int i=0; i<piecesCount; i++){
        targetX = (float)pieces[i][0];
        targetY = (float)pieces[i][1];
        if(fabsf(old[i][1] - targetY) > 0.02f){
            if(old[i][1] < (float)pieces[i][1])old[i][1]+=speed * GetFrameTime();
            else if(old[i][1] > (float)pieces[i][1])old[i][1]-=speed * GetFrameTime();
        }else{
            old[i][1] = targetY;
            if(fabsf(old[i][0] - targetX) > 0.02f){
            if(old[i][0] < (float)pieces[i][0])old[i][0]+=speed * GetFrameTime();
            else if(old[i][0] > (float)pieces[i][0])old[i][0]-=speed * GetFrameTime();
            }else{
                old[i][0] = targetX;
            }
        }
    }
}



