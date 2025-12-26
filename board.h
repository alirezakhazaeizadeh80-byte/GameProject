#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"

void DrawGridB(int rows, int cols, int cellWidth, int cellHeight, int height, int width);
<<<<<<< HEAD
Vector2 GetCellPosition(int row, int col, int startX, int startY, int cellWidth, int cellHeight);
void DrawPiece(Texture2D piece, int row, int col, int startX, int startY, int cellWidth, int cellHeight);
void ShowingLightcore(int rows, int cols, int cellWidth, int cellHeight);
void Showingpieces(Texture2D piece, int piecesNo, int pieces[][2], int cellWidth, int cellHeight);
void ShowingWalls(int wallCount ,int walls[][2], char wallsState[], int cellWidth, int cellHeight);
=======
void ShowingLightcore(int rows, int cols, int cellWidth, int cellHeight);
void Showingpieces(Texture2D piece, int piecesNo, int pieces[][2], int cellWidth, int cellHeight);
void ShowingWalls(int wallCount, int walls[][2], char wallsState[], int cellWidth, int cellHeight, int wallTurn[]);
void tempWalls(int rows, int cols, int cellWidth, int cellHeight, Rectangle BlaWalls[rows][cols][2]);
void showTempWall(Vector2 mousePos, int rows, int cols, int cellWidth, int cellHeight, int isWall[rows][cols][2], Rectangle BlaWalls[rows][cols][2]);
int ShowingTempWalls(int rows, int cols, int walls[][2], int* wallCount ,char wallsState[], int* tempWallConter, int isWall[rows][cols][2], Vector2 mousePos, Rectangle BlaWalls[rows][cols][2], int wallTurn[]);
int min(int x1, int x2);
int max(int x1, int x2);
>>>>>>> develop
#endif
