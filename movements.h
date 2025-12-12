#ifndef MOVEMENTS_C
#define MOVEMENTS_C


void movePieces(int rows, int cols, int players[][2],int player, int walls[][2], char wallsstates[] ,int wallcount, char move, int *showerror);
int hitWalls(int rows, int cols, int players[][2],int player, int walls[][2], int wallcount, char wallsstates[] , char move);


#endif