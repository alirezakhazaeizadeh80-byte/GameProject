# ifndef INPUTS_H
# define INPUTS_H

int controllingInputs(int players[][2],int playersCount, int shadowWatchers[][2],int shadowWatcherCont, int lightCoreH, int lightCoreW);
void signing(int x, int y, int n, int m, int mark[][m]);
void dfs(int x, int y, int n, int m,  int sign[][m], int *counter, int isWall[][m][2]);
int ControllingWalls(int WallCount, int n, int m, int walls[][2], char WallsState[], int isWall[][m][2]);
# endif