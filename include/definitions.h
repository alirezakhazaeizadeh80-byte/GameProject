#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <stdio.h>
#include <stdlib.h>
/*
 * File: definitions.h
 * Purpose: Global game state and configuration variables.
 * Notes: These globals are shared across modules for simplicity.
 */
/* Window and board dimensions. */
float width;
float height;
int m, n;
/* Entity counts. */
int playersCount;
int huntersCount;
int WallCount;
/* Goal (lightcore) position. */
int lightCoreH;
int lightCoreW;
/* UI and feedback flags. */
int showError = 0;
float maxsize;
float MaxSize;
int TextPrinted = 0;
int BoardQuake = 0;
int BonusCount = 5;
int option = -1;
char TextState = 'I';
float TextTimer = -1;
float MoveTimer = 0;
int isQuake = 0;
int PickedHunter = -1;
int HunterX = -1;
int HunterY = -1;
/* Bonus data. */
int bonuses[5][2];
float fontsize = 10.0f;
float FontSize = 10.0f;
float speed = 50.0f;
float Speed = 60.0f;
/* Game flow state. */
int GameStoppage = 0;
float transparency = 0.0;
int selected = -1;
char s = 'I';
float timer = -1;
int player = -1;
int sw = 0;
int counter = 0;
int isReturn = 0;
int alivePlayers;
int TempWallcounter;
/* Core board state. */
int players[15][2];
int hunters[15][2];
char WallsState[300];
int walls[300][2];
int isBonus[15][15];
int wallTurn[300];
int isWall[15][15][2];
int isHunter[15][15];
int PlHuDistance[20][15];
float oldHunters[20][2];
float oldPlayers[20][2];
int BonusWalls[20];
int playerMoved[20];
Rectangle BlaWalls[15][15][2];
int dir[20];
/* Geometry and rendering assets. */
float cellHeight;
float cellWidth;
Color Background = {213, 249, 222, 1};
Texture2D pieceRed;
Texture2D pieceBlue;
Texture2D box;
Font f;
/* Camera and screen shake. */
float shakeTimeLeft = 0.0f;
float shakeIntensity = 5.0f;
Camera2D cam = {0};
Vector2 shakeOffset = {0, 0};
/* Miscellaneous flags. */
int GameStart = 0;
int PickBonusCount = 0;
int MovePlayerBonus = -1;
float vul = 0.5f;
int StartFade = 0;
#endif
