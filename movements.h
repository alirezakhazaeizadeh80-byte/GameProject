#ifndef MOVEMENTS_C
#define MOVEMENTS_C
#include "raylib.h"
#include "raymath.h"


void movePieces(int rows, int cols, int players[][2],int player, int walls[][2], char wallsstates[] ,int wallcount, char move, int *showerror, int isWall[][cols][2]);
void updateHunters(int row, int cols, int hunters[][2], int huntersCount, int players[][2],int alivePlayers, int PlHuDistance[][alivePlayers] ,int walls[][2], char wallStates[],int wallsCount, int isWall[][cols][2], int isHunter[][cols]);
void Win(int height, int width,int lightcoreX, int lightcoreY, int players[][2], int playerCount, Font f, float *fontsize, float maxsize, float speed, int *GameStoppage);
int searchNearestPlayer(int hunter ,int alivePlayers , int huntersCount ,int PlHuDistance[huntersCount][alivePlayers], int ignore[]);
void Lose(int height, int width, int cols,int players[][2], int *alivePlayers, int hunters[][2], int isHunter[][cols], float *fontsize,float maxsize, float speed , Font f, int *GameStoppage, int LightcoreH, int LightcoreW);


#endif