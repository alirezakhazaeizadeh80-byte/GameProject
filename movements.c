
# include "movements.h"



void movePieces(int rows, int cols, int players[][2], int player, char move, int *showerror){
    if (move == 'W' && players[player][0] <= 0)
    {
        *showerror = 1;
    }
    else if (move == 'W')
    {
        players[player][0] -= 1;
    }
    if (move == 'A' && players[player][1] <= 0)
    {
        *showerror = 1;
    }
    else if (move == 'A')
    {
        players[player][1] -= 1;
    }
    if (move == 'S' && players[player][0] >= ( rows - 1) )
    {
        *showerror = 1;
    }
    else if (move == 'S')
    {
        players[player][0] += 1;
    }
    if (move == 'D' && players[player][1] >= (cols - 1))
    {
        *showerror = 1;
    }
    else if (move == 'D')
    {
        players[player][1] += 1;
    }



}








