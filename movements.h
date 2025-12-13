#ifndef MOVEMENTS_C
#define MOVEMENTS_C


void movePieces(int rows, int cols, int players[][2],int player, int walls[][2], char wallsstates[] ,int wallcount, char move, int *showerror, int isWall[][cols][2]);
//int hitWalls(int rows, int cols, int players[][2],int player, int walls[][2], int wallcount, char wallsstates[] , char move);
void updateShadowWatchers(int row, int cols, int shadowWatcher[][2], int shadowWatcherCount, int players[][2], int player, int walls[][2], char wallStates[],int wallsCount, int isWall[][cols][2]);
//int checkWall(int walls[][2], int wallsCount,char wallStates[] ,char state, int wallx, int wally);


#endif