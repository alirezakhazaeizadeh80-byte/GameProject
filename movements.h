#ifndef MOVEMENTS_C
#define MOVEMENTS_C
#include "raylib.h"
#include "raymath.h"
#include "bonus.h"

int isPlayer(int players[][2], int alivePlayers, int x, int y);
void movePieces(int rows, int cols, int players[][2],int player, int walls[][2], char wallsstates[] ,int wallcount, char move, int *showerror, int isWall[][cols][2], int alivePlayers);
void updateHunters(int row, int cols, int playercount, int hunters[][2], int huntersCount, int players[][2],int alivePlayers, int PlHuDistance[][playercount] ,int walls[][2], char wallStates[],int wallsCount, int isWall[][cols][2], int isHunter[][cols], int m, int isBonus[][m]);
void Win(int height, int width,int lightcoreX, int lightcoreY, int players[][2], int playerCount, Font f, float *fontsize, float maxsize, float speed, int *GameStoppage);
int searchNearestPlayer(int hunter, int playercount ,int alivePlayers , int huntersCount ,int PlHuDistance[huntersCount][playercount]);
void Lose(int height, int width, int cols,int players[][2], int *alivePlayers, int hunters[][2], int isHunter[][cols], float *fontsize,float maxsize, float speed , Font f, int *GameStoppage, int LightcoreH, int LightcoreW);
// void AnimatePlayers(char dir, float *currX, float *currY, int targetX, int targetY, int players[][2], int player);

#endif