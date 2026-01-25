#ifndef MOVEMENTS_C
#define MOVEMENTS_C
#include "raylib.h"
#include "raymath.h"
#include "bonus.h"
#include "pathfinding.h"
#include <math.h>

int isPlayer(int players[][2], int alivePlayers, int x, int y);
void movePieces(int rows, int cols, int players[][2],int player, int walls[][2], char wallsstates[] ,int wallcount, char move, int *showerror, int isWall[][15][2], int alivePlayers, int isHunter[][15]);
void updateHunters(int n, int m, int hunters[][2], int huntersCount, int players[][2], int alivePlayers, int PlHuDistance[][15] , int isWall[][15][2], int isHunter[][15], int dir[]);
void Win(int height, int width,int lightcoreX, int lightcoreY, int players[][2], int playerCount, Font f, float *fontsize, float maxsize, float speed, int *GameStoppage);
int searchNearestPlayer(int hunter,int alivePlayers , int huntersCount ,int PlHuDistance[][15], int ignore[]);
void Lose(int height, int width, int cols,int players[][2], int *alivePlayers, int hunters[][2], int huntersCount, int isHunter[][15], float *fontsize,float maxsize, float speed , Font f, int *GameStoppage, int LightcoreH, int LightcoreW, float oldPlayers[][2], float oldHunters[][2], int *counter, int playerMoved[]);
void AnimatePieces(float old[][2], int pieces[][2], int piecesCount, float speed, int state, int dir[]);
void PiecesMoving(int GameStoppage, float cellWidth, float cellHeight, int *alivePlayers, int players[][2], int playerMoved[], int *player, int sw, int n, int m, int walls[][2], int *WallCount, int BonusWalls[], int *TempWallcounter, int isWall[][15][2], Rectangle BlaWalls[][15][2], char WallsState[], int *showError, int *counter, float *timer, int wallTurn[], int hunters[][2], int huntersCount, int PlHuDistance[][15], float *shakeTimeLeft, int BoardQuake, int isHunter[][15], int dir[], int isBonus[][15], Camera2D *cam, float shakeIntensity, Vector2 *shakeOffset, int *option, int *MovePlayerBonus);
#endif