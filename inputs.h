# ifndef INPUTS_H
# define INPUTS_H


int controllingInputs(int players[][2],int playersCount, int shadowWatchers[][2],int shadowWatcherCont, int lightCoreH, int lightCoreW);
void signing(int x, int y, int n, int m, int mark[][m]);
void dfs(int x, int y, int *sw, int n, int m,  int sign[][m][2], int state, int isWall[][m][2]);
# endif