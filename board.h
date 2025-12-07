#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"

void DrawGridB(int rows, int cols, int cellWidth, int cellHeight, int height, int width);
Vector2 GetCellPosition(int row, int col, int startX, int startY, int cellWidth, int cellHeight);
void DrawPiece(Texture2D piece, int row, int col, int startX, int startY, int cellWidth, int cellHeight);
void ShowingLightcore(int rows, int cols, int cellWidth, int cellHeight);
void Showingpieces(Texture2D piece, int piecesNo, int pieces[][2], int cellWidth, int cellHeight);
void ShowingWalls(int wallCount ,int walls[][2], char wallsState[], int cellWidth, int cellHeight);
#endif
