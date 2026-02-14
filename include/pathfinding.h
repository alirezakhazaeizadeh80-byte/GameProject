#ifndef PATHFINDING_C
#define PATHFINDING_C

#include <math.h>
#include <limits.h>
#define MAX_OPEN 150
#define MAX_CLOSED 150
/*
 * File: pathfinding.h
 * Purpose: Declarations and data types for A* pathfinding.
 */

/* Grid coordinate pair. */
typedef struct
{
    int row;
    int col;
} Pair;

/* Open list entry with f-score and position. */
typedef struct
{
    int f;
    Pair p;
} pPair;

/* Cell bookkeeping for A* (parent and f/g/h scores). */
typedef struct
{
    int parent_i;
    int parent_j;
    int f, g, h;
} cell;

/* Remove an entry from the open list by index. */
void erase(pPair *openlist, int opencount, int index);
/* Validate that a cell is within bounds. */
int isValid(int rows, int cols, int i, int j);
/* Check whether the edge between two adjacent cells is not blocked by a wall. */
int isUnBlocked(int rows, int cols, Pair ori, Pair dest, int isWall[][15][2]);
/* Return true if the current cell matches the destination. */
int isDestination(int i, int j, Pair dest);
/* Manhattan distance heuristic for A*. */
int calculateH(int i, int j, Pair dest);
/* Reconstruct the path by following parent pointers. */
void tracepath(int rows, int cols, cell cells[][15], Pair dest, Pair *paths, int *pathcount);
/* Compute a path from origin to destination while avoiding walls and bonuses. */
void aStar(int rows, int cols, int isWall[][15][2], Pair ori, Pair dest, Pair *path, int *pathcount, int isBonus[][15]);

#endif
