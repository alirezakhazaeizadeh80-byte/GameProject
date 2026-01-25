#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"
#include <stdio.h>

void DrawGridB(int rows, int cols, int cellWidth, int cellHeight, int height, int width);
void ShowingLightcore(int rows, int cols, int cellWidth, int cellHeight);
void Showingpieces(Texture2D piece, int piecesNo, float pieces[][2], int cellWidth, int cellHeight, int playerMoved[], int state, float timer, float *transparency, char *s, int selected, int *PickedHunter, int *MovePlayerBonus);
void ShowingBonusBox(Texture2D box, int bonusCount, int bonuses[][2], int cellWidth, int cellHeight);
void ShowingWalls(int wallCount, int walls[][2], char wallsState[], int cellWidth, int cellHeight, int wallTurn[]);
void tempWalls(int rows, int cols, int cellWidth, int cellHeight, Rectangle BlaWalls[][15][2]);
void showTempWall(Vector2 mousePos, int rows, int cols, int cellWidth, int cellHeight, int isWall[][15][2], Rectangle BlaWalls[][15][2]);
int ShowingTempWalls(int rows, int cols, int walls[][2], int* wallCount ,char wallsState[], int* tempWallCounter, int isWall[][15][2], Vector2 mousePos, Rectangle BlaWalls[][15][2], int wallTurn[], int state, int BonusWalls[], int player);
int min(int x1, int x2);
int max(int x1, int x2);
void SavingGame(int *lightCoreH, int *lightCoreW, int players[][2], int hunters[][2], int *playersCount, int *huntersCount, int walls[][2], int *n, int *m, int isWall[][15][2], int *BonusCount, int isBonus[][15], int bonuses[][2], int playerMoved[], int BonusWalls[], int PlHuDistance[][15], float oldHunters[][2], float oldPlayers[][2], char WallsState[], int *TempWallcounter, int *option, int WallTurn[], int *WallCount, int isHunter[][15], int *alivePlayers, int *counter);
void ReturnGameBasics(FILE *game, int *lightCoreH, int *lightCoreW, int *playersCount, int *huntersCount, int isReturn, int *n, int *m, float *width, float *height, float *maxsize, float *MaxSize, float *cellHeight, float *cellWidth);
void ReturnGameDetails(FILE *game, int isReturn, int lightCoreH, int lightCoreW, int players[][2], int hunters[][2], int playersCount, int huntersCount, int walls[][2], int n, int m, int isWall[][15][2], int *BonusCount, int isBonus[][15], int bonuses[][2], int playerMoved[], int BonusWalls[], int PlHuDistance[][15], float oldHunters[][2], float oldPlayers[][2], char WallsState[], int *TempWallcounter, int *option, int WallTurn[], int *WallCount, int isHunter[][15], int *alivePlayers, int *counter, int dir[]);
void LoadPiecesAndFonts(Texture2D *pieceRed, Texture2D *pieceBlue, Texture2D *box, Font *f, float maxsize);
#endif
