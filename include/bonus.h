#ifndef BONUS_H
#define BONUS_H
#include "raylib.h"
#include "raymath.h"
#include "movements.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * File: bonus.h
 * Purpose: Declarations for bonus selection and effects.
 */

/* Allow the player to pick and move a hunter during the bonus. */
int PickHunter(int hunters[][2], int huntersCount, float cellWidth, float cellHeight, int n, int m, int isWall[][15][2], int *PickBonusCount, int isHunter[][15], int *TextPrinted, int *PickedHunter, int *HunterX, int *HunterY, int players[][2], int alivePlayers);
/* Find an index in a 2D list of positions. */
int FindIndex(int bonuses[][2], int BonusesCount, int x, int y);
/* Check whether any player occupies the given grid cell. */
int CheckPlayers(int players[][2], int alivePlayers, int x, int y);
/* Randomly move players and hunters during the board quake bonus. */
void ChangePositionsRandomly(int players[][2], int hunters[][2], int aliveplayers, int huntersCount, int n, int m, int isHunter[][15], int isWall[][15][2], int isBonus[][15]);
/* Draw a black outline around text to improve readability. */
void TextOutline(Vector2 pos, Vector2 origin, float fontSize, const char *str, Font f);
/* Evaluate and apply bonus effects, including animations and input handling. */
void CheckBonus(int *option, float *fontsize, float maxsize, float speed, int playerMoved[], int width, int height, Font f, char *TextState, float *TextTimer, int *TextPrinted, int hunters[][2], int huntersCount, int n, int m, int isWall[][15][2], int cellWidth, int cellHeight, int *showError, int alivePlayers, int players[][2], int IsBonus[][15], int *BonusesCount, int BonuaWalls[], float *MoveTimer, int isHunter[][15], int *BoardQuake, int bonuses[][2], int *counter, int *isQuake, int *PickedHunter, int *HunterX, int *HunterY, int LightcoreX, int LightcoreY, float oldHunters[][2], int *PickBonusCount, int *MovePlayerBonus);
#endif
