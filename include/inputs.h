#ifndef INPUTS_H
#define INPUTS_H

/*
 * File: inputs.h
 * Purpose: Declarations for setup helpers and wall validation.
 */

/* Mark a cell and its neighbors as occupied in the placement mask. */
void signing(int x, int y, int n, int m, int mark[][15]);
/* Depth-first search to verify grid connectivity with walls. */
void dfs(int x, int y, int n, int m, int sign[][15], int *counter, int isWall[][15][2]);
/* Randomly generate valid walls while preserving grid connectivity. */
int ControllingWalls(int WallCount, int n, int m, int walls[][2], char WallsState[], int isWall[][15][2]);
#endif
