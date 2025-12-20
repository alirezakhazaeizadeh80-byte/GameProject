# ifndef INPUTS_H
# define INPUTS_H

void signing(int x, int y, int n, int m, int mark[][m]);
void dfs(int x, int y, int n, int m,  int sign[][m], int *counter, int isWall[][m][2]);
int ControllingWalls(int WallCount, int n, int m, int walls[][2], char WallsState[], int isWall[][m][2]);
# endif