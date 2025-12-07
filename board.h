#ifndef BOARD_H
#define BOARD_H

#include "raylib.h"

void DrawGridB(int rows, int cols, int cellWidth, int cellHeight, int height, int width);
void ShowingLightcore(int rows, int cols, int cellWidth, int cellHeight);
void Showingpieces(Texture2D piece, int piecesNo, int pieces[][2], int cellWidth, int cellHeight);
void ShowingWalls(int wallCount, int walls[][2], char wallsState[], int cellWidth, int cellHeight);

#endif
