# ifndef INPUTS_H
# define INPUTS_H

void signing(int x, int y, int n, int m, int mark[][15]);
void dfs(int x, int y, int n, int m,  int sign[][15], int *counter, int isWall[][15][2]);
int ControllingWalls(int WallCount, int n, int m, int walls[][2], char WallsState[], int isWall[][15][2]);
# endif