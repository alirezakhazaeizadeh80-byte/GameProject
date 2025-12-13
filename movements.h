#ifndef MOVEMENTS_C
#define MOVEMENTS_C
#include "raylib.h"


void movePieces(int rows, int cols, int players[][2],int player, int walls[][2], char wallsstates[] ,int wallcount, char move, int *showerror, int isWall[][cols][2]);
void updateShadowWatchers(int row, int cols, int shadowWatcher[][2], int shadowWatcherCount, int players[][2], int player, int walls[][2], char wallStates[],int wallsCount, int isWall[][cols][2], int isShadowWatcher[][cols]);
void Win(int height, int width,int lightcoreX, int lightcoreY, int players[][2], int playerCount, Font f, float *fontsize, float maxsize, float speed);
void Lose(int height, int width, int cols,int players[][2], int playerCount , int shaowWatcher[][2], int isShadowWatcher[][cols], float *fontsize,float maxsize, float speed , Font f);


#endif