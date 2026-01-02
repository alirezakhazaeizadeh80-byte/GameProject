#ifndef PATHFINDING_C
#define PATHFINDING_C


#include <math.h>
#include <limits.h>
#define MAX_OPEN 150
#define MAX_CLOSED 150
typedef struct{
    int row;
    int col;
} Pair;

typedef struct
{
    int f;
    Pair p;
} pPair;

typedef struct{
    int parent_i;
    int parent_j;
    int f, g, h;
} cell;

void erase(pPair* openlist, int opencount, int index);
int isValid(int rows, int cols, int i, int j);
int isUnBlocked(int rows, int cols, Pair ori, Pair dest, int isWall[rows][cols][2]);
int isDestination(int i, int j, Pair dest);
int calculateH(int i, int j, Pair dest);
void tracepath(int rows , int cols, cell cells[][cols], Pair dest, Pair* paths, int *pathcount);
void aStar(int rows, int cols, int isWall[rows][cols][2], Pair ori, Pair dest, Pair* path, int* pathcount);

#endif